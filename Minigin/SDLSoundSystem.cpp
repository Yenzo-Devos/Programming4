#include "SDLSoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <unordered_map>

#include <thread>
#include <queue>
#include <mutex>

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl();
	~SDLSoundSystemImpl();

	SDLSoundSystemImpl(const SDLSoundSystemImpl& other) = delete;
	SDLSoundSystemImpl(SDLSoundSystemImpl&& other) = delete;
	SDLSoundSystemImpl& operator=(const SDLSoundSystemImpl& other) = delete;
	SDLSoundSystemImpl& operator=(SDLSoundSystemImpl&& other) = delete;

	bool Load(const std::string& filePath, const std::string& soundID);
	void Play(const std::string& soundID, const int volume, int loops);
	void PlayMusic(const std::string& filepath, int loops);
	void PauseSound();
	void PauseMusic();
	void ResumeSound();
	void ResumeMusic();
	void StopSound();
	void StopMusic();
	void MuteAllSound();
	void SetVolume(const std::string& soundID, const int volume);
	void AddToQueue(AudioFile audio);

private:
	void AudioThreadQueue(std::stop_token stopToken);

	std::mutex m_QueueMutex{};
	std::mutex m_PlayMutex{};
	std::jthread m_AudioThread{};
	std::condition_variable m_Condition;
	
	std::queue<AudioFile> m_AudioQueue{};
	std::unordered_map<std::string, Mix_Chunk*> m_pLoadedSounds{};
	Mix_Music* m_pLoadedMusic{};
	bool m_IsMuted{ false };
};

dae::SDLSoundSystem::SDLSoundSystemImpl::SDLSoundSystemImpl()
	: m_AudioThread{ [this](std::stop_token stopToken) { this->AudioThreadQueue(std::move(stopToken)); } }
{
}

dae::SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
{
	m_AudioThread.request_stop();
	for (auto sound : m_pLoadedSounds)
		StopSound();
	StopMusic();
	
	for (auto sound : m_pLoadedSounds)
		Mix_FreeChunk(sound.second);
	Mix_FreeMusic(m_pLoadedMusic);

	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	m_AudioThread.join();
}

bool dae::SDLSoundSystem::SDLSoundSystemImpl::Load(const std::string& filePath, const std::string& soundID)
{
	Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());

	if (!sound)
	{
		std::cerr << "Loading sound effect failed: " << Mix_GetError() << "\n";
		return false;
	}

	std::lock_guard<std::mutex> lock(m_QueueMutex);
	m_pLoadedSounds[soundID] = sound;
	return true;
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::Play(const std::string& soundID, const int volume, int loops)
{
	int channel = Mix_PlayChannel(-1, m_pLoadedSounds[soundID], loops);
	if (channel == -1)
	{
		std::cerr << "Playing audio failed: " << Mix_GetError() << '\n';
		return;
	}
	if (m_IsMuted)
		Mix_Volume(channel, 0);
	else
		Mix_Volume(channel, volume);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::PlayMusic(const std::string& filepath, int loops)
{
	m_pLoadedMusic = Mix_LoadMUS(filepath.c_str());
	if (!m_pLoadedMusic)
	{
		std::cerr << "Loading music failed: " << Mix_GetError() << '\n';
		return;
	}
	if (Mix_PlayMusic(m_pLoadedMusic, loops) == -1)
	{
		std::cerr << "Playing music failed: " << Mix_GetError() << '\n';
		return;
	}
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::PauseSound()
{
	Mix_Pause(-1);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::PauseMusic()
{
	Mix_PauseMusic();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::ResumeSound()
{
	Mix_Resume(-1);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::ResumeMusic()
{
	Mix_ResumeMusic();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::StopSound()
{
	Mix_HaltChannel(-1);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::StopMusic()
{
	Mix_HaltMusic();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::MuteAllSound()
{
	if (m_IsMuted)
	{
		Mix_Volume(-1, 100);
		Mix_VolumeMusic(100);
		m_IsMuted = false;
	}
	else
	{
		Mix_Volume(-1, 0);
		Mix_VolumeMusic(0);
		m_IsMuted = true;
	}
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::SetVolume(const std::string& soundID, const int volume)
{
	Mix_VolumeChunk(m_pLoadedSounds[soundID], volume);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::AddToQueue(AudioFile audio)
{
	{
		std::lock_guard<std::mutex> lock(m_QueueMutex);
		m_AudioQueue.push(audio);
	}

	m_Condition.notify_all();
}

// got help with this logic from Yarno Ceulemans mine just locked my whole game up
void dae::SDLSoundSystem::SDLSoundSystemImpl::AudioThreadQueue(std::stop_token stopToken)
{
	while (!stopToken.stop_requested())
	{
		std::unique_lock<std::mutex> playLock{ m_PlayMutex };
		m_Condition.wait(playLock, [this, &stopToken]() -> bool {
			std::lock_guard queueLock{ m_QueueMutex };
			return !m_AudioQueue.empty() || stopToken.stop_requested();
			});

		m_QueueMutex.lock();
		AudioFile temp = m_AudioQueue.front();
		m_AudioQueue.pop();
		m_QueueMutex.unlock();

		if (!Load(temp.filePath, temp.name))
			continue;

		if (m_pLoadedSounds.find(temp.name) != m_pLoadedSounds.end())
			Play(temp.name, 100, temp.loops);
	}
}

dae::SDLSoundSystem::SDLSoundSystem()
	: m_pImpl{ std::make_unique<SDLSoundSystemImpl>() }
{
	if (Mix_Init(SDL_INIT_AUDIO) < 0)
		std::cerr << "SDL_mixer init failed: " << SDL_GetError() << '\n';
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cerr << "SDL_Mixer OpenAudio failed: " << Mix_GetError() << '\n';
}

bool dae::SDLSoundSystem::Load(const std::string& filePath, const std::string& soundID)
{
	return m_pImpl->Load(filePath, soundID);
}

void dae::SDLSoundSystem::Play(const std::string& soundID, const int volume, int loops)
{
	m_pImpl->Play(soundID, volume, loops);
}

void dae::SDLSoundSystem::PlayMusic(const std::string& filepath, int loops)
{
	m_pImpl->PlayMusic(filepath, loops);
}

void dae::SDLSoundSystem::PauseSound()
{
	m_pImpl->PauseSound();
}

void dae::SDLSoundSystem::PauseMusic()
{
	m_pImpl->PauseMusic();
}

void dae::SDLSoundSystem::ResumeSound()
{
	m_pImpl->ResumeSound();
}

void dae::SDLSoundSystem::ResumeMusic()
{
	m_pImpl->ResumeMusic();
}

void dae::SDLSoundSystem::StopSound()
{
	m_pImpl->StopSound();
}

void dae::SDLSoundSystem::StopMusic()
{
	m_pImpl->StopMusic();
}

void dae::SDLSoundSystem::MuteAllSound()
{
	m_pImpl->MuteAllSound();
}

void dae::SDLSoundSystem::SetVolume(const std::string& soundID, const int volume)
{
	m_pImpl->SetVolume(soundID, volume);
}

void dae::SDLSoundSystem::AddToQueue(AudioFile audio)
{
	m_pImpl->AddToQueue(audio);
}

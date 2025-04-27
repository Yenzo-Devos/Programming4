#include "SDLSoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <unordered_map>

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl() = default;
	~SDLSoundSystemImpl();

	SDLSoundSystemImpl(const SDLSoundSystemImpl& other) = delete;
	SDLSoundSystemImpl(SDLSoundSystemImpl&& other) = delete;
	SDLSoundSystemImpl& operator=(const SDLSoundSystemImpl& other) = delete;
	SDLSoundSystemImpl& operator=(SDLSoundSystemImpl&& other) = delete;

	bool Load(const std::string& filePath, const std::string& soundID);
	void Play(const std::string& soundID, const int volume, int loops);
	void Pause();
	void Resume();
	void Stop();
	void MuteAllSound();
	void SetVolume(const std::string& soundID, const int volume);

private:
	std::unordered_map<std::string, Mix_Chunk*> m_pLoadedSounds;
	bool m_IsMuted{ false };
};

dae::SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
{
	for (auto sound : m_pLoadedSounds)
		Mix_FreeChunk(sound.second);

	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}

bool dae::SDLSoundSystem::SDLSoundSystemImpl::Load(const std::string& filePath, const std::string& soundID)
{
	Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());

	if (!sound)
	{
		std::cerr << "Failed to load sound effect" << Mix_GetError() << "\n";
		return false;
	}

	m_pLoadedSounds[soundID] = sound;
	return true;
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::Play(const std::string& soundID, const int volume, int loops)
{
	if (m_pLoadedSounds.find(soundID) != m_pLoadedSounds.end())
	{
		int channel = Mix_PlayChannel(-1, m_pLoadedSounds[soundID], loops);
		Mix_Volume(channel, volume);
	}
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::Pause()
{
	Mix_Pause(-1);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::Resume()
{
	Mix_Resume(-1);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::Stop()
{
	Mix_HaltChannel(-1);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::MuteAllSound()
{
	if (m_IsMuted)
		Mix_Volume(-1, 100);
	else
		Mix_Volume(-1, 0);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::SetVolume(const std::string& soundID, const int volume)
{
	Mix_VolumeChunk(m_pLoadedSounds[soundID], volume);
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

void dae::SDLSoundSystem::Pause()
{
	m_pImpl->Pause();
}

void dae::SDLSoundSystem::Resume()
{
	m_pImpl->Resume();
}

void dae::SDLSoundSystem::Stop()
{
	m_pImpl->Stop();
}

void dae::SDLSoundSystem::MuteAllSound()
{
	m_pImpl->MuteAllSound();
}

void dae::SDLSoundSystem::SetVolume(const std::string& soundID, const int volume)
{
	m_pImpl->SetVolume(soundID, volume);
}

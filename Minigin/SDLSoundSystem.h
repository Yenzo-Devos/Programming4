#pragma once
#include "SoundSystem.h"

#include <memory>

namespace dae
{
	class SDLSoundSystem : public SoundSystem
	{
	public:
		SDLSoundSystem();

		bool Load(const std::string& filePath, const std::string& soundID) override;
		void Play(const std::string& soundID, const int volume, int loops) override;
		void PlayMusic(const std::string& filepath, int loops) override;
		void PauseSound() override;
		void PauseMusic() override;
		void ResumeSound() override;
		void ResumeMusic() override;
		void StopSound() override;
		void StopMusic() override;
		void MuteAllSound() override;
		void SetVolume(const std::string& soundID, const int volume) override;
		void AddToQueue(AudioFile audio);

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}
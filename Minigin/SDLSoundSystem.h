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
		void Pause() override;
		void Resume() override;
		void Stop() override;
		void MuteAllSound() override;
		void SetVolume(const std::string& soundID, const int volume) override;
		void AddToQueue(AudioFile audio);

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}
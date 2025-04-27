#pragma once
#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		// add needed functions for soundsystem like play etc
		virtual ~SoundSystem() = default;

		virtual bool Load(const std::string& filePath, const std::string& soundID) = 0;
		virtual void Play(const std::string& soundID, const int volume, int loops) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Stop() = 0;
		virtual void MuteAllSound() = 0;
		virtual void SetVolume(const std::string& soundID, const int volume) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
		bool Load(const std::string&, const std::string&) override { return false; }
		void Play(const std::string&, const int, int) override {}
		void Pause() override {}
		void Resume() override {}
		void Stop() override {}
		void MuteAllSound() override {}
		void SetVolume(const std::string&, const int) override {}
	};
}
#pragma once
#include <string>

namespace dae
{
	struct AudioFile
	{
		std::string filePath;
		std::string name;
		int loops;
	};

	class SoundSystem
	{
	public:
		// add needed functions for soundsystem like play etc
		virtual ~SoundSystem() = default;

		virtual bool Load(const std::string& filePath, const std::string& soundID) = 0;
		virtual void Play(const std::string& soundID, const int volume, int loops) = 0;
		virtual void PlayMusic(const std::string& filepath, int loops) = 0;
		virtual void PauseSound() = 0;
		virtual void PauseMusic() = 0;
		virtual void ResumeSound() = 0;
		virtual void ResumeMusic() = 0;
		virtual void StopSound() = 0;
		virtual void StopMusic() = 0;
		virtual void MuteAllSound() = 0;
		virtual void SetVolume(const std::string& soundID, const int volume) = 0;
		virtual void AddToQueue(AudioFile audio) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		bool Load(const std::string&, const std::string&) override { return false; }
		void Play(const std::string&, const int, int) override {}
		void PlayMusic(const std::string& filepath, int loops) override {}
		void PauseSound() override {}
		void PauseMusic() override {}
		void ResumeSound() override {}
		void ResumeMusic() override {}
		void StopSound() override {}
		void StopMusic() override {}
		void MuteAllSound() override {}
		void SetVolume(const std::string&, const int) override {}
		void AddToQueue(AudioFile) override {};
	};
}
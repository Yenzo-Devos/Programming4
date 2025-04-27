#pragma once
#include <string>

class SoundSystem
{
public:
	// add needed functions for soundsystem like play etc
	virtual ~SoundSystem() = default;
	virtual void Play(const std::string soundID, const float volume) = 0;

private:

};


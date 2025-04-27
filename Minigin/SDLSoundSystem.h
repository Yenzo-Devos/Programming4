#pragma once
#include "SoundSystem.h"

class SDLSoundSystem : public SoundSystem
{
public:
	void Play(const std::string soundID, const float volume) override;
private:

};


#pragma once
#include "SoundSystem.h"

#include <memory>

class ServiceLocator final
{
public:
	static SoundSystem& GetSoundSystem() { return *m_SoundSystemInstance; }
	static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss) { m_SoundSystemInstance = std::move(ss); }
private:
	static std::unique_ptr<SoundSystem> m_SoundSystemInstance;
};


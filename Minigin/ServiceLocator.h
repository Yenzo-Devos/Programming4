#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *m_pSoundSystemInstance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
		{
			if (ss == nullptr)
				m_pSoundSystemInstance = std::make_unique<NullSoundSystem>();
			else
				m_pSoundSystemInstance = std::move(ss);
		}

	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystemInstance;
	};
}
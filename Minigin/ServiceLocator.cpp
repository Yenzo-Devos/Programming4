#include "ServiceLocator.h"
std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_pSoundSystemInstance{std::make_unique<NullSoundSystem>()};
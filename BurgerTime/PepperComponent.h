#pragma once
#include "BaseComponent.h"
#include "HitboxComponent.h"
#include "glm.hpp"
#include "GameObject.h"
#include "Subject.h"

namespace game
{
	class PepperComponent : public dae::BaseComponent
	{
	public:
		PepperComponent(dae::GameObject* pOwner, dae::HitboxComponent* hitboxComp, int pepperCount);
		~PepperComponent() = default;

		PepperComponent(const PepperComponent& other) = delete;
		PepperComponent(PepperComponent&& other) = delete;
		PepperComponent& operator=(const PepperComponent& other) = delete;
		PepperComponent& operator=(PepperComponent&& other) = delete;
		
		void Update(float deltaTime) override;
		bool Activate(glm::vec2 pos, glm::vec2 dir);

		void AddObserver(dae::Observer* pObserver);
		void RemoveObserver(dae::Observer* pObserver);

		int GetPepperCount() const { return m_PepperCount; }
	
	private:
		bool m_IsActive{ false };
		float m_AccuActiveTime{ 0.f };
		const float m_ActiveTime{ 0.5f };
		void DeActivate();

		int m_PepperCount{ };
		
		dae::HitboxComponent* m_pHitboxComp{};
		std::unique_ptr<dae::Subject> m_pPepperEvent;
	};
}



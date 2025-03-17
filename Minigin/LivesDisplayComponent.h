#pragma once
#include "Observer.h"
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class LivesDisplayComponent : public Observer, public BaseComponent
	{
	public:
		LivesDisplayComponent(GameObject* owner, TextComponent* pTexture);
		virtual ~LivesDisplayComponent() = default;

		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

		void Update(float) override{};
		void Broadcast(GameObject* pGameObject, Event event) override;
	
	private:
		TextComponent* m_pLivesText;
		std::string m_LifeText;

		void UpdateLivesTexture(GameObject* pGameObject);
	};
}


#pragma once
#include "Observer.h"
#include "BaseComponent.h"

#include <string>

namespace dae
{
	class TextureComponent;
	class GameObject;
}

namespace game
{
	class LivesDisplayComponent : public dae::Observer, public dae::BaseComponent
	{
	public:
		LivesDisplayComponent(dae::GameObject* owner, dae::TextureComponent* pTexture);
		virtual ~LivesDisplayComponent() = default;

		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

		void Update(float) override{};
		void Broadcast(dae::GameObject* pGameObject, dae::Event event) override;
	
	private:
		dae::TextureComponent* m_pLivesTexture;
	};
}


#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "TextureComponent.h"

namespace dae
{
	class LivesComponent : public BaseComponent, public Subject
	{
	public:
		LivesComponent(GameObject* owner, int maxHealth, TextureComponent* pTexture);
		virtual ~LivesComponent() = default;

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		virtual void Update(float) override {};
		void LoseLife(int amount);

	private:
		const int m_MaxLives;
		int m_CurrentLives;
	};
}


#include "FallComponent.h"
#include "GameObject.h"

game::FallComponent::FallComponent(dae::GameObject* pOwner, float fallingSpeed)
	: BaseComponent( pOwner )
	, m_Speed{ fallingSpeed }
{
}

void game::FallComponent::Update(float deltaTime)
{
	if (!m_IsActive)
		return;

	m_pOwner->SetLocalPosition(m_pOwner->GetWorldPosition() + (m_Direction * m_Speed * deltaTime));
}

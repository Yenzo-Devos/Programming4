#include "Command.h"
#include "GameObject.h"

dae::MoveCommand::MoveCommand(GameObject* gameObject, glm::vec3 dir, float speed)
	: m_pGameObject{ gameObject }
	, m_Direction{ dir }
	, m_Speed{ speed }
{

}

void dae::MoveCommand::Execute(float deltaTime)
{
	m_pGameObject->SetLocalPos(m_pGameObject->GetWorldPos() + (m_Direction * m_Speed * deltaTime));
}

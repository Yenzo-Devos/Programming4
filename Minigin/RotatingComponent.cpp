#define _USE_MATH_DEFINES

#include "RotatingComponent.h"
#include "GameObject.h"

dae::RotatingComponent::RotatingComponent(GameObject* owner, glm::vec3 origin, float radius, float speed)
	: BaseComponent(owner)
	, m_Origin{ origin }
	, m_Radius{ radius }
	, m_Speed{ speed }
{

}

void dae::RotatingComponent::Update(float deltaTime)
{
	m_Angle += m_Speed * deltaTime;

	glm::vec3 pos = m_Origin + m_Radius * glm::vec3{ cos(m_Angle), sin(m_Angle), 0 };

	m_pOwner->SetLocalPosition(pos);

	if (m_Angle > 2 * M_PI)
		m_Angle -= float(2 * M_PI);
	else if (m_Angle < (2 * M_PI) * -1)
		m_Angle += float(2 * M_PI);
}

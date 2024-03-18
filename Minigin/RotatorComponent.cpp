#define _USE_MATH_DEFINES

#include "RotatorComponent.h"
#include "GameObject.h"
#include <math.h>


engine::RotatorComponent::RotatorComponent(engine::GameObject* pOwner, const glm::vec3& origin, float radius, float speed)
	: BaseComponent(pOwner)
	, m_Origin{ origin }
	, m_Radius{ radius }
	, m_Speed{ speed }
{
	
}

void engine::RotatorComponent::Update()
{
	m_Angle += deltaTime * (float((2 * M_PI)) * m_Speed);

	const glm::vec3 position{ m_Origin + m_Radius * glm::vec3{glm::cos(m_Angle), glm::sin(m_Angle), 0} };

	GetOwner()->SetLocalPosition(position);

	if (m_Angle > 2 * M_PI)
		m_Angle -= float(2 * M_PI);
	else if (m_Angle < (2 * M_PI) * -1)
		m_Angle += float(2 * M_PI);
}

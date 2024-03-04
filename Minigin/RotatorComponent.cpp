#define _USE_MATH_DEFINES

#include "RotatorComponent.h"
#include "GameObject.h"
#include <math.h>


engine::RotatorComponent::RotatorComponent(engine::GameObject* pOwner, const glm::vec3& origin, float radius)
	: BaseComponent(pOwner)
	, m_Origin{ origin }
	, m_Radius{ radius }
{

}

void engine::RotatorComponent::Update(float deltaTime)
{
	m_Angle += deltaTime * float((2 * M_PI));

	const glm::vec3 position{ m_Origin + m_Radius * glm::vec3{glm::cos(m_Angle), glm::sin(m_Angle), 0} };

	GetOwner()->SetLocalPosition(position);
}

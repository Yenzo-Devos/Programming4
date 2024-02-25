#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		void Awake() override;
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_position;
	};
}

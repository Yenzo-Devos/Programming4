#pragma once
#include "BaseComponent.h"
#include "box2d.h"

#include <vector>
#include <memory>

namespace dae
{
	class HitboxComponent : public BaseComponent
	{
	public:
		HitboxComponent(GameObject* owner);
		~HitboxComponent() = default;
		
		HitboxComponent(const HitboxComponent& other) = delete;
		HitboxComponent(HitboxComponent&& other) = delete;
		HitboxComponent& operator=(const HitboxComponent& other) = delete;
		HitboxComponent& operator=(HitboxComponent&& other) = delete;

		void AddHitbox(float halfWidth, float halfHeight);
		std::vector<b2Polygon*> GetAllHitboxes();

	private:
		std::vector<std::unique_ptr<b2Polygon>> m_pHitboxVec{};
	};
}



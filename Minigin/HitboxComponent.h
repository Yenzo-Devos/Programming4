#pragma once
#include "BaseComponent.h"

#include <vector>
#include <memory>

namespace dae
{
	class HitboxComponent : public BaseComponent
	{
	public:
		struct Box {
			int left;
			int top;
			int width;
			int height;
		};

		HitboxComponent(GameObject* owner);
		~HitboxComponent() = default;
		
		HitboxComponent(const HitboxComponent& other) = delete;
		HitboxComponent(HitboxComponent&& other) = delete;
		HitboxComponent& operator=(const HitboxComponent& other) = delete;
		HitboxComponent& operator=(HitboxComponent&& other) = delete;

		virtual void Update(float) override {}

		void AddHitbox(int left, int top, int width, int height);
		std::vector<Box*> GetAllHitboxes();

	private:
		std::vector<std::unique_ptr<Box>> m_pHitboxVec{};
	};
}



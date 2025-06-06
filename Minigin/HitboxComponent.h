#pragma once
#include "BaseComponent.h"

#include <map>
#include <memory>
#include <string>

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
			int offsetLeft;
			int offsetTop;
		};

		HitboxComponent(GameObject* owner);
		~HitboxComponent() = default;
		
		HitboxComponent(const HitboxComponent& other) = delete;
		HitboxComponent(HitboxComponent&& other) = delete;
		HitboxComponent& operator=(const HitboxComponent& other) = delete;
		HitboxComponent& operator=(HitboxComponent&& other) = delete;

		virtual void Update(float) override {};
		void UpdateHitboxPosition();

		void AddHitbox(const std::string& identifier, int offsetLeft, int offsetTop, int width, int height);
		Box* GetHitbox(const std::string& identifier);

	private:
		std::map<std::string, std::unique_ptr<Box>> m_pHitboxMap{};
	};
}



#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

#include <memory>
#include <vector>
#include <glm.hpp>

namespace dae
{
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(dae::GameObject* owner, bool srcRectEnabled = false);
		~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
		
		struct Rect
		{
			int left;
			int bottom;
			int width;
			int height;
		};

		struct RenderObject
		{
			Rect dstRect;
			Rect srcRect;
			int offsetX;
			int offsetY;
		};

		void Render();
		void Update(float) override {};

		void SetTexture(Texture2D* pTexture);
		
		void AddObjectToRender(const Rect& dstRect, const Rect& srcRect = Rect{0,0,0,0}, int offsetX = 0, int offsetY = 0);
		void SetSourceRect(int index, const Rect& srcRect) { m_ObjectToRender[index].srcRect = srcRect; }

	private:
		bool m_SourceRectEnabled;

		std::vector<RenderObject> m_ObjectToRender;
		dae::Texture2D* m_pTexture{};
	};
}
#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{
	class RenderComponent : public BaseComponent
	{
		struct Rect
		{
			int left;
			int bottom;
			int width;
			int height;
		};

	public:
		RenderComponent(dae::GameObject* owner, bool srcRectEnabled = false);
		~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	
		void Render();
		void SetTexture(Texture2D* pTexture, int width, int height);
		void SetSourceRect(const Rect& srcRect) { m_SrcRect = srcRect; }

	private:
		bool m_SourceRectEnabled;
		int m_Width;
		int m_Heigth;
		Rect m_SrcRect;

		std::shared_ptr<dae::Texture2D> m_pTexture;
	};
}



#pragma once
#include "BaseComponent.h"
#include "imgui_plot.h"
#include <vector>

namespace engine
{
	class TrashTheCache : public BaseComponent
	{
	public:
		TrashTheCache(engine::GameObject* pOwner);
		virtual ~TrashTheCache();

		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache(TrashTheCache&& other) = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) = delete;

		virtual void Awake() override {};
		virtual void RenderUI() override;

	private:
		
		std::vector<float> m_StepsInfo;
		const int m_ContainerSize;
		ImColor m_Color1, m_Color2;
		const int m_MaxStepSize;

		void PlottingData(std::vector<float> data, ImColor color);

		int m_BenchmarkAmount;
		std::vector<float> m_IntAverage = std::vector<float>(11);
		void RenderEx1();
		void TrashTheCacheBenchmark(int benchmarkAmount);

		struct Transform
		{
			float matrix[16] =
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};

		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};

		class GameObject3DAlt
		{
		public:
			Transform* transform;
			int ID;
		};

		std::vector<float> m_GameObjectAverage = std::vector<float>(11);
		std::vector<float> m_AltGameObjectAverage = std::vector<float>(11);

		void RenderEx2();
		void GameObject3DTest(int benchmarkCount);
		void AltGameObject3DTest(int benchmarkCount);
	};
}


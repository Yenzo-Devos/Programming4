#pragma once
#include "BaseComponent.h"
#include "imgui.h"
#include "imgui_plot.h"

#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>

namespace dae
{
	class TrashTheCacheComponent : public BaseComponent
	{
		struct Matrix
		{
			float matrix[16] = {
					1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1 };
		};

		class TestObject3D
		{
		public:
			Matrix matrix;
			int id;
		};

		class AltTestObject3D
		{
		public:
			Matrix* matrix;
			int id;
		};

	public:
		TrashTheCacheComponent(GameObject* owner);
		~TrashTheCacheComponent() = default;

		TrashTheCacheComponent(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent(TrashTheCacheComponent&& other) = delete;
		TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other) = delete;

		virtual void Update(float) override {};
		void Render() override;

	private:
		// members for both exercises
		int m_NrOfBenchmarkRuns{};
		const int m_NrOfAllocatedObj{ 10'000'000 };
		std::vector<float> m_StepInfo{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
		ImColor m_Red{ 255, 0, 0 };
		ImColor m_Green{ 0, 255, 0 };
		ImColor m_Blue{ 0, 0, 255 };

		// functions for both exercises
		void PlotData(std::vector<float> data, ImColor color, std::string plotName);
		void PlotTwoLinesData(std::vector<std::vector<float>> data, std::vector<ImColor> colors, std::string plotName);
		std::vector<float> TakeAverages(std::vector<std::vector<long long>> times, int nrOfRuns);

		// exercise 1 members
		std::vector<float> m_IntAverages = std::vector<float>();

		// exercise 1 function
		void RenderEx1();
		void BenchmarkInts(int nrOfRuns);

		// exercise 2 members
		std::vector<float> m_TestObjectAverages = std::vector<float>();
		std::vector<float> m_AltTestObjectAverages = std::vector<float>();

		// exercise 2 functions
		void RenderEx2();
		void BenchmarkTestObjects(int nrOfRuns);
		void BenchmarkAltTestObjects(int nrOfRuns);
	};
}
#include "TrashTheCache.h"
#include "Renderer.h"

#include <algorithm>
#include <numeric>
#include <chrono>

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

using namespace std::chrono;

engine::TrashTheCache::TrashTheCache(engine::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_StepsInfo{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 }
	, m_ContainerSize{ 10000000 }
	, m_Color1{ 255, 0, 0 }
	, m_Color2{ 0, 0, 255 }
	, m_MaxStepSize{ 1024 }
	, m_BenchmarkAmount{ }
	, m_IntAverage{ }
{
	/*IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Renderer::GetInstance().GetWindow(), SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();*/
}

engine::TrashTheCache::~TrashTheCache()
{
	/*ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();*/
}

void engine::TrashTheCache::RenderUI()
{
	// RenderExercises
	RenderEx1();
	RenderEx2();
}

void engine::TrashTheCache::PlottingData(std::vector<float> data, ImColor color)
{
	static uint32_t selection_start = 0, selection_length = 0;

	float maxVal = *std::max_element(begin(data), end(data));
	float minVal = *std::min_element(begin(data), end(data));


	// GRAPH
	ImGui::PlotConfig plotConfig{};

	plotConfig.values.xs = m_StepsInfo.data();
	plotConfig.values.count = (int)m_StepsInfo.size() + 1;
	plotConfig.values.ys = data.data();
	plotConfig.values.color = color;
	plotConfig.scale.min = minVal;
	plotConfig.scale.max = maxVal;
	plotConfig.tooltip.show = true;
	plotConfig.tooltip.format = "x=%.2f, y=%.2f";
	plotConfig.grid_x.show = true;
	plotConfig.grid_x.size = 200;
	plotConfig.grid_x.subticks = 4;
	plotConfig.grid_y.show = true;
	plotConfig.grid_y.size = maxVal / 10.f;
	plotConfig.grid_y.subticks = 5;
	plotConfig.selection.show = true;
	plotConfig.selection.start = &selection_start;
	plotConfig.selection.length = &selection_length;
	plotConfig.frame_size = ImVec2(200, 100);

	ImGui::Plot("plot", plotConfig);
}

void engine::TrashTheCache::RenderEx1()
{
	ImGui::Begin("Exercise 1");

	ImGui::InputInt("# samples", &m_BenchmarkAmount);
	if (m_BenchmarkAmount < 1)
		m_BenchmarkAmount = 1;
	if (ImGui::Button("Trash the cache!"))
		TrashTheCacheBenchmark(m_BenchmarkAmount);
	if (m_IntAverage.size() > 0)
		PlottingData(m_IntAverage, m_Color1);

	ImGui::End();
}

void engine::TrashTheCache::TrashTheCacheBenchmark(int benchmarkAmount)
{
	std::vector<int> intArr(m_ContainerSize, int{});
	
	std::vector<std::vector<long long>> elapsedTimes(m_StepsInfo.size(), std::vector<long long>(benchmarkAmount));

	for (int index{ 0 }; index < benchmarkAmount; ++index)
	{
		int idx{ 0 };
		for (int stepSize = 1; stepSize <= m_MaxStepSize; stepSize *= 2)
		{
			auto startTime = high_resolution_clock::now();

			for (int i{ 1 }; i < m_ContainerSize; i += stepSize)
			{
				intArr[i] *= 2;
			}

			auto endTime = high_resolution_clock::now();
			auto elapsedTime = duration_cast<microseconds>(endTime - startTime).count();
			elapsedTimes[idx++][index] = elapsedTime;
		}
	}

	int stepSize{ 1 };
	std::vector<float> averages;
	for (int i{ 0 }; i < int(m_StepsInfo.size()); i++)
	{
		std::sort(elapsedTimes[i].begin(), elapsedTimes[i].end());
		if (m_BenchmarkAmount != 1)
		{
			elapsedTimes[i].erase(elapsedTimes[i].begin());
		}

		float average = std::accumulate(elapsedTimes[i].begin(), elapsedTimes[i].end(), 0.f) / elapsedTimes[i].size();

		stepSize *= 2;
		averages.push_back(average);
	}
	m_IntAverage = averages;
}

void engine::TrashTheCache::RenderEx2()
{
	static uint32_t selection_start = 0, selection_length = 0;
	ImGui::Begin("Exercise 2");

	ImGui::InputInt("# samples", &m_BenchmarkAmount);
	if (m_BenchmarkAmount < 1)
		m_BenchmarkAmount = 1;

	if (ImGui::Button("Trash the cache with gameobject!"))
		GameObject3DTest(m_BenchmarkAmount);

	if (m_GameObjectAverage.size() > 0)
		PlottingData(m_GameObjectAverage, m_Color1);

	if (ImGui::Button("Trash the cache with altered gameObject!"))
		AltGameObject3DTest(m_BenchmarkAmount);

	if (m_AltGameObjectAverage.size() > 0)
		PlottingData(m_AltGameObjectAverage, m_Color2);

	// Graph 3	
	const ImU32 colors[2] = { m_Color1, m_Color2 };

	const float maxVal = std::max(*std::max_element(begin(m_GameObjectAverage), end(m_GameObjectAverage)), *std::max_element(begin(m_AltGameObjectAverage), end(m_AltGameObjectAverage)));
	const float minVal = std::min(*std::min_element(begin(m_GameObjectAverage), end(m_GameObjectAverage)), *std::min_element(begin(m_AltGameObjectAverage), end(m_AltGameObjectAverage)));

	const float* data[2] = { m_GameObjectAverage.data(), m_AltGameObjectAverage.data() };

	ImGui::PlotConfig plotConfig;

	plotConfig.values.xs = m_StepsInfo.data();;
	plotConfig.values.count = (int)m_StepsInfo.size() + 1;
	plotConfig.values.ys_list = data;
	plotConfig.values.ys_count = 2;
	plotConfig.values.colors = colors;
	plotConfig.scale.min = minVal;
	plotConfig.scale.max = maxVal;
	plotConfig.tooltip.show = true;
	plotConfig.tooltip.format = "x=%.2f, y=%.2f";
	plotConfig.grid_x.show = true;
	plotConfig.grid_x.size = 200;
	plotConfig.grid_x.subticks = 4;
	plotConfig.grid_y.show = true;
	plotConfig.grid_y.size = maxVal / 10.f;
	plotConfig.grid_y.subticks = 5;
	plotConfig.selection.show = true;
	plotConfig.selection.start = &selection_start;
	plotConfig.selection.length = &selection_length;
	plotConfig.frame_size = ImVec2(200, 100);

	ImGui::Plot("Combined Graphs", plotConfig);

	ImGui::End();
}

void engine::TrashTheCache::GameObject3DTest(int benchmarkCount)
{
	std::vector<GameObject3D> objectVector( (size_t)m_ContainerSize, GameObject3D{} );
	std::vector<std::vector<long long>> elapsedTimes(m_StepsInfo.size(), std::vector<long long>(benchmarkCount));

	for (int index{ 0 }; index < benchmarkCount; ++index)
	{
		int idx{ 0 };
		for (int stepSize = 1; stepSize < m_MaxStepSize; stepSize *= 2)
		{
			auto startTime = high_resolution_clock::now();

			for (int i{ 1 }; i < m_ContainerSize; i += stepSize)
			{
				objectVector[i].ID *= 2;
			}

			auto endTime = high_resolution_clock::now();
			auto elapsedTime = duration_cast<microseconds>(endTime - startTime).count();
			elapsedTimes[idx++][index] = elapsedTime;
		}
	}

	int stepSize{ 1 };
	std::vector<float> averages;
	for (int i{ 0 }; i < int(m_StepsInfo.size()); i++)
	{
		std::sort(elapsedTimes[i].begin(), elapsedTimes[i].end());

		if (benchmarkCount != 1)
			elapsedTimes[i].erase(elapsedTimes[i].begin());
		//elapsedTimes[i].pop_back();

		float average = std::accumulate(elapsedTimes[i].begin(), elapsedTimes[i].end(), 0.f) / elapsedTimes[i].size();

		stepSize *= 2;
		averages.push_back(average);
	}

	m_GameObjectAverage = averages;
}

void engine::TrashTheCache::AltGameObject3DTest(int benchmarkCount)
{
	std::vector<GameObject3DAlt> objectVector( (size_t)m_ContainerSize, GameObject3DAlt{} );
	std::vector<std::vector<long long>> elapsedTimes(m_StepsInfo.size(), std::vector<long long>(benchmarkCount));

	for (int index{ 0 }; index < benchmarkCount; ++index)
	{
		int idx{ 0 };
		for (int stepSize = 1; stepSize < m_MaxStepSize; stepSize *= 2)
		{
			auto startTime = high_resolution_clock::now();

			for (int i{ 1 }; i < m_ContainerSize; i += stepSize)
			{
				objectVector[i].ID *= 2;
			}

			auto endTime = high_resolution_clock::now();
			auto elapsedTime = duration_cast<microseconds>(endTime - startTime).count();
			elapsedTimes[idx++][index] = elapsedTime;
		}
	}

	int stepSize{ 1 };
	std::vector<float> averages;
	for (int i{ 0 }; i < int(m_StepsInfo.size()); i++)
	{
		std::sort(elapsedTimes[i].begin(), elapsedTimes[i].end());

		if (benchmarkCount != 1)
			elapsedTimes[i].erase(elapsedTimes[i].begin());
		//elapsedTimes[i].pop_back();

		float average = std::accumulate(elapsedTimes[i].begin(), elapsedTimes[i].end(), 0.f) / elapsedTimes[i].size();

		stepSize *= 2;
		averages.push_back(average);
	}

	m_AltGameObjectAverage = averages;
}

#include "TrashTheCacheComponent.h"

dae::TrashTheCacheComponent::TrashTheCacheComponent(GameObject* owner)
	: BaseComponent(owner)
{
}

void dae::TrashTheCacheComponent::Render()
{
	RenderEx1();
	RenderEx2();
}

void dae::TrashTheCacheComponent::PlotData(std::vector<float> data, ImColor color, std::string plotName)
{
	static uint32_t selection_start = 0, selection_length = 0;
	float minVal = *std::min_element(data.begin(), data.end());
	float maxVal = *std::max_element(data.begin(), data.end());
	
	ImGui::PlotConfig conf;
	conf.values.xs = m_StepInfo.data();
	conf.values.count = static_cast<int>(m_StepInfo.size());
	conf.values.ys = data.data();
	conf.values.color = color;
	conf.scale.min = minVal;
	conf.scale.max = maxVal;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_x.size = 200;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = maxVal / 10.f;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(200, 100);
	ImGui::Plot(plotName.c_str(), conf);
}

void dae::TrashTheCacheComponent::PlotTwoLinesData(std::vector<std::vector<float>> data, std::vector<ImColor> colors, std::string plotName)
{
	uint32_t selection_start = 0, selection_length = 0;
	const float* yData[2] = { data[0].data(), data[1].data() };
	ImU32 colorArr[2] = { colors[0], colors[1] };

	float minVal = std::min(*std::min_element(data[0].begin(), data[0].end()), *std::min_element(data[1].begin(), data[1].end()));
	float maxVal = std::max(*std::max_element(data[0].begin(), data[0].end()), *std::max_element(data[1].begin(), data[1].end()));

	ImGui::PlotConfig conf;
	conf.values.xs = m_StepInfo.data();
	conf.values.count = static_cast<int>(m_StepInfo.size());
	conf.values.ys_list = yData;
	conf.values.ys_count = 2;
	conf.values.colors = colorArr;
	conf.scale.min = minVal;
	conf.scale.max = maxVal;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_x.size = 200;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = maxVal / 10.f;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(200, 100);
	ImGui::Plot(plotName.c_str(), conf);
}

std::vector<float> dae::TrashTheCacheComponent::TakeAverages(std::vector<std::vector<long long>> times, int nrOfRuns)
{
	std::vector<float> bufferAverages{};
	for (int index{ 0 }; index < static_cast<int>(m_StepInfo.size()); ++index)
	{
		std::sort(times[index].begin(), times[index].end());
		if (nrOfRuns > 2)
		{
			times[index].erase(times[index].begin());
			times[index].pop_back();
		}

		float average = std::accumulate(times[index].begin(), times[index].end(), 0.f) / static_cast<float>(times[index].size());
		bufferAverages.emplace_back(average);
	}
	return bufferAverages;
}

void dae::TrashTheCacheComponent::RenderEx1()
{
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_NrOfBenchmarkRuns);
	if (m_NrOfBenchmarkRuns < 1)
		m_NrOfBenchmarkRuns = 1;
	if (ImGui::Button("Trash the cache"))
		BenchmarkInts(m_NrOfBenchmarkRuns);
	if (m_IntAverages.size() > 0)
		PlotData(m_IntAverages, m_Red, "IntPlot");
	ImGui::End();
}

void dae::TrashTheCacheComponent::BenchmarkInts(int nrOfRuns)
{
	std::vector<int> arr(m_NrOfAllocatedObj, int{});
	std::vector<std::vector<long long>> elapsedTimes(m_StepInfo.size(), std::vector<long long>(nrOfRuns));
	
	for (int index = 0; index < nrOfRuns; ++index)
	{
		int count{ 0 };
		for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arr.size(); i += stepSize)
				arr[i] *= 2;

			auto endTime = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
			elapsedTimes[count++][index] = elapsedTime;
		}
	}

	m_IntAverages = TakeAverages(elapsedTimes, nrOfRuns);
}

void dae::TrashTheCacheComponent::RenderEx2()
{
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# samples", &m_NrOfBenchmarkRuns);
	
	if (ImGui::Button("Trash the cache with TestObject3D"))
		BenchmarkTestObjects(m_NrOfBenchmarkRuns);
	
	if (m_TestObjectAverages.size() > 0)
		PlotData(m_TestObjectAverages, m_Green, "TestObjectPlot");
	
	if (ImGui::Button("Trash the cache with Alt TestObject3D"))
		BenchmarkAltTestObjects(m_NrOfBenchmarkRuns);
	
	if (m_AltTestObjectAverages.size() > 0)
		PlotData(m_AltTestObjectAverages, m_Blue, "AltTestObjectPlot");
	
	if (m_TestObjectAverages.size() > 0 &&
		m_AltTestObjectAverages.size() > 0)
	{
		std::vector<std::vector<float>> data = { m_TestObjectAverages, m_AltTestObjectAverages };
		std::vector<ImColor> colors = { m_Green, m_Blue };
		PlotTwoLinesData(data, colors, "Combined Graph");
	}
	ImGui::End();
}

void dae::TrashTheCacheComponent::BenchmarkTestObjects(int nrOfRuns)
{
	std::vector<TestObject3D> arr(m_NrOfAllocatedObj, TestObject3D{});
	std::vector<std::vector<long long>> elapsedTimes(m_StepInfo.size(), std::vector<long long>(nrOfRuns));

	for (int index = 0; index < nrOfRuns; ++index)
	{
		int count{ 0 };
		for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arr.size(); i += stepSize)
				arr[i].id *= 2;
			auto endTime = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
			elapsedTimes[count++][index] = elapsedTime;
		}
	}

	m_TestObjectAverages = TakeAverages(elapsedTimes, nrOfRuns);
}

void dae::TrashTheCacheComponent::BenchmarkAltTestObjects(int nrOfRuns)
{
	std::vector<AltTestObject3D> arr(m_NrOfAllocatedObj, AltTestObject3D{});
	std::vector<std::vector<long long>> elapsedTimes(m_StepInfo.size(), std::vector<long long>(nrOfRuns));

	for (int index = 0; index < nrOfRuns; ++index)
	{
		int count{ 0 };
		for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arr.size(); i += stepSize)
				arr[i].id *= 2;

			auto endTime = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
			elapsedTimes[count++][index] = elapsedTime;
		}
	}

	m_AltTestObjectAverages = TakeAverages(elapsedTimes, nrOfRuns);
}

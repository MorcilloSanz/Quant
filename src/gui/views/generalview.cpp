#include "generalview.h"

#include "ticker/tickerdata.h"

namespace quant
{

GeneralView::GeneralView()
    : View() {
}

void GeneralView::window() {

    TickerData& tickerData = TickerData::getInstance();
    int total = static_cast<int>(tickerData.getClose().size());

    ImGui::Begin("General");

    static int currentRange = 0;
    if (ImGui::RadioButton("1D", currentRange == 0)) currentRange = 0; ImGui::SameLine();
    if (ImGui::RadioButton("1M", currentRange == 1)) currentRange = 1; ImGui::SameLine();
    if (ImGui::RadioButton("1Y", currentRange == 2)) currentRange = 2; ImGui::SameLine();
    if (ImGui::RadioButton("2Y", currentRange == 3)) currentRange = 3; ImGui::SameLine();
    if (ImGui::RadioButton("5Y", currentRange == 4)) currentRange = 4; ImGui::SameLine();
    if (ImGui::RadioButton("MAX", currentRange == 5)) currentRange = 5;

    int samples[6] = {10, 31, 365, 730, 1825, total}; 

    int count = samples[currentRange];
    if(count < tickerData.getT().size())
        count = static_cast<int>(tickerData.getT().size());

    int start = total - count;

    ImVec2 size = ImGui::GetContentRegionAvail();
    size.y = 3.f * size.y / 4.f;

    if (ImPlot::BeginSubplots(tickerData.getTicker().c_str(), 1, 2, size)) {

        // Plot prices
        double xMin = tickerData.getT()[start]; 
        double xMax = tickerData.getT()[start + count - 1];

        double yMin = tickerData.getOpen()[start];
        double yMax = tickerData.getOpen()[start];

        for (int i = start; i < start + count; ++i) {
            yMin = std::min(yMin, tickerData.getOpen()[i]);
            yMin = std::min(yMin, tickerData.getHigh()[i]);
            yMin = std::min(yMin, tickerData.getLow()[i]);
            yMin = std::min(yMin, tickerData.getClose()[i]);

            yMax = std::max(yMax, tickerData.getOpen()[i]);
            yMax = std::max(yMax, tickerData.getHigh()[i]);
            yMax = std::max(yMax, tickerData.getLow()[i]);
            yMax = std::max(yMax, tickerData.getClose()[i]);
        }

        ImPlot::SetNextAxisLimits(ImAxis_X1, xMin, xMax, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, yMin, yMax, ImGuiCond_Always);

        if (ImPlot::BeginPlot("Price")) {
            ImPlot::PlotLine("Open", &tickerData.getT()[0] + start, &tickerData.getOpen()[0] + start, count);
            ImPlot::PlotLine("High", &tickerData.getT()[0] + start, &tickerData.getHigh()[0] + start, count);
            ImPlot::PlotLine("Low", &tickerData.getT()[0] + start, &tickerData.getLow()[0] + start, count);
            ImPlot::PlotLine("Close", &tickerData.getT()[0] + start, &tickerData.getClose()[0] + start, count);
            ImPlot::EndPlot();
        }

        // Plot Volume
        double volMin = 0.0;
        double volMax = tickerData.getVolume()[start];
        for (int i = start; i < start + count; ++i)
            volMax = std::max(volMax, tickerData.getVolume()[i]);

        ImPlot::SetNextAxisLimits(ImAxis_X1, xMin, xMax, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, volMin, volMax, ImGuiCond_Always);

        if (ImPlot::BeginPlot("Volume")) {
            ImPlot::PlotBars("Volume", &tickerData.getT()[0] + start, &tickerData.getVolume()[0] + start, count, 2);
            ImPlot::EndPlot();
        }

        ImPlot::EndSubplots();
    }
    
    ImGui::End();
}

}
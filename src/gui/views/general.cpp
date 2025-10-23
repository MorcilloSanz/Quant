#include "general.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

constexpr int total = 1000;

double t[total];
double open[total];
double high[total];
double low[total];
double close[total];
double volume[total];

bool initialized = false;

// Number of samples for each time range (1D, 1M, 1Y...)
int samples[6] = {10, 100, 200, 500, 800, total}; 

double random_range(double min, double max) {
    return min + (max - min) * (rand() / (double)RAND_MAX);
}

namespace quant
{

void generalWindow() {

    // Init time series
    if(!initialized) {

        double price = 100.0;

        for (int i = 0; i < total; ++i) {

            t[i] = i;

            // Simular una variación diaria tipo random walk
            double drift = random_range(-0.02, 0.02);  // cambio porcentual diario
            price *= (1.0 + drift);

            // Simular los valores OHLC con pequeñas fluctuaciones alrededor de "price"
            double daily_range = price * random_range(0.005, 0.02);  // rango diario (0.5% a 2%)

            open[i]  = price * (1.0 + random_range(-0.005, 0.005));
            close[i] = price * (1.0 + random_range(-0.005, 0.005));
            high[i]  = std::max(open[i], close[i]) + daily_range * random_range(0.3, 1.0);
            low[i]   = std::min(open[i], close[i]) - daily_range * random_range(0.3, 1.0);

            // Simular volumen con algo de ruido periódico
            volume[i] = 1'000'000 + 200'000 * sin(i * 0.1) + random_range(-50'000, 50'000);
        }

        initialized = true;
    }

    static float f = 0.0f;
    static int counter = 0;
    ImGui::Begin("General");

    ImGui::Text("ABOUT THIS DEMO:");
    ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
    ImGui::BulletText("The \"Tools\" menu above gives access to: Style Editors (ImPlot/ImGui)\n"
                        "and Metrics (general purpose Dear ImGui debugging tool).");

    ImGui::Separator();

    static int currentRange = 0;
    if (ImGui::RadioButton("1D", currentRange == 0)) currentRange = 0; ImGui::SameLine();
    if (ImGui::RadioButton("1M", currentRange == 1)) currentRange = 1; ImGui::SameLine();
    if (ImGui::RadioButton("1Y", currentRange == 2)) currentRange = 2; ImGui::SameLine();
    if (ImGui::RadioButton("2Y", currentRange == 3)) currentRange = 3; ImGui::SameLine();
    if (ImGui::RadioButton("5Y", currentRange == 4)) currentRange = 4; ImGui::SameLine();
    if (ImGui::RadioButton("MAX", currentRange == 5)) currentRange = 5;

    int count = samples[currentRange];
    int start = total - count;

    ImVec2 size = ImGui::GetContentRegionAvail();
    size.y = 3.f * size.y / 4.f;

    if (ImPlot::BeginSubplots("NVDA", 1, 2, size)) {

        // Plot prices
        double xMin = t[start];
        double xMax = t[start + count - 1];

        double yMin = open[start];
        double yMax = open[start];

        for (int i = start; i < start + count; ++i) {
            yMin = std::min(yMin, open[i]);
            yMin = std::min(yMin, high[i]);
            yMin = std::min(yMin, low[i]);
            yMin = std::min(yMin, close[i]);

            yMax = std::max(yMax, open[i]);
            yMax = std::max(yMax, high[i]);
            yMax = std::max(yMax, low[i]);
            yMax = std::max(yMax, close[i]);
        }

        ImPlot::SetNextAxisLimits(ImAxis_X1, xMin, xMax, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, yMin, yMax, ImGuiCond_Always);

        if (ImPlot::BeginPlot("Price")) {
            ImPlot::PlotLine("Open", t + start, open + start, count);
            ImPlot::PlotLine("High", t + start, high + start, count);
            ImPlot::PlotLine("Low", t + start, low + start, count);
            ImPlot::PlotLine("Close", t + start, close + start, count);
            ImPlot::EndPlot();
        }

        // Plot volume
        double volMin = 0.0;
        double volMax = volume[start];
        for (int i = start; i < start + count; ++i)
            volMax = std::max(volMax, volume[i]);

        ImPlot::SetNextAxisLimits(ImAxis_X1, xMin, xMax, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, volMin, volMax, ImGuiCond_Always);

        if (ImPlot::BeginPlot("Volume")) {
            ImPlot::PlotBars("Volume", t + start, volume + start, count, 2);
            ImPlot::EndPlot();
        }

        ImPlot::EndSubplots();
    }
    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}
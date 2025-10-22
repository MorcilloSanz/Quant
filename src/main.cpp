#include <iostream>
#include <algorithm>

#include "window/window.h"
#include "gui/gui.h"

void generalWindow();
void candlestickWindow();
void geometricBrownianMotionWindow();
void indicatorsWindow();

constexpr int total = 1000;

double t[total];
double open[total];
double high[total];
double low[total];
double close[total];
double volume[total];

int samples[6] = {10, 100, 200, 500, 800, total}; // Number of samples for each time range (1D, 1M, 1Y...)

int main() {

    // Main window
    quant::Window window("Quant", 1080, 720);
    ImGuiIO& io = quant::initGui(window);

    // Init time series
    for (int i = 0; i < total; ++i) {
        t[i] = i;
        open[i] = 128 + i + cos(i);
        high[i] = open[i] + 2 % rand();
        low[i] = open[i] - 2 % rand();
        close[i] = open[i] + 3 % rand();
        volume[i] = 1000000 + 1000 * rand();
    }

    // Rendering
    window.setRenderingCallback([&](quant::Window* window) {

        bool p_open = true;
        quant::newFrameImGui();
        quant::dockSpace(&p_open);

        candlestickWindow();
        geometricBrownianMotionWindow();
        indicatorsWindow();
        generalWindow();

        quant::renderImGui(io, *window);
    });

    // Main Loop
    window.loop();
    quant::destroyImGui();

    return 0;
}

void generalWindow() {

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
    //size.y = 3 * size.y / 4;

    if (ImPlot::BeginSubplots("NVDA", 1, 2, size)) {

        // -------------------
        // Plot de precios (OHLC)
        // -------------------
        double x_min = t[start];
        double x_max = t[start + count - 1];

        double y_min = open[start];
        double y_max = open[start];

        for (int i = start; i < start + count; ++i) {
            y_min = std::min(y_min, open[i]);
            y_min = std::min(y_min, high[i]);
            y_min = std::min(y_min, low[i]);
            y_min = std::min(y_min, close[i]);

            y_max = std::max(y_max, open[i]);
            y_max = std::max(y_max, high[i]);
            y_max = std::max(y_max, low[i]);
            y_max = std::max(y_max, close[i]);
        }

        ImPlot::SetNextAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, y_min, y_max, ImGuiCond_Always);

        if (ImPlot::BeginPlot("Price")) {
            ImPlot::PlotLine("Open", t + start, open + start, count);
            ImPlot::PlotLine("High", t + start, high + start, count);
            ImPlot::PlotLine("Low", t + start, low + start, count);
            ImPlot::PlotLine("Close", t + start, close + start, count);
            ImPlot::EndPlot();
        }

        // -------------------
        // Plot de volumen
        // -------------------
        double vol_min = 0.0;
        double vol_max = volume[start];
        for (int i = start; i < start + count; ++i)
            vol_max = std::max(vol_max, volume[i]);

        ImPlot::SetNextAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, vol_min, vol_max, ImGuiCond_Always);

        if (ImPlot::BeginPlot("Volume")) {
            ImPlot::PlotBars("Volume", t + start, volume + start, count, 2);
            ImPlot::EndPlot();
        }

        ImPlot::EndSubplots();
    }
    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void candlestickWindow() {
    ImGui::Begin("Candlestick");
    ImGui::Text("Candlestick chart with the automatic detection of patterns");
    ImGui::End();
}

void geometricBrownianMotionWindow() {
    ImGui::Begin("Geometric Brownian Motion");
    ImGui::Text("SDE brownian motion and simulations");
    ImGui::End();
}

void indicatorsWindow() {
    ImGui::Begin("Indicators");
    ImGui::Text("Long, mid and short term trading indicators");
    ImGui::End();
}
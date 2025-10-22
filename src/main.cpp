#include <iostream>

#include "window/window.h"
#include "gui/gui.h"

void generalWindow();
void candlestickWindow();
void geometricBrownianMotionWindow();
void indicatorsWindow();

int main() {

    // Main window
    quant::Window window("Quant", 1080, 720);
    ImGuiIO& io = quant::initGui(window);

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

    static bool groupVisible = true;
    ImGui::Checkbox("Show group", &groupVisible);

    ImGui::SameLine();

    if(ImGui::Button("Test"))
        std::cout << "button" << std::endl;

    ImGui::Separator();

    static float xs1[1001], ys1[1001];
    for (int i = 0; i < 1001; ++i) {
        xs1[i] = i * 0.001f;
        ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
    }

    static double xs2[20], ys2[20];
    for (int i = 0; i < 20; ++i) {
        xs2[i] = i * 1/19.0f;
        ys2[i] = xs2[i] * xs2[i];
    }

    if (ImPlot::BeginPlot("Line Plots")) {
        ImPlot::SetupAxes("x","y");
        ImPlot::PlotLine("f(x)", xs1, ys1, 1001);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
        ImPlot::PlotLine("g(x)", xs2, ys2, 20,ImPlotLineFlags_Segments);
        ImPlot::EndPlot();
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
#include <iostream>

#include "window/window.h"
#include "gui/gui.h"

void generalWindow();
void candlestickWindow();
void geometricBrownianMotionWindow();
void indicatorsWindow();

static float xs1[1001], ys1[1001];
static float xs2[1001], ys2[1001];
static float xs3[1001], ys3[1001];
static float xs4[1001], ys4[1001];

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

    ImVec2 size = ImGui::GetContentRegionAvail();
    //size.y = 3 * size.y / 4;

    if (ImPlot::BeginSubplots("NVDA", 1, 2, size)) {

        for (int i = 0; i < 1001; ++i) {
            xs1[i] = i * 0.01f;
            ys1[i] = xs1[i] * sin(xs1[i]);

            xs2[i] = i * 0.01f;
            ys2[i] = xs2[i] * cos(xs2[i]);

            xs3[i] = i * 0.01f;
            ys3[i] = -xs2[i] * sin(xs2[i]);

            xs4[i] = i * 0.01f;
            ys4[i] = xs2[i] * tanh(xs3[i]);
        }
    
        // Open
        if (ImPlot::BeginPlot("Price")) {
            
            ImPlot::PlotLine("Open", xs1, ys1, 1001);
            ImPlot::PlotLine("High", xs2, ys2, 1001);
            ImPlot::PlotLine("Low", xs3, ys3, 1001);
            ImPlot::PlotLine("Close", xs4, ys4, 1001);

            ImPlot::EndPlot();
        }

        // Volume
        if (ImPlot::BeginPlot("Volume")) {
            static double xs4[100], ys4[100];
            for (int i = 0; i < 100; i += 2) {
                xs4[i] = i;
                ys4[i] = fabs(sin(xs4[i] * 0.1));
            }
            ImPlot::PlotBars("sin(x)", xs4, ys4, 100, 2);
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
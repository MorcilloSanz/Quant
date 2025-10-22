#include <iostream>

#include "window/window.h"
#include "gui.h"

void imguiMainWindow();

int main() {

    // Main window
    quant::Window window("Quant", 800, 600);

    window.setResizeCallback([&](quant::Window* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // GLEW
    if(glewInit() != GLEW_OK) {
        std::cout << "Failed to init GLEW" << std::endl;
        return -1;
    }

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    quant::initImGui(io, window);

    // Rendering
    window.setRenderingCallback([&](quant::Window* window) {

        // Clear
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool p_open = true;
        quant::dockSpace(&p_open);

        // Main window
        imguiMainWindow();

        // Render ImGui
        quant::renderImGui(io, *window);
    });

    window.loop();

    // Destroy contexts
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    return 0;
}

void imguiMainWindow() {

    static float f = 0.0f;
    static int counter = 0;
    ImGui::Begin("Main Window");

    ImGui::Text("ABOUT THIS DEMO:");
    ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
    ImGui::BulletText("The \"Tools\" menu above gives access to: Style Editors (ImPlot/ImGui)\n"
                        "and Metrics (general purpose Dear ImGui debugging tool).");

    ImGui::Separator();

    static bool groupVisible = true;
    ImGui::Checkbox("Show group", &groupVisible);

    ImGui::SameLine();

    if(ImGui::Button("Test")) {
        std::cout << "button" << std::endl;
    }

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
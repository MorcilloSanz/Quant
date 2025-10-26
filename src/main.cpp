#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <thread>

#include <filesystem>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#endif

#include "window/window.h"

#include "gui/gui.h"
#include "gui/views/generalview.h"
#include "gui/views/candlestick.h"
#include "gui/views/sde.h"
#include "gui/views/indicators.h"

#include "ticker/tickerdata.h"

#define HISTORY_FILE_NAME "history.csv"
#define TICKER_FILE_NAME "ticker.txt"

std::filesystem::path getExecutablePath();
std::string getExecutableDir();

int main() {

    // Load ticker data
    quant::TickerData& tickerData = quant::TickerData::getInstance();

    std::thread tickerThread([&]() {

        std::filesystem::path exePath = getExecutablePath();
        std::string dir = exePath.parent_path().string();

        tickerData.loadDataFromFile(dir + "/" + HISTORY_FILE_NAME);
        tickerData.loadInfoFromFile(dir + "/" + TICKER_FILE_NAME);

        std::cout << tickerData.getTicker() << std::endl;
        std::cout << tickerData.getSector() << std::endl;
    });

    // Main window
    quant::Window window("Quant", 1080, 720);
    ImGuiIO& io = quant::initGui(window);

    quant::GeneralView generalView;

    // Rendering
    window.setRenderingCallback([&](quant::Window* window) {

        bool p_open = true;
        quant::newFrameImGui();
        quant::dockSpace(&p_open);

        if(tickerData.isLoaded()) {
            quant::candlestickWindow();
            quant::geometricBrownianMotionWindow();
            quant::indicatorsWindow();
            generalView.window();
        }else{
            quant::spinnerWindow("Loading ticker data", 10.0f, 3.0f, IM_COL32(255, 255, 255, 255));
        }

        quant::renderImGui(io, *window);
    });

    // Main Loop
    window.loop();

    quant::destroyImGui();
    tickerThread.join();

    return 0;
}

std::filesystem::path getExecutablePath() {
#if defined(_WIN32)
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return std::filesystem::path(path);
#elif defined(__linux__)
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);
    path[count] = '\0';
    return std::filesystem::path(path);
#else
    return {};
#endif
}

std::string getExecutableDir() {
    std::filesystem::path exePath = getExecutablePath();
    return exePath.parent_path().string();
}
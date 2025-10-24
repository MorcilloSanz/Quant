#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "window/window.h"

#include "gui/gui.h"
#include "gui/views/generalview.h"
#include "gui/views/general.h"
#include "gui/views/candlestick.h"
#include "gui/views/sde.h"
#include "gui/views/indicators.h"

#include "ticker/tickerdata.h"

int main() {

    // Load ticker data
    quant::TickerData& tickerData = quant::TickerData::getInstance();

    std::thread tickerThread([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        tickerData.loadDataFromFile("history.csv");
        tickerData.loadInfoFromFile("ticker.txt");
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
            quant::generalWindow();
            //generalView.window();
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

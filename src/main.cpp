#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

#include "window/window.h"

#include "gui/gui.h"
#include "gui/views/general.h"
#include "gui/views/candlestick.h"
#include "gui/views/sde.h"
#include "gui/views/indicators.h"
#include "gui/views/tickerselectionview.h"

#include "util/curl.h"

int main() {

    quant::curl("https://dog.ceo/api/breeds/image/random > ticker.json");

    quant::TickerSelectionView tickerSelectionView;

    // Main window
    quant::Window window("Quant", 1080, 720);
    ImGuiIO& io = quant::initGui(window);

    // Rendering
    window.setRenderingCallback([&](quant::Window* window) {

        bool p_open = true;
        quant::newFrameImGui();
        quant::dockSpace(&p_open);

        if(tickerSelectionView.isSelected()) {
            quant::candlestickWindow();
            quant::geometricBrownianMotionWindow();
            quant::indicatorsWindow();
            quant::generalWindow();
        }else {
            tickerSelectionView.window();
        }

        quant::renderImGui(io, *window);
    });

    // Main Loop
    window.loop();
    quant::destroyImGui();

    return 0;
}

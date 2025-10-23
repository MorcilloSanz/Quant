#include "candlestick.h"

#include "gui/gui.h"

namespace quant
{

void candlestickWindow() {
    ImGui::Begin("Candlestick");
    ImGui::Text("Candlestick chart with the automatic detection of patterns");
    ImGui::End();
}

}
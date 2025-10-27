#include "candlestickview.h"

#include "gui/gui.h"

namespace quant {

CandlestickView::CandlestickView()
    : View() {
}

void CandlestickView::window() {
    ImGui::Begin("Candlestick");
    ImGui::Text("Candlestick chart with the automatic detection of patterns");
    ImGui::End();
}

}
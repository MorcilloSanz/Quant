#include "tickerselectionview.h"

namespace quant
{

TickerSelectionView::TickerSelectionView()
    : selected(false) {
}

void TickerSelectionView::window() {

    ImGui::Begin("Ticker selection");

    static char text[128] = "";
    ImGui::Text("Enter the ticker name:");
    ImGui::InputText("Ticker", text, IM_ARRAYSIZE(text));

    ImGui::SameLine();

    if(ImGui::Button("Accept")) {
        selected = true;

        // Load ticker information
    }

    ImGui::End();
}


}
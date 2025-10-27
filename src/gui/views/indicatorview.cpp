#include "indicatorview.h"

#include "gui/gui.h"

namespace quant {

IndicatorView::IndicatorView()
    : View() {
}

void IndicatorView::window() {
    ImGui::Begin("Indicators");
    ImGui::Text("Long, mid and short term trading indicators");
    ImGui::End();
}

}
#include "sdeview.h"

#include "gui/gui.h"

namespace quant {

SDEView::SDEView()
    : View() {
}

void SDEView::window() {
    ImGui::Begin("Geometric Brownian Motion");
    ImGui::Text("SDE brownian motion and simulations");
    ImGui::End();
}

}
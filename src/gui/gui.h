#pragma once

#include "window/window.h"
#include "styles.h"

#ifndef IMPLOT_DISABLE_OBSOLETE_FUNCTIONS
#define IMPLOT_DISABLE_OBSOLETE_FUNCTIONS
#endif

#include <implot/implot.h>

namespace quant
{

void initImGui(ImGuiIO& io, const Window& window);
ImGuiIO& initGui(const Window& window);

void dockSpace(bool* p_open);
void newFrameImGui();

void renderImGui(ImGuiIO& io, const Window& window);
void destroyImGui();

}
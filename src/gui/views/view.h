#pragma once

#include "gui/gui.h"

namespace quant
{

class View {
public:
    View() = default;
    ~View() = default;
public:
    virtual void window() = 0;
};

}
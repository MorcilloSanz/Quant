#pragma once

#include <iostream>
#include <vector>

#include "view.h"

namespace quant
{

class IndicatorView : public View {
public:
    IndicatorView();
    ~IndicatorView() = default;
public:
    void window() override;
};

}
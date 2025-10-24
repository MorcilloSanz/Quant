#pragma once

#include <iostream>
#include <vector>

#include "view.h"

namespace quant
{

class GeneralView : public View {
public:
    GeneralView();
    ~GeneralView() = default;
public:
    void window() override;
};

}
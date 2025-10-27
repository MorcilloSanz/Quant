#pragma once

#include <iostream>
#include <vector>

#include "view.h"

namespace quant
{

class SDEView : public View {
public:
    SDEView();
    ~SDEView() = default;
public:
    void window() override;
};

}
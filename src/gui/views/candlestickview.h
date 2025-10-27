#pragma once

#include <iostream>
#include <vector>

#include "view.h"

namespace quant
{

class CandlestickView : public View {
public:
    CandlestickView();
    ~CandlestickView() = default;
public:
    void window() override;
};

}
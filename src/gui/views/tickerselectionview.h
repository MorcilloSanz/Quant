#pragma once

#include "view.h"

namespace quant
{

class TickerSelectionView : public View {
private:
    bool selected;
public:
    TickerSelectionView();
    ~TickerSelectionView() = default;
public:
    void window() override;
public:
    inline bool isSelected() const {
        return selected;
    }
};

}
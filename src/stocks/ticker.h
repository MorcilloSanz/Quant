#pragma once

#include <iostream>
#include <vector>

struct TickerData {
    std::vector<double> open, high, low, close;
    std::vector<double> volume;
    std::vector<double> bollingerTop, bollingerMid, bollingerBot;
};

TickerData loadTickerData() {
    
}
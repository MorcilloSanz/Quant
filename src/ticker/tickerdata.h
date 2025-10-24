#pragma once

#include <iostream>
#include <vector>

namespace quant
{

class TickerData {
private:
    std::vector<double> t;
    std::vector<double> open;
    std::vector<double> high;
    std::vector<double> low;
    std::vector<double> close;
    std::vector<double> volume;
    std::string ticker;
    bool loaded;
private:
    TickerData();
    ~TickerData() = default;
public:
    TickerData(const TickerData&) = delete;
    TickerData& operator=(const TickerData&) = delete;
public:
    static TickerData& getInstance() {
        static TickerData instance;
        return instance;
    }
public:
    void loadDataFromFile(const std::string& file);
    void loadInfoFromFile(const std::string& file);
public:
    inline const std::vector<double>& getT() {
        return t;
    }

    inline const std::vector<double>& getOpen() {
        return open;
    }

    inline const std::vector<double>& getHigh() {
        return high;
    }

    inline const std::vector<double>& getLow() {
        return low;
    }

    inline const std::vector<double>& getClose() {
        return close;
    }

    inline const std::vector<double>& getVolume() {
        return volume;
    }

    inline const std::string& getTicker() {
        return ticker;
    }

    inline bool isLoaded() const {
        return loaded;
    }
};

}
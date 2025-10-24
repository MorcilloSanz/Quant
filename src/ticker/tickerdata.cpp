#include "tickerdata.h"

namespace quant
{

TickerData::TickerData()
    : ticker("Test"), loaded(false) {
}

void TickerData::loadDataFromFile(const std::string& file) {


    loaded = true;
}

void TickerData::loadInfoFromFile(const std::string& file) {

}

}
#include "tickerdata.h"

#include <fstream>
#include <string>

#include "util/split.h"
#include "util/csv.h"

namespace quant
{

TickerData::TickerData()
    : ticker(""), sector(""), loaded(false) {
}

void TickerData::loadDataFromFile(const std::string& file) {

    CSVReader reader(file);

    for (int i = 0; i < reader.getGridWidth(); i++) {
        for (int j = 0; j < reader.getGridHeight(); j++) {
            
            std::string value = reader.getCell(i, j);

        }
    }

    loaded = true;
}

void TickerData::loadInfoFromFile(const std::string& file) {

    std::ifstream f(file);

    if(f.is_open()) {

        std::string line;

        int index = 0;
        while (getline(f, line)) {

            if(index == 0)
                ticker = line;
            else if(index == 1)
                sector = line;

            index ++;
        }

        f.close();
    }
}

}
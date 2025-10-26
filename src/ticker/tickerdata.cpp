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

    for(int j = 0; j < reader.getGridHeight(); j ++) {

        if(j == 0)
            continue;

        std::string date = reader.getCell(HISTORY_COLUMN_DATE, j);
        date = split(date, " ")[0];

        t.push_back(j - 1);
        dates.push_back(date);
        open.push_back(std::stod(reader.getCell(HISTORY_COLUMN_OPEN, j)));
        high.push_back(std::stod(reader.getCell(HISTORY_COLUMN_HIGH, j)));
        low.push_back(std::stod(reader.getCell(HISTORY_COLUMN_LOW, j)));
        close.push_back(std::stod(reader.getCell(HISTORY_COLUMN_CLOSE, j)));
        volume.push_back(std::stod(reader.getCell(HISTORY_COLUMN_VOLUME, j)));
    }

    if(!dates.empty())
        dates[dates.size() - 1] = "Now";

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
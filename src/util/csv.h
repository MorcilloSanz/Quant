/*
    USAGE:

    CSVReader csvReader(csvPath);
    for (int i = 0; i < csvReader.getGridWidth(); i++) {
        for (int j = 0; j < csvReader.getGridHeight(); j++) {
            std::string value = csvReader.getCell(i, j);
        }
    }
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "split.h"

#define CSV_DELIMITER ","

class CSVReader {
private:
    std::string filePath;
    std::vector<std::vector<std::string>> cellBuffer;
    unsigned int gridWidth, gridHeight;
public:
    CSVReader(const std::string& _filePath)
        : filePath(_filePath), gridWidth(0), gridHeight(0) {
        loadFile();
    }
    CSVReader() = default;
    ~CSVReader() = default;
private:
    void loadFile() {

        std::ifstream file(filePath);

        if (file.is_open()) {
            
            std::string line;
            while (getline(file, line)) {

                std::vector<std::string> splitted = split(line, std::string(CSV_DELIMITER));
                cellBuffer.push_back(splitted);

                if (splitted.size() > gridWidth) 
                    gridWidth = splitted.size();

                gridHeight++;
            }
            
            file.close();
        }
    }
public:
    std::string getCell(unsigned int x, unsigned int y) {
        std::vector<std::string> cells = cellBuffer[y];
        return cells[x];
    }

    inline std::string& getFilePath() {
        return filePath;
    }

    inline unsigned int getGridWidth() const {
        return gridWidth;
    }

    inline unsigned int getGridHeight() const {
        return gridHeight;
    }
};
#pragma once

#include <iostream>
#include <string>
#include <vector>

bool delimiterAt(const std::string& str, const std::string& delimiter, unsigned int index) {

    std::string delimiterBuff = "";
    for (int i = index; i < str.size(); i++) {

        delimiterBuff += str[i];
        if (delimiterBuff == delimiter)
            return true;
        else if (delimiterBuff.size() > delimiter.size())
            return false;
    }
    
    return false;
};

std::vector<std::string> split(const std::string& str, const std::string& delimiter) {

    std::string buff = "";
    std::vector<std::string> splitted;

    for (int i = 0; i < str.size(); i++) {

        if (!delimiterAt(str, delimiter, i)) 
            buff += str[i];
        else {
            splitted.push_back(buff);
            i += delimiter.size() - 1;
            buff = "";
        }

        if (i >= str.size() - 1) 
            splitted.push_back(buff);
    }

    return splitted;
}
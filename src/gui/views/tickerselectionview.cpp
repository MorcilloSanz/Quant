#include "tickerselectionview.h"

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

namespace quant
{

TickerSelectionView::TickerSelectionView()
    : selected(false) {
}

void TickerSelectionView::window() {

    ImGui::Begin("Ticker selection");

    static char text[128] = "";
    ImGui::Text("Enter the ticker name:");
    ImGui::InputText("Ticker", text, IM_ARRAYSIZE(text));

    ImGui::SameLine();

    if(ImGui::Button("Accept")) {
        
        std::string ticker(text);
        std::transform(ticker.begin(), ticker.end(), ticker.begin(),
                   [](unsigned char c){ return std::toupper(c); });

        std::ostringstream oss;
        oss << "curl -L -o ticker.csv \"https://query1.finance.yahoo.com/v7/finance/download/";
        oss << ticker;
        oss << "?period1=0&period2=9999999999&interval=1d&events=history\"";

        std::string command = oss.str();
        std::cout << command << std::endl;

        int ret = system(command.c_str());
        if(ret != 0){
            std::cerr << "Couldn't execute curl\n";
        }

        selected = true;
    }

    ImGui::End();
}


}
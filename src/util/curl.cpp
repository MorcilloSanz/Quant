#include "curl.h"

#include <sstream>

namespace quant
{

int curl(const std::string& command) {

    std::ostringstream oss;
    oss << "curl " << command;
    
    return system(oss.str().c_str());
}

}
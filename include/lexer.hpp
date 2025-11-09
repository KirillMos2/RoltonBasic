#pragma once

#include <vector>
#include <string>

namespace lexer {
    typedef struct {
        std::string type;
        std::string value;
    } token;

    std::vector<token> lexering(std::string code);
}

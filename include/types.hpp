#pragma once

#include <cstdlib>
#include <string>
#include <vector>

namespace rbl_types {
    typedef struct {
        std::string name;
        std::string type;
        std::string value;
    } var;
    typedef struct {
        std::string command;
        std::vector<std::string> args;
    } ast_type;
};

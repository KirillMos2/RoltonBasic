#pragma once

#include <cstdlib>
#include <string>
#include <vector>

#define PRINT_WORD tokens[0].type == "WORD" and tokens[0].value == "PRINT"
#define VARINT_WORD tokens[0].type == "WORD" and tokens[0].value == "VARINT"
#define VARSTR_WORD tokens[0].type == "WORD" and tokens[0].value == "VARSTR"
#define TYPE_WORD tokens[0].type == "WORD" and tokens[0].value == "TYPE"

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

#pragma once

#include <vector>
#include <string>
#include "types.hpp"

namespace compiler {
    bool in_vector(std::vector<std::string> vct, std::string find);
    std::string translating(std::vector<rbl_types::ast_type> ast, std::vector<rbl_types::var> vars);
}

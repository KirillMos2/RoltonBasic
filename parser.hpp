#pragma once

#include <vector>
#include "lexer.hpp"
#include "types.hpp"

namespace parser {
    rbl_types::ast_type parse(std::vector<lexer::token> tokens);
}

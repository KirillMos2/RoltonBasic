#include <cstdlib>
#include <iostream>
#include <string>
#include "types.hpp"

namespace compiler {
bool in_vector(std::vector<std::string> vct, std::string find) {
    for (int i = 0; i != vct.size(); i++) {
        if (find == vct[i]) return true;
    }
    return false;
}

std::string translating(std::vector<rbl_types::ast_type> ast, std::vector<rbl_types::var> vars) {
    std::vector<std::string> includes;
    std::string out = "int main() {\n";
    std::string ret = "";
    for (int i = 0; i != ast.size(); i++) {
        auto astt = ast[i];
        if (astt.command == "PRINT") {
            
            includes.push_back("<stdio.h>");
            includes.push_back("<stdlib.h>");
            out += "    printf(\"";
            if (astt.args[0] == "\"\"" && astt.args[(astt.args).size()-1] == "\"\"") {
                for (int i = 1; i != (astt.args).size()-1; i++) {
                    out += astt.args[i];
                }
                out += "\"";
            }
            else {
                if ((astt.args).size() == 1) {
                    int st = 0;
                    for (int i = 0; i != vars.size(); i++) {
                        if (vars[i].name == astt.args[0]) {
                            st = 1;
                            if (vars[i].type == "integer") {
                                out += "%d\", " + astt.args[0];
                            }
                            else if (vars[i].type == "string") {
                                out += "%s\", " + astt.args[0];
                            }
                        }
                    }
                    if (st == 0) {
                        std::cerr<<"You want "<<astt.args[0]<<" but it not created. List of vars:\n\n";
                        for (int h = 0; h != vars.size(); h++) {
                            std::cerr<<"Name: "<<vars[h].name<<"\nType: "<<vars[h].type<<"\nValue: "<<vars[h].value<<"\n\n";
                        }
                        exit(23);
                    }
                }
            }
            out += ");\n";
        }
        else if (astt.command == "VARINT") {
            out += "    int ";
            out += astt.args[0];
            out += " = ";
            out += astt.args[1];
            out += ";\n";
            vars.push_back({astt.args[0], "integer", astt.args[1]});
        }
        else if (astt.command == "VARSTR") {
            if (astt.args[1] == "\"\"" && astt.args[3] == "\"\"") {
                out += "    char ";
                out += astt.args[0];
                out += "[] = \"";
                out += astt.args[2];
                out += "\";\n";
                vars.push_back({astt.args[0], "string", astt.args[1]});
            }
            else {
                std::cerr<<"SYNTAX ERROR: not found quotes\n";
                exit(22);
            }
        }
        else if (astt.command == "TYPE") {
            out += "    // this function unsupported on C";
        }
    }
    out += "}";
    ret += includes;
    ret += "\n";
    ret += out;
    return ret;
}
};

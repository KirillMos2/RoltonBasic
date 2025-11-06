#include <cstdlib>
#include <string>
#include "types.hpp"

namespace compiler {
std::string translating(std::vector<rbl_types::ast_type> ast, std::vector<rbl_types::var> vars) {
    std::string includes = "";
    std::string out = "int main() {\n";
    std::string ret = "";
    for (int i = 0; i != ast.size(); i++) {
        auto astt = ast[i];
        if (astt.command == "PRINT") {
            includes += "\n#include <stdio.h>\n#include <stdlib.h>";
            out += "    printf(\"";
            if (astt.args[0] == "\"" && astt.args[(astt.args).size()-2] == "\"") {
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
                                out += "%%d\", " + astt.args[0];
                            }
                            else if (vars[i].type == "string") {
                                if (astt.args[0] == "SYSVERSION") {
                                    out += "%%s\", __VERSION__";
                                }
                                else {
                                    out += "%%s\", " + astt.args[0];
                                }
                            }
                        }
                        if (st == 0) {
                            std::cerr<<"You want "<<astt.args[0]<<" but it not created. List of vars:\n\n";
                            for (int h = 0; h != vars.size(); h++) {
                                std::cerr<<"Name: "<<vars[i].name<<"\nType: "<<vars[i].type<<"\nValue: "<<vars[i].value<<"\n\n";
                            }
                            exit(23);
                        }
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
            out += "    char[] ";
            out += astt.args[0];
            out += " = ";
            out += astt.args[1];
            out += ";\n";
            vars.push_back({astt.args[0], "string", astt.args[1]});
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

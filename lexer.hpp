#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#ifndef LEXER_H
#define LEXER_H

namespace lexer {
    typedef struct {
        std::string type;
        std::string value;
    } token;
    std::vector<token> lexering(std::string code) {
        std::vector<token> tokens;
        std::string buffer;
        int mod = 0;
        /*
        0 - буфер пустой
        1 - буквы
        2 - цифры
        */
        std::string buf = "";
        token newtoken;
        for (int i = 0; i != code.size(); i++) {
            char symb = code[i];
            if (!(std::isalpha(symb)) && mod == 1) {
                if (buf == "PRINT"
                ||  buf == "VARINT"
                ||  buf == "VARSTR"
                ||  buf == "TYPE"
                ||  buf == "INPUT"
                ||  buf == "SUM"
                ||  buf == "SUB"
                ) {
                    newtoken = {"KWORD", buf};
                    tokens.push_back(newtoken);
                    buf = "";
                    mod = 0;
                }
                else {
                    newtoken = {"WORD", buf};
                    tokens.push_back(newtoken);
                    buf = "";
                    mod = 0;
                }
            }
            else if (!(std::isalpha(symb)) && mod == 2) {
                newtoken = {"DIGIT", buf};
                tokens.push_back(newtoken);
                buf = "";
                mod = 0;
            }
            switch (symb) {
                case '=':
                    if (code[i+1] == '=') {
                        i++;
                        newtoken = {"EQUALS", "NONE"};
                        tokens.push_back(newtoken);
                    }
                    else {
                        newtoken = {"EQUAL", "NONE"};
                        tokens.push_back(newtoken);
                    }
                    break;
                case ' ':
                    newtoken = {"SPACE", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case '+':
                    newtoken = {"PLUS", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case '-':
                    newtoken = {"MINUS", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case '*':
                    newtoken = {"STAR", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case '%':
                    newtoken = {"MOD", "NONE"};
                    tokens.push_back(newtoken);
                    break; // FIXED ERROR 0xa0000001 from anonim user
                case '/':
                    newtoken = {"SLASH", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case '(':
                    newtoken = {"L_PAREN", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case ')':
                    newtoken = {"R_PAREN", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case '\'':
                case '\"':
                    newtoken = {"QUOTE", "NONE"};
                    tokens.push_back(newtoken);
                    break;
                case '\\':
                    if (code[i+1] == 'n') {
                        i++;
                        newtoken = {"SPECSYMBOL", "\n"};
                        tokens.push_back(newtoken);
                    }
                    else if (code[i+1] == 't') {
                        i++;
                        newtoken = {"SPECSYMBOL", "\t"};
                        tokens.push_back(newtoken);
                    }
                    else if (code[i+1] == 'v') {
                        i++;
                        newtoken = {"SPECSYMBOL", "\v"};
                        tokens.push_back(newtoken);
                    }
                    else {
                        std::cout<<std::endl<<"LEXERFAIL: Uwnkown symbol";
                        exit(10);
                    }
                    break;
                case '.':
                case ',':
                case '?':
                case '!':
                case '@':
                case '#':
                case '№':
                case '$':
                case ';':
                case '&':
                case '_':
                    buf += symb;
                    newtoken = {"SYMBOL", buf};
                    tokens.push_back(newtoken);
                    buf = "";
                    break;
                default:
                    if (std::isalpha(symb)) {
                        if (buf == "") {
                            buf += symb;
                            mod = 1;
                        }
                        else {
                            if (mod == 1) {
                                buf += symb;
                            }
                            else {
                                if (buf == "PRINT"
                                ||  buf == "VARINT"
                                ||  buf == "VARSTR"
                                ||  buf == "TYPE"
                                ||  buf == "INPUT"
                                ||  buf == "SUM"
                                ||  buf == "SUB"
                                ) {
                                    newtoken = {"KWORD", buf};
                                    tokens.push_back(newtoken);
                                    buf = "";
                                    mod = 0;
                                }
                                else {
                                    newtoken = {"WORD", buf};
                                    tokens.push_back(newtoken);
                                    buf = "";
                                    mod = 0;
                                }
                            }
                        }
                        break;
                    }
                    else if (std::isdigit(symb)){
                        if (buf == "") {
                            buf += symb;
                            mod = 2;
                        }
                        else {
                            if (mod == 2) {
                                buf += symb;
                            }
                            else {
                                newtoken = {"DIGIT", buf};
                                tokens.push_back(newtoken);
                                buf = "";
                                mod = 0;
                            }
                        }
                        break;
                    }
                    else {
                        buffer = "";
                        buffer += symb;
                        newtoken = {"SYMBOL", buffer};
                        tokens.push_back(newtoken);
                        break;
                    }
            }
        }
        if (buf != "") {
            if (mod == 1) {
                newtoken = {"WORD", buf};
            } else if (mod == 2) {
                newtoken = {"DIGIT", buf};
            }
            tokens.push_back(newtoken);
        }
        return tokens;
        
    }
};
#endif

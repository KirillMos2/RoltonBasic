#include "parser.hpp"
#include <iostream>

namespace parser {
    rbl_types::ast_type parse(std::vector<lexer::token> tokens) {
        std::cout<<"[PARSER LOG] INIT VARS\n";
        rbl_types::ast_type ast_vct;
        std::vector<lexer::token> cls_tks;
        std::vector<lexer::token> cls_tks2;
        int b = 0;
        int len = tokens.size();
        std::cout<<"[PARSER LOG] LIST ALL TOKENS\n";
        for (int i = 0; i != tokens.size(); i++) {
            std::cout<<"TOKEN TYPE: "<<tokens[i].type<<"\nTOKEN VALUE: "<<tokens[i].value<<"\n\n";
        }
        if (len == 0) {
            std::cout<<"[PARSER LOG] TOKENS NOT FOUND\n";
            ast_vct = {"", {""}};
            return ast_vct;
        }
        else {
            std::cout<<"[PARSER LOG] CLEARING TOKENS\n";
            for (int i = 0; i != tokens.size(); i++) {
                if (!(tokens[i].type == "SPACE")) {
                    cls_tks.push_back(tokens[i]);
                }
            }
            std::cout<<"[PARSER LOG] MAIN CYCLE\n";
            if (cls_tks[0].type == "KWORD") {
                std::cout<<"[PARSER LOG] ADDING COMMAND IN AST\n";
                ast_vct.command = tokens[0].value;
                std::cout<<"[PARSER LOG] GETTING NUM OF CLEAR TOKENS\n";
                int leng = cls_tks.size();
                std::cout<<"[PARSER LOG] CREATE BUFFER\n";
                std::string buf = "\"";
                for (int i = 0; i != leng; i++) {
                    if (cls_tks[i].type == "QUOTE") {
                        std::cout<<"[PARSER LOG] QUOTE TOKEN FOUND\n";
                        if (buf != "") {
                            buf += "\"";
                            cls_tks2.push_back({"STRING", buf});
                            buf = "\"";
                            b = 0;
                        }
                        else {
                            b = 1;
                        }
                    }
                    else {
                        std::cout<<"[PARSER LOG] OTHER TOKEN FOUND\n";
                        if (b) {
                            std::cout<<"[PARSER LOG] BUFFER STATUS IS TRUE\n";
                            if (cls_tks[i].type == "WORD"
                            ||  cls_tks[i].type == "KWORD"
                            ||  cls_tks[i].type == "SYMBOL"
                            ||  cls_tks[i].type == "SPECSYMBOL"
                            ||  cls_tks[i].type == "DIGIT") {
                                std::cout<<"[PARSER LOG] IF TOKEN IN MULTI-SYMBOL VALUE CATEGORY\n";
                                buf += cls_tks[i].value;
                            }
                            else {
                                std::cout<<"[PARSER LOG] IF TOKEN IN NONE OR SINGLE VALUE CATEGORY\n";
                                if (cls_tks[i].type == "EQUAL") {
                                    buf += "=";
                                }
                                else if (cls_tks[i].type == "EQUALS") {
                                    buf += "==";
                                }
                                else if (cls_tks[i].type == "PLUS") {
                                    buf += "+";
                                }
                                else if (cls_tks[i].type == "MINUS") {
                                    buf += "-";
                                }
                                else if (cls_tks[i].type == "STAR") {
                                    buf += "*";
                                }
                                else if (cls_tks[i].type == "SLASH") {
                                    buf += "/";
                                }
                                else if (cls_tks[i].type == "MOD") {
                                    buf += "%";
                                }
                                else if (cls_tks[i].type == "L_PAREN") {
                                    buf += "(";
                                }
                                else if (cls_tks[i].type == "R_PAREN") {
                                    buf += ")";
                                }
                                else if (cls_tks[i].type == "SPACE") {
                                    buf += " ";
                                }
                            }
                        }
                        else {
                            std::cout<<"[PARSER LOG] BUFFER STATUS IS FALSE\n";
                            cls_tks2.push_back(cls_tks[i]);
                        }
                    }
                }
            }
            else {
                std::cout<<"[PARSER LOG] INCTRUCTION INCORRECT, CHECK TOKENS LOG\n";
                exit(21);
            }
        }
        if (b == 1) {
            std::cout<<"[PARSER LOG] BUFFER STATUS IS TRUE AFTER CYCLE\n";
            exit(20);
        }
        std::vector<std::string> argss;
        for (int h = 1; h != cls_tks2.size(); h++) {
            argss.push_back(cls_tks2[h].value);
        }
        std::cout<<"[PARSER LOG] ADD DATA IN AST\n";
        ast_vct.args = argss;
        return ast_vct;
    }
}

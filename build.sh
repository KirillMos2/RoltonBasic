mkdir build/

g++ -c lexer.cpp -o build/lexer.o -I include/
g++ -c parser.cpp -o build/parser.o -I include/
g++ -c compiler.cpp -o build/compiler.o -I include/
g++ rolton-basic.cpp build/lexer.o build/parser.o build/compiler.o -o roltonbasic -I include/

rm -rf build/

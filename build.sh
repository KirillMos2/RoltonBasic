mkdir build/

g++ -c lexer.cpp -o build/lexer.o
g++ -c parser.cpp -o build/parser.o
g++ -c compiler.cpp -o build/compiler.o
g++ -c types.cpp -o build/types.o
g++ rolton-basic.cpp build/lexer.o build/parser.o build/compiler.o build/types.o -o roltonbasic

rm -rf build/

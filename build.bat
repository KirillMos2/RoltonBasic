mkdir build/

g++.exe -c lexer.cpp -o build\lexer.o -I include\
g++.exe -c parser.cpp -o build\parser.o -I include\
g++.exe -c compiler.cpp -o build\compiler.o -I include\
g++.exe rolton-basic.cpp build\lexer.o build\parser.o build\compiler.o -o roltonbasic -I include\

del build\
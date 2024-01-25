c-compiler:
	gcc *.c microXML.h -o main.exe
cpp-compiler:
	g++ *.cpp microXML.c microXML.h -o main.exe
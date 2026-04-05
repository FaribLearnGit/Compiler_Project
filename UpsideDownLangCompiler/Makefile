BISON_DIR=C:\Progra~2\GnuWin32\share\bison

all: compiler.exe

parser.tab.c parser.tab.h: parser.y
	set BISON_PKGDATADIR=$(BISON_DIR) && bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

compiler.exe: parser.tab.c lex.yy.c ast.c executor.c
	gcc parser.tab.c lex.yy.c ast.c executor.c -o compiler.exe

run: compiler.exe
	compiler.exe test.udl

clean:
	del /Q parser.tab.c parser.tab.h lex.yy.c compiler.exe output.txt 2>nul
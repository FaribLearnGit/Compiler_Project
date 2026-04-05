# UpsideDownLang Minimal Compiler Project

This is a minimal FLEX + BISON compiler project based on your proposal PDF for **UpsideDownLang**. It avoids AST creation and keeps only the necessary files.

## Files

- `lexer.l` - lexical analyzer for UpsideDownLang
- `parser.y` - syntax parser and driver program
- `test.udl` - sample input source file
- `output.txt` - example output produced after running the test file
- `Makefile` - build and run commands

## Build

```bash
bison -d parser.y
flex lexer.l
gcc -o compiler lex.yy.c parser.tab.c -lfl
```

Or simply:

```bash
make
```

## Run

```bash
./compiler test.udl output.txt
```

Or simply:

```bash
make run
```

## Notes

- The compiler writes analysis/parsing messages directly into the output file.
- No AST node file is used.
- The grammar is intentionally minimal so the project stays manageable.
- It is built from the keyword/operator mapping in your proposal.

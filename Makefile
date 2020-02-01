CC = gcc -g -Werror
OBJ = mycc
SOURCES = ast.c parser.tab.c lex.yy.c genllvm.c main.c
TEST_SOURCE_FILE = test/hello.c

debug: build
	./$(OBJ) $(TEST_SOURCE_FILE) -D

test: build
	./$(OBJ) $(TEST_SOURCE_FILE)

build: $(SOURCES)
	$(CC) $^ -o $(OBJ)

lex.yy.c: scanner.l
	flex $<

parser.tab.c: parser.y
	bison -vdt $<

clean:
	rm lex.yy.c y.*
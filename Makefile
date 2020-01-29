CC = gcc
OBJ = mycc
TEST_SOURCE_FILE = test/hello.c

test: build
	./$(OBJ) < $(TEST_SOURCE_FILE)

build: main.c lex.yy.c y.tab.c
	$(CC) $^ -o $(OBJ)

lex.yy.c: scanner.l
	flex $<

y.tab.c: parser.y
	bison -vdty $<

clean:
	rm lex.yy.c y.*
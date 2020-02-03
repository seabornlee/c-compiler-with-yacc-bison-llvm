CC = gcc
CFLAGS = -g -Werror
EXE = mycc
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
CPPFLAGS = -I$(INCLUDE_DIR)
SRC = parser.tab.c lex.yy.c $(wildcard $(SRC_DIR)/*.c)
SRC_RESOURCES = $(SRC_DIR)/resources
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c,%.o,$(SRC))))
TEST_RESOURCES = test/resources

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

%lex.yy.c: $(SRC_RESOURCES)/scanner.l
	flex -o $(SRC_DIR)/$(notdir $(basename $@)).c $<

%parser.tab.c: $(SRC_RESOURCES)/parser.y
	bison -o $(SRC_DIR)/$(notdir $@) -vdt $<
	mv $(SRC_DIR)/parser.tab.h $(INCLUDE_DIR)

clean:
	rm -f $(SRC_DIR)/parser.*
	rm -f $(INCLUDE_DIR)/parser.*
	rm -rf $(OBJ_DIR)
	rm -f $(EXE)

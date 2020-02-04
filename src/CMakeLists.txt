set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.c)

set(SOURCES ${SOURCES})

find_package(BISON)
find_package(FLEX)
BISON_TARGET(Parser resources/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
FLEX_TARGET(Scanner resources/scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${BINARY} ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} ${SOURCES})
add_library(${BINARY}_lib STATIC ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} ${SOURCES})

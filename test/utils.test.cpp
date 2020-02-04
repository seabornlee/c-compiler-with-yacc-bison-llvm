#include "gtest/gtest.h"

extern "C" {
    #include "utils.h"
}

TEST(UtilsTest, shouldReplaceString) {
    char *origin = "%s\n%s!\n";
    char *result = replace(origin, "\n", "\\0A");
    ASSERT_STREQ("%s\\0A%s!\\0A", result);
}
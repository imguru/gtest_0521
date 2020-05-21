
#include <gtest/gtest.h>

// void foo();
#include "foo.c"

TEST(FooTest, foo) {
	foo();
}

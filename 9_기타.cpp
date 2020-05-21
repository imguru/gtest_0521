#include <gtest/gtest.h>
#define class struct
#define private public
#include "User.h"

TEST(UserTest, foo) {
	User user;

	user.foo();

	ASSERT_EQ(42, user.age);
}

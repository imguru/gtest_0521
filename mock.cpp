
#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Google Mock

TEST(SampleTest, foo) {}

#if 0
int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv); // ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#endif



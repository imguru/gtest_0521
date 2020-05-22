// 11_파라미터화 테스트
bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}
	return true;
}

#include <gtest/gtest.h>

TEST(PrimeTest, IsPrime) {
	int data[] = { 2, 3, 5, 7, 11, 13, 17 };
	
	for (int i = 0 ; i < 7; ++i) {
		EXPECT_TRUE(IsPrime(data[i])) << "IsPrime";
	}
}

TEST(PrimeTest, IsPrime2) {
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_TRUE(IsPrime(7));
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(13));
	EXPECT_TRUE(IsPrime(17));
}

// 11_파라미터화 테스트
// : 입력 데이터를 바꿔가면서, 수차례 반복 검사하는 데이터 중심의 테스트에서 코드 중복을 없애주는 기법.
// => xUnit Test Framework
// => 문제점
//  - 테스트의 이름에서 어떤 데이터를 검증하는지 알 수 없다.
//  - 데이터의 수가 적을 경우, 파라미터화 테스트를 적용하지 않는 것이 낫다.
bool IsPrime(int value) {
	return false;
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}
	return true;
}

#include <gtest/gtest.h>

// 1. Testcase class를 만듭니다.
// class PrimeTest : public ::testing::Test {
class PrimeTest : public ::testing::TestWithParam<int> {
};

// 2. Data Set을 정의합니다.
int data[] = { 2, 3, 5, 7, 11, 13, 17 };
// INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, ::testing::ValuesIn(data));
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, ::testing::Values(2, 3, 5, 7, 11, 13, 17));

// 3. 테스트 함수를 제공하면 됩니다.
// TEST, TEST_F, TEST_P(파라미터화 테스트)
// GetParam(): 값을 얻는 함수 입니다.
TEST_P(PrimeTest, IsPrime) {
	int value = GetParam();
	EXPECT_TRUE(IsPrime(value)) << "IsPrime : " << value;
}






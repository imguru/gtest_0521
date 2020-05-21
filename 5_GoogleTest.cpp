#include <gtest/gtest.h>

// 1. 단언문(함수) - 단언 매크로
//    ASSERT_EQ, NE, LT, LE, GT, GE ...
//   주의사항: 단언문이 실패할경우, 이후의 코드는 수행되지 않는다.

// 구글 테스트에서는 테스트가 실패하더라도, 이후의 코드를 실행하는 단언문을 제공합니다.
//   EXPECT_EQ, NE, LT, LE, GT, GE ...
//  => 하나의 단언문만 실패하더라도, 테스트의 전체 결과는 실패가된다.
TEST(GoogleTestSample, Test1) {
	int expected = 42;
	int actual = 42;

	// 인자의 순서를 주의해야 합니다.
	EXPECT_EQ(expected, 42);
	EXPECT_EQ(expected, actual);  // 죽은 단언문
								  // - 하나의 테스트 함수안에서 단언문을 최소한으로 사용해야 한다.
								  //  => 테스트 함수가 많아질 수 있다.
}

#include <string>

// 2. 문자열 처리
//  const char* 
//  std::string
//   - EXPECT_STREQ/NE  => const char*
TEST(GoogleTestSample, Test2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	// s1 == s2
	EXPECT_EQ(s1, s2) << "Reason 1";

	const char* s3 = s1.c_str();
	const char* s4 = "hello";

	// s3 == s4
	// EXPECT_EQ(s3, s4) << "Reason 2";
	EXPECT_STREQ(s3, s4) << "Reason 2";
}

// 3. 부동 소수점
//  - ASSERT_EQ 사용하면 안됩니다.
//  => ASSERT_DOUBLE_EQ / ASSERT_NEAR
TEST(GoogleTestSample, Test3) {
	double a = 0.7;
	double b = 0.1 * 7;

	ASSERT_DOUBLE_EQ(a, b);
	ASSERT_NEAR(a, b, 0.000000001);
#if 0
	if (a == b) {
		printf("Same\n");
	} else {
		printf("Diff\n");
	}
#endif
}

// 4. 예외 테스트
// EXPECT_THROW / EXPECT_ANY_THROW
void checkName(const std::string& name) {
	 // throw 3;
#if 0
	if (name.empty()) 
		throw std::invalid_argument("name is empty");
#endif

	// ....
}

// checkName을 빈 이름으로 호출하였을 때, invalid_argument 예외가 제대로 발생하는지 여부를 검증하고 싶다.
TEST(GoogleTestSample, Test4_Badcase) {
	try {
		checkName("");
		FAIL() << "기대한 예외가 발생하지 않음.";
	} catch (std::invalid_argument& e) {
		printf("Good!\n");
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생했음.";
	}
}

TEST(GoogleTestSample, Test4) {
	EXPECT_THROW(checkName(""), std::invalid_argument);
	
	EXPECT_ANY_THROW(checkName("")); // 예외가 발생하면 성공!
}























#include <gtest/gtest.h>

// TestCase : Test의 집합
// TestSuite : 동일한 픽스쳐를 가지는 Test의 집합
//  => TestCase를 TestSuite으로 취급한다.

// * 테스트 함수를 만드는 방법.
// TestCaseName.TestName
TEST(TestCaseName, TestName) {
	// 테스트가 작성 중이면, 실패하여야 한다.
	FAIL() << "테스트가 작성 중입니다.";
}

TEST(TestCaseName2, TestName) {

}

// Google Test 메인은 아래와 같이 작성하면 됩니다.
// - gtest_main.cc 라는 파일을 이용해서, main을 작성하지 않도록 할 수 있습니다.
#if 0
int main(int argc, char** argv) {
	// 1. gtest 라이브러리 초기화
	testing::InitGoogleTest(&argc, argv);

	// 2. 테스트를 실행한다.
	return RUN_ALL_TESTS();
}
#endif


#include <gtest/gtest.h>

// Google Test 메인은 아래와 같이 작성하면 됩니다.
int main(int argc, char** argv) {
	// 1. gtest 라이브러리 초기화
	testing::InitGoogleTest(&argc, argv);

	// 2. 테스트를 실행한다.
	return RUN_ALL_TESTS();
}

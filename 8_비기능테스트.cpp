
#include <gtest/gtest.h>
#include <unistd.h>

// 8_비기능 테스트 
//  : 기능의 시간 / 메모리 누수

void foo() {
	sleep(3);
}

class FooTest : public ::testing::Test {
protected:
	time_t startTime;
	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < 2) << "시간 초과: " << duration << " 초가 걸렸습니다.";
	}
};

// 2초 안에서 수행되는지 여부를 검증하고 싶다.
TEST_F(FooTest, foo) {
	foo();
}

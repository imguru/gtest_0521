
#include <gtest/gtest.h>
#include <unistd.h>

void foo() {
	sleep(3);
}

template <typename T, int N>
class TimeTest : public ::testing::Test {
protected:
	// static int PIVOT = N;

	time_t startTime;
	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < N) << "시간 초과: " << duration << " 초가 걸렸습니다.";
	}
};

// CRTP: Curiosly Recurring Template Pattern
//  => 부모 클래스를 분리 하는 의도로 사용한다.
class FooTest : public TimeTest<FooTest, 2> {
protected:
#if 1
	virtual void SetUp() {
		// TimeTest::SetUp();
	}

	virtual void TearDown() {
		// TimeTest::TearDown();
	}
#endif
};


#if 1
#define EXPECT_TIMEOUT(fn, sec)	    \
	{                               \
		time_t s = time(0);         \
		fn;                         \
		time_t e = time(0);         \
		time_t d = e - s;           \
		EXPECT_TRUE(d < sec) << "Timeout: " << d << "sec"; \
	}
#endif

// 2초 안에서 수행되는지 여부를 검증하고 싶다.
TEST_F(FooTest, foo) {
	EXPECT_TIMEOUT(foo(), 2); // - 테스트 유틸리티 함수를 직접 만들어서 사용하는 것도 좋습니다.
}

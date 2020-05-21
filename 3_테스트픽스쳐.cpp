#include <gtest/gtest.h>

class Calc {
public:
	// Calc(double n) : {} 
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}

	double Display() { return 0; }
};

// Test Fixture
// 1. 정의: xUnit Test Pattern에서 SUT를 실행하기 위해 준비해야 하는 모든 작업
// 2. 픽스쳐를 구성하는 모든 로직 부분을 픽스쳐를 설치한다. 라고 합니다.

// 테스트 픽스쳐를 설치하는 방법 1
// => Inline Setup
// : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
// 장점
//  - 테스트의 인과 관계를 쉽게 파악할 수 있다.
// 단점
//  - 모든 테스트 함수 안에서 중복이 발생한다.

TEST(CalcTest, PlusTest) {
	Calc* calc = new Calc;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	if (calc->Display() != 4) {
		FAIL() << "2 + 2 했을 때";
	}
}

TEST(CalcTest, PressPlus_2Plus2_DisplaysFour) {
	Calc* calc = new Calc;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	ASSERT_EQ(4, calc->Display()) << "2 + 2 했을 때";
}


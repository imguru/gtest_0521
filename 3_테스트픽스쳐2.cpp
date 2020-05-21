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

// 방법 2. Delegate Setup(위임 설치)
//  : 픽스쳐 설치에 대한 중복 코드를 별도의 함수로 묶는다.
//    전역 함수로 제공하는 것이 아니라, 해당 테스트 케이스를 통해서 접근할 수 있도록 하는 것이 좋다.

// TestCase class
class CalcTest : public testing::Test {
// private: 테스트 함수에서 접근할 수 없다.
protected:
	Calc* CreateCalc() { return new Calc; }
	// Test Utility 함수 - Creation
};

// 주의사항 : 테스트 함수를 만들 때, TEST -> TEST_F
// TEST_F: ::testing::Test를 상속받는 클래스의 자식 클래스를 생성하는 매크로입니다.
// TEST: ::testing::Test의 자식 클래스를 생성하는 매크로입니다.
TEST_F(CalcTest, PlusTest) {
	Calc* calc = CreateCalc();
	// Calc* calc = new Calc;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	if (calc->Display() != 4) {
		FAIL() << "2 + 2 했을 때";
	}
}

TEST_F(CalcTest, PressPlus_2Plus2_DisplaysFour) {
	Calc* calc = CreateCalc();

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	ASSERT_EQ(4, calc->Display()) << "2 + 2 했을 때";
}


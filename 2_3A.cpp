#include <gtest/gtest.h>

// SUT - 테스트 대상 시스템(System Under Test)
class Calc {
public:
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}

	double Display() { return 0; }
};

// 테스트 함수를 구성하는 방법.
// 3A / TDD(테스트 주도 개발) / BDD(행위 주도 개발)
// 1. Arrange: 객체를 생성하고, 필요한 경우에 설정하고 준비한다. - Given
// 2. Act: 객체에 작용을 가한다.                                 - When
// 3. Assert: 기대하는 바를 단언한다.                            - Then

// SUT      TestCase / TestSuite
// Calc  ->  CalcTest, CalcSpec

// CalcTest.PlusTest
//  --filter=*.PlusTest
//  --filter=*.P_*
//  --filter=CalcTest.*
//  ex) P_PlusTest
//      N_PlusTest
//      T_PlusTest
TEST(CalcTest, PlusTest) {
	// Arrange
	Calc* calc = new Calc;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	// Assert
	if (calc->Display() != 4) {
		FAIL() << "2 + 2 했을 때";
	}
}

// 개선점
// 1) 단위 테스트 함수 안에서 제어 구문의 발생을 최소화하는 것이 좋다.
//  => 조건문, 반복문, 예외처리
//  => xUnit Test Framework는 단언 함수를 통해 기대 조건을 체크할 수 있도록 합니다.

// 2) 현재의 테스트의 이름은 테스트가 어떤 시나리오로 동작하는지 알 수 없습니다.
//    ex) 테스트대상함수_시나리오_기대값

// TEST(CalcTest, PlusTest2) {
TEST(CalcTest, PressPlus_2Plus2_DisplaysFour) {
	// Arrange
	Calc* calc = new Calc;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	// Assert
	ASSERT_EQ(4, calc->Display()) << "2 + 2 했을 때";
}

// 테스트 품질 - Effective Unit Test
// 1) 가독성 
// 2) 유지보수성
// 3) 신뢰성









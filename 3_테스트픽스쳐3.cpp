#include <gtest/gtest.h>

class Calc {
public:
	// Calc(double n) : {} 
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}

	double Display() { return 0; }
};

// 3. Implicit Setup/TearDown(암묵적 설치/해체)
//  => xUnit Test Framework이 제공하는 기능입니다.
//  장점
//   => 테스트 코드의 중복을 제거하고, 불필요한 상호작용을 테스트 코드에서 제거할 수 있다.
//  단점
//   => 픽스쳐 설치가 테스트 코드 밖에 존재하기 떄문에, 테스트 코드 안에서 인과관계를 이해하기 어렵다.

class CalcTest : public testing::Test {
protected:
	Calc *calc;
	
	CalcTest() : calc(NULL) {}

	virtual void SetUp() override {
		printf("SetUp()\n");
		calc = new Calc;
	}

	// 아래 함수는 테스트의 성공 실패와 관계없이 무조건 호출됩니다.
	virtual void TearDown() override {
		printf("TearDown()\n");
		delete calc;
	}
};

// xUnit Test Pattern - 4단계 테스트 패턴
// 1단계 - 테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 설정하는 작업. - SetUp()
// 2단계 - SUT와 상호작용한다.  - TEST_F
// 3단계 - 기대 결과를 확인한다. - TEST_F
// 4단계 - 테스트 픽스쳐를 해체해서, 테스트 시작 전으로 돌려놓는다. - TearDown()

// 테스트 함수 안에서 ASSERT가 실패하면, 이후의 코드는 실행되지 않는다.
TEST_F(CalcTest, PlusTest) {
	// Calc* calc = new Calc;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	if (calc->Display() != 4) {
		FAIL() << "2 + 2 했을 때";
	}

	// delete calc;
	// printf("메모리 해지.\n");
}

TEST_F(CalcTest, PressPlus_2Plus2_DisplaysFour) {
	// Calc* calc = new Calc;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	
	ASSERT_EQ(4, calc->Display()) << "2 + 2 했을 때";

	// delete calc;
	// printf("메모리 해지.\n");
}


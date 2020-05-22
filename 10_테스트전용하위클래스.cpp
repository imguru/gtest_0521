#include <stdio.h>
// 테스트 전용 하위 클래스
// SUT
class Engine {
public:
	Engine() { printf("Engine()\n"); }

	virtual void Start() {
		printf("Engine Start()\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ...
		engine->Start();
	}
};

#include <gtest/gtest.h>

// Engine
//  => 테스트 전용 하위 클래스
//  => 부모가 테스트를 위한 기능을 제공하고 있지 않다면, 테스트 코드 안에서 자식 클래스를 통해 해당 기능을 구현하면 된다.
//    : 제품 코드를 변경하지 않고, 테스트되지 않은 요구사항을 만족할 수 있다.
class TestEngine : public Engine {
	// 테스트를 위한 속성 
	bool isStart;
public:
	TestEngine(): isStart(false) { printf("TestEngine()\n"); }

	virtual void Start() {
		Engine::Start();    // 부모의 기능을 그대로 사용한다.
		isStart = true;
	}

	// 테스트를 위한 함수 
	bool IsStart() {
		return isStart;
	}
};

class CarTest : public ::testing::Test {
};

// Car 객체에 Go를 호출하였을 때, Engine 객체에 대해서 Start가 제대로 호출되었는지 여부를 검증하고 싶다.
TEST_F(CarTest, GoTest) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	// 검증을 해야하는데, 검증할 수 있는 방법이 존재하지 않는다.
	ASSERT_TRUE(engine.IsStart()) << "자동차가 Go 했을 때";
}
















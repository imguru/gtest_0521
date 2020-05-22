
// 테스트 대역 종류
// 1. Test Stub   => Stub
// 2. Fake Object => Fake
// 3. Test Spy    => Spy
// 4. Mock Object => Mock
//

// Test Stub Pattern
// => '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//  : 실제 의존하는 객체를 테스트용 객체로 교체해서, 
//    SUT가 테스트하는데 필요한 결과를 보내도록 한다.
//  : 특수한 상황을 시뮬레이션 할 수 있다.
//    => 네트워크 오류, OS의 결과, 시간 
//    => 제어할 수 없는 환경을 제어하기 위해 사용한다.

#include <iostream>

// Network 연결이 끊겼을 경우 발생하는 예외
class IOException : public std::exception {
public:
	virtual const char* what() {
		return "Bad connection...";
	}
};

struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;
	// 인터페이스가 기본 구현을 가지면 좋습니다.
	// 인터페이스를 구현하는 하위 클래스가 해당 기능을 구현하지 않아도 됩니다.
	// virtual void Attack() = 0;
	virtual void Attack() {}
};

class TCPConnection : public IConnection {
public:
	virtual void Move(int x, int y) override {
		// ...
	}
};

class Player {
	IConnection* connection;
public:
	Player(IConnection* p) : connection(p) {}

	void Move(int x, int y) {
		try {
			connection->Move(x, y);
		} catch (IOException& e) {
			//...
			throw e;
		}
	}
};

#include <gtest/gtest.h>

class StubConnection : public IConnection {
public:
	virtual void Move(int x, int y) {
		throw IOException();
	}
};

// 의존성 주입 장점
//  - 제품 코드를 사용하는 방식 그대로 테스트를 수행할 수 있다.

// Connection이 끊겼을 경우, IOException이 제대로 전파되는지 검증하고 싶다.
TEST(PlayerTest, MoveTest) {
	// TCPConnection conn;
	StubConnection conn;
	Player player(&conn);

	ASSERT_THROW(player.Move(10, 23), IOException);
}

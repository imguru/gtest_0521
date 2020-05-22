#include <string>
#include <vector>
#include "DLoggerTarget.h"

#if 0
enum Level {
	INFO, WARN, ERROR, 
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}
	
	virtual void Write(Level level, const std::string& message) = 0;
};
#endif

// class FileTarget : public DLoggerTarget {};
// class NetTarget : public DLoggerTarget {};

// 분산 로거 - Observer Pattern(Subject)
class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* e : targets) {
			e->Write(level, message);
		}
	}
};

//---------------------
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// DLogger에 Write를 수행하였을 때, Log가 제대로 전달되는지 여부를 검증하고 싶다.
//  : 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서,
//    테스트 안된 요구사항이 있을 때
//    => Test Spy Pattern
//    - 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//      : 다른 컴포넌트로부터의 간접 출력을 저장해두었다가 검증한다.
//      상태검증 - 객체에 작용을 가한 후, 단언 함수를 이용해서 상태를 검증하는 것.
//    => Mock Object Pattern
//      => 행위 기반 검증(동작 검증)
//      동작 검증 - 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부 / 호출 순서 / 호출 횟수 등을 통해
//                  검증 작업을 수행하는 것을 의미한다.
//           => Mock Framework
//              Java: jMock, EasyMock, Mockito, Spock ...
//              C++: Google Mock
//
// Google Mock 적용하는 방법.
//  1) 매크로 작업
#if 0
// 아래 작업을 직접했을 경우, 실수가 발생할 수 있다.
// googlemock/scripts/generator/gmock_gen.py

class MockTarget : public DLoggerTarget {
	// virtual void Write(Level level, const std::string& message)
public:
	// MOCK_METHOD{인자개수}(함수의이름, 함수의시그니쳐);
	// (Old)MOCK_METHOD2(Write, void(Level, const std::string&));
	
	// 1.10: MOCK_METHOD(반환타입, 함수이름, 인자의 정보);
	MOCK_METHOD(void, Write, (Level, const std::string&));
};
#endif
#include "MockDLoggerTarget.h"

TEST(DLoggerTest, WriteTest) {
	DLogger logger;
	MockDLoggerTarget mock1, mock2;
	logger.AddTarget(&mock1);
	logger.AddTarget(&mock2);

	// ASSERT 영역을 먼저 작성해야 합니다. - Google Mock
	EXPECT_CALL(mock1, Write(INFO, "test_message"));
	EXPECT_CALL(mock2, Write(INFO, "test_message"));

	// Act
	logger.Write(INFO, "test_message");
}

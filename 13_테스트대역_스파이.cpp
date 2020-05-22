// Test Spy
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR, 
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}
	
	virtual void Write(Level level, const std::string& message) = 0;
};

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

// DLogger에 Write를 수행하였을 때, Log가 제대로 전달되는지 여부를 검증하고 싶다.
// Test Spy Pattern
//  : 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서,
//   테스트 안된 요구사항이 있을 때
//
// => 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//   : 다른 컴포넌트로부터의 간접 출력을 저장해두었다가 검증한다.

#include <algorithm>

class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;
	
	std::string concat(Level level, const std::string& message) {
		static const char* levelStr[] = {
			"INFO", "WARN", "ERROR",
		};

		return std::string(levelStr[level]) + "@" + message;
	}
public:
	virtual void Write(Level level, const std::string& message) {
		history.push_back(concat(level, message));
	}

	bool IsReceived(Level level, const std::string& message) {
		std::string log = concat(level, message);

		return std::find(history.begin(), history.end(), log) != history.end();
	}
};

TEST(DLoggerTest, WriteTest) {
	DLogger logger;
	SpyTarget spy1, spy2;
	logger.AddTarget(&spy1);
	logger.AddTarget(&spy2);

	logger.Write(INFO, "test_message");

	EXPECT_TRUE(spy1.IsReceived(INFO, "test_message"));
	EXPECT_TRUE(spy2.IsReceived(INFO, "test_message"));
}

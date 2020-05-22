#include <string>
// SUT
//  테스트 대역
//   의도: 의존하는 객체를 테스트 대역으로 대체해서, SUT에 의해서만 테스트의 결과가 결정되도록 하고 싶다.
//   한계
//    => 테스트 대역을 적용할 수 있는 설계가 필요합니다.

// 아래 제품 코드를 테스트 대역을 적용할 수 있도록 변경해봅시다.
//  => 틈새 만들기
//  =>  핵심: SUT가 의존 객체를 이용할 때, 느슨한 결합(약한 결합) 형태의 설계가 적용되어야 합니다.
//  - 강한 결합: SUT가 협력 객체를 이용할 때, 구체적인 타입에 의존하는 것.
//  - 약한 결합: SUT가 협력 객체를 이용할 때, 추상 클래스나 인터페이스에 의존하는 것.
//    => 의존하는 객체를 직접 생성(new)하는 것이 아니라, 외부에서 생성해서 전달 받아야 합니다.
//    => DI(Dependency Injection) 설계
//    => 의존성 주입
//      문제점: 보일러플레이트가 발생합니다.
//      B* b = new B;
//		C* c = new C;
//      A* a = new A(b, c);
//       방법
//        1. 생성자 주입 - 협력 객체가 필수적일 경우 
//        2. 메소드 주입 - 협력 객체가 필수적이지 않을 경우

struct IFileSystem {
	virtual ~IFileSystem() {}
	virtual bool IsValid(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) {
		return false;
	}
};

class Logger {
	IFileSystem* fileSystem;
public:
	Logger(IFileSystem* p = NULL) : fileSystem(p) {
		// 핵심: 기존 객체의 사용방법과 다르지 않도록 한다.
		if (p == NULL) {
			fileSystem = new FileSystem;
		}
	} 

	bool IsValidLogFilename(const std::string& filename) {
		//----------------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}
		//----------------
		bool result = fileSystem->IsValid(filename);
		return result;
	}
};

//-----------------------------------
#include <gtest/gtest.h>

class LoggerTest : public ::testing::Test {
};

// 자기 설명적인 변수명과 자기 설명적인 문자열을 사용하는 것을 테스트 코드의 가독성에 도움이 된다.
TEST_F(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string badfilename = "bad.log";

	ASSERT_FALSE(logger.IsValidLogFilename(badfilename)) << "파일명이 다섯글자 미만일 때";
}

TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string goodfilename = "gooood.log";

	bool actual = logger.IsValidLogFilename(goodfilename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}

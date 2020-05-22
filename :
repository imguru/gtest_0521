#include <string>
// SUT
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

class StubFileSystem : public IFileSystem {
public:
	virtual bool IsValid(const std::string& filename) override {
		return true;
	}
};

class LoggerTest : public ::testing::Test {
};

// 자기 설명적인 변수명과 자기 설명적인 문자열을 사용하는 것을 테스트 코드의 가독성에 도움이 된다.
TEST_F(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string badfilename = "bad.log";

	ASSERT_FALSE(logger.IsValidLogFilename(badfilename)) << "파일명이 다섯글자 미만일 때";
}

TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string goodfilename = "gooood.log";

	bool actual = logger.IsValidLogFilename(goodfilename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}

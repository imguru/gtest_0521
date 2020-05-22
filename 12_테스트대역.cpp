#include <string>
// SUT

class FileSystem {
public:
	bool IsValid(const std::string& filename) {
		return false;
	}
};

class Logger {
public:
	// 요구사항: 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
	//  ex) hello.log -> true
	//      ok.log    -> false
	bool IsValidLogFilename(const std::string& filename) {
		//----------------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}
		//----------------

		FileSystem* fileSystem = new FileSystem;
		bool result = fileSystem->IsValid(filename);
		delete fileSystem;
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

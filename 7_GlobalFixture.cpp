// Global Fixture - 프로그램의 시작 / 끝
//     SetUp() / TearDown()

#include <gtest/gtest.h>

class MyTestEnvironment : public ::testing::Environment {
public:
	virtual void SetUp() override {
		printf("Global Fixture SetUp()\n");
	}

	virtual void TearDown() override {
		printf("Global Fixture TearDown()\n");
	}
};

// 전역 픽스쳐 
//  - 설치 방법 2가지
// 1) main을 직접 작성하지 않을 때
//  => 전역 변수
// ::testing::Environment* const test_env = ::testing::AddGlobalTestEnvironment(new MyTestEnvironment);

// 2) main을 직접 작성할 때
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	::testing::AddGlobalTestEnvironment(new MyTestEnvironment);

	return RUN_ALL_TESTS();
}

class SampleTest2 : public ::testing::Test {
protected:
	static void SetUpTestCase() {
		printf("SampleTest2 - SetupTestCase()\n");
	}

	static void TearDownTestCase() {
		printf("SampleTest2 - TearDownTestCase()\n");
	}
};

TEST_F(SampleTest2, foo) {}
TEST_F(SampleTest2, goo) {}

class SampleTest : public ::testing::Test {
protected:
	static void SetUpTestCase() {
		printf("SampleTest - SetupTestCase()\n");
	}

	static void TearDownTestCase() {
		printf("SampleTest - TearDownTestCase()\n");
	}
};

TEST_F(SampleTest, foo) {}
TEST_F(SampleTest, goo) {}

















#include <string>
#include <unistd.h> // sleep

// 픽스쳐의 설치 또는 해체가 느린 경우
//  -> 모든 테스트에서 수행되기 때문에, 전체적인 테스트가 느려지는 문제가 발생한다.
//  => Slow Test
//   : 개발자의 생산성을 떨어뜨린다.
//  => Suite Fixture Setup / TearDown - xUnit Test Framework
//  => 위의 문제가 아닌 다른 경우에는 사용하는 것이 좋지 않습니다.
//    - 문제점: "변덕스러운 테스트"가 발생할 수 있습니다.

// DatabaseTest::SetUpTestCase(); - Suite Fixture Setup - static
// DatabaseTest* testcase = new DatabaseTest;
// testcase->SetUp();
// testcaes->TestBody();
// testcase->TearDown();

// DatabaseTest* testcase = new DatabaseTest;
// testcase->SetUp();
// testcaes->TestBody();
// testcase->TearDown();
// DatabaseTest::TearDownTestCase(); - Suite Fixture TearDown - static

// SUT
class Database {
public:
	void Connect() { sleep(2); }
	void Disconnect() { sleep(1); }

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return false; }
};

#include <gtest/gtest.h>

class DatabaseTest : public ::testing::Test {
protected:
	static Database* database;

	// DatabaseTest() : database(NULL) {}

	static void SetUpTestCase() {
		printf("SetUpTestCase()\n");
		database = new Database;
		database->Connect();
	}

	static void TearDownTestCase() {
		printf("TearDownTestCase()\n");
		database->Disconnect();
		delete database;
	}

	virtual void SetUp() override {
	}

	virtual void TearDown() override {
	}
};

// 정적 멤버 변수는 외부 정의가 필요합니다.
Database* DatabaseTest::database = NULL;


TEST_F(DatabaseTest, foo) {}
TEST_F(DatabaseTest, goo) {}

TEST_F(DatabaseTest, LoginTest) {
	database->Login("test_id", "test_password");
	bool actual = database->IsLogin();

	ASSERT_TRUE(actual) << "로그인 하였을 때";
}

TEST_F(DatabaseTest, LogoutTest) {
	database->Login("test_id", "test_password");
	database->Logout();
	bool actual = database->IsLogin();

	ASSERT_FALSE(actual) << "로그아웃 하였을 때";
}
#if 0
TEST_F(DatabaseTest, LoginTest) {
	Database* database = new Database;
	database->Connect();

	database->Login("test_id", "test_password");
	bool actual = database->IsLogin();

	ASSERT_TRUE(actual) << "로그인 하였을 때";

	database->Disconect();
	delete database;
}

TEST_F(DatabaseTest, LogoutTest) {
	Database* database = new Database;
	database->Connect();
	
	database->Login("test_id", "test_password");
	database->Logout();
	bool actual = database->IsLogin();

	ASSERT_FALSE(actual) << "로그아웃 하였을 때";

	database->Disconnect();
	delete database;
}
#endif

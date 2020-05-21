#include <string>

// SUT
class Database {
public:
	void Connect() {}
	void Disconnect() {}

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return false; }
};

#include <gtest/gtest.h>

class DatabaseTest : public ::testing::Test {
protected:
	Database* database;

	DatabaseTest() : database(NULL) {}

	virtual void SetUp() override {
		database = new Database;
		database->Connect();
	}

	virtual void TearDown() override {
		database->Disconnect();
		delete database;
	}
};

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

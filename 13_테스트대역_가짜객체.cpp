
#include <string>

class User {
	std::string name;
	int age;
public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string GetName() const { return name; }
	int GetAge() const { return age; }
};

struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* u) {
		// ...
		database->SaveUser(u->GetName(), u);
		// ...
	}

	User* Load(const std::string& name) {
		// ...
		return database->LoadUser(name);
	}
};

#include <gtest/gtest.h>
#include <map>

// Docker

// Fake Object Pattern
//  : 아직 준비되지 않은 의존 객체로 인해서, 테스트 안된 요구사항 있을 때...
// => 동일한 기능을 제공하는 가벼운 테스트 대역으로 문제를 해결 할 수 있다.
// 1) 의존하는 객체를 사용할 수 없을 때
// 2) 의존하는 객체가 너무 느릴 때 - Slow Test
class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	virtual void SaveUser(const std::string& name, User* user) {
		data[name] = user;
	}

	virtual User* LoadUser(const std::string& name) {
		return data[name];
	}
};

// EQ
bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

// NE
bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

// 객체의 문자열 출력 형태를 변경하기 위해서는 아래 함수가 필요합니다.
std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age=" << user.GetAge() << ")";
}

TEST(UserManagerTest, SaveTest) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_EQ(expected, *actual) << "Load 하였을 때";
	EXPECT_NE(expected, *actual);
	// 사용자 정의 객체를 EXPECT_EQ / ASSERT_EQ를 통해 비교하기 위해서는,
	// operator== 을 제공해주어야 합니다.
}

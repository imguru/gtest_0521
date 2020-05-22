#include <gtest/gtest.h>

class User {
	int age;
public:
	User() : age(42) {}

protected:
	int GetAge() { return age; }
};

// SUT에서 접근해야 하는 필드나 메소드가 protected 인 경우, 테스트 전용 하위 클래스를 통해
// 쉽게 해결할 수 있다.
class TestUser : public User {
public:
	using User::GetAge;  // 부모의 protected 인터페이스의 접근 지정 레벨을 public 으로 변경한다.
};


TEST(UserTest, AgeTest) {
	TestUser user;

	ASSERT_EQ(42, user.GetAge());
}

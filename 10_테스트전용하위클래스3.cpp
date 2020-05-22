#include <gtest/gtest.h>

// #define private public
// #define class struct

// GoogleTest는 private의 필드나 메소드를 검증하기 위한 기능을 제공합니다.
class User {
	int age;
public:
	User() : age(42) {}
private:
	int GetAge() { return age; }

	FRIEND_TEST(UserTest, AgeTest);
	// 제품 코드가 google test에 의존성이 발생한다.
	// => 제품 코드에서 의존성을 제거하기 위해서는 조건부 컴파일을 활용하면 된다.
};

// Clean Code - 로버트 C 마틴
//  => private 메소드의 목적은 public 메소드의 가독성을 높이기 위해 사용한다.
//  => 검증하지 못한 private 메소드 보다는 검증된 public 메소드가 낫다.

TEST(UserTest, AgeTest) {
	User user;

	ASSERT_EQ(42, user.GetAge());
}

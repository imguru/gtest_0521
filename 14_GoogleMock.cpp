// Google Mock
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class User {
public:
	virtual ~User() {}  // 상속
	
	virtual void Stop() {}
	virtual void Move(int x, int y) {}

	virtual int GetX() const { return 0; }
	virtual int GetY() const { return 1; }
};

class MockUser : public User {
 public:
  MOCK_METHOD0(Stop, void());
  MOCK_METHOD2(Move, void(int x, int y));
  MOCK_CONST_METHOD0(GetX, int());
  MOCK_CONST_METHOD0(GetY, int());
};

// 행위 기반 검증
//  1. 호출 여부
//  2. 호출 횟수
//  3. 호출 순서
//  4. 호출 인자
void Sample3(User* p) {
	p->Move(10, 20);
	p->Stop();
}

// 순서를 고려하고 싶다. - testing::InSequence
TEST(MockTest, Sample3Test) {
	// MockUser* mock = new MockUser;
	MockUser mock;
	testing::InSequence seq; // 생성만 한다.

	EXPECT_CALL(mock, Move(10, 20));
	EXPECT_CALL(mock, Stop());
	
	Sample3(&mock);
	// delete mock;
	// mock 객체가 파괴할 때, 검증을 수행한다.
}

void Sample2(User* p) {
	p->Move(10, 20);
	p->Move(20, 20);
	p->Move(30, 20);
	p->Move(10, 20);
	p->Move(20, 20);
	p->Move(30, 20);
}

// - 호출 횟수 / 호출 인자
// 1. Times(N)
// 2. testing::_;
// 3. testing::AnyNumber;
using testing::_;
using testing::AnyNumber;
TEST(MockTest, Sample2Test) {
	MockUser mock;
	
	// EXPECT_CALL(mock, Move(10, 20)).Times(3);
	EXPECT_CALL(mock, Move(_, 20)).Times(AnyNumber());

	Sample2(&mock);
}

void Sample1(User* p) {
	p->Move(10, 20);
	p->Stop();
}

TEST(MockTest, SampleTest) {
	MockUser mock;
	
	EXPECT_CALL(mock, Move(10, 20));
	EXPECT_CALL(mock, Stop());

	Sample1(&mock);
}

// Stub도 Google Mock을 통해 만들 수 있습니다.
//  => ON_CALL
using testing::Return;
TEST(MockTest, StubTest) {
	MockUser mock;
	ON_CALL(mock, GetX()).WillByDefault(Return(10));
	ON_CALL(mock, GetY()).WillByDefault(Return(30));

	EXPECT_EQ(10, mock.GetX());
	EXPECT_EQ(30, mock.GetY());
}

TEST(MockTest, StubTest2) {
	MockUser mock;

	// Stub의기능을 EXPECT_CALL을 통해서도 가능하다.
	EXPECT_CALL(mock, GetX())
		.WillOnce(Return(10))
		.WillOnce(Return(20))
		.WillRepeatedly(Return(30));

	printf("%d\n", mock.GetX());
	printf("%d\n", mock.GetX());
	printf("%d\n", mock.GetX());
}

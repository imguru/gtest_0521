
// Google Mock

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class User {
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

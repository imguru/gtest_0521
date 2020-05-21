#include <gtest/gtest.h>

// 테스트 프레임워크가 동작하는 방식
// TEST -> TEST_F

// 신선한 픽스쳐 전략
//  : 

#if 0
	SampleTest* t = new SampleTest;
	t->SetUp();
	t->TestBody();
	t->TearDown();
	
	SampleTest* t = new SampleTest;
	t->SetUp();
	t->TestBody2();
	t->TearDown();
#endif

class SampleTest : public testing::Test {
protected:
	SampleTest() { printf("SampleTest()\n"); }
	~SampleTest() { printf("~SampleTest()\n"); }

	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

TEST_F(SampleTest, Test1) {
	printf("  SampleTest.Test1()\n");
}

TEST_F(SampleTest, Test2) {
	printf("  SampleTest.Test2()\n");
}

#include <gtest/gtest.h>
// SUT
class Image {
public:
#ifdef IMAGE_MEMORY_TEST
	static int allocCount;
	
	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}
#endif
};

#ifdef IMAGE_MEMORY_TEST
int Image::allocCount = 0;
#endif

void foo() {
	Image* p = new Image;
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;
	Image* p4 = new Image;
}

class ImageTest : public ::testing::Test {
protected:
	int alloc;
	virtual void SetUp() {
#ifdef IMAGE_MEMORY_TEST
		alloc = Image::allocCount;
#endif
	}

	virtual void TearDown() {
#ifdef IMAGE_MEMORY_TEST
		int diff = Image::allocCount - alloc;
		EXPECT_EQ(0, diff) << diff << " Objects leaks";
#endif
	}
};

// foo 함수를 호출 했을 때, 객체의 메모리가 해지 되지 않은 경우를 테스트 하고 싶다.
TEST_F(ImageTest, foo) {
	foo();
}

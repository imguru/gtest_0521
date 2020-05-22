
// Google Test Listener - main()
#include <gtest/gtest.h>

// ./a.out --gtest_output=xml => test_details.xml 파일 생성
TEST(SampleTest, Test1) {
	RecordProperty("cpu", "1.2");
	RecordProperty("mem", "20%");

	SUCCEED(); 
}
TEST(SampleTest, Test2) { SUCCEED(); }
TEST(SampleTest, Test3) { FAIL(); }
TEST(SampleTest, Test4) { FAIL(); }

using testing::TestInfo;
class MyPrinter : public testing::EmptyTestEventListener {
  void OnTestStart(const TestInfo& test_info) {
	printf("**************************START\n");	
	printf("name: %s\n", test_info.name());
  }

  void OnTestEnd(const TestInfo& test_info) {
	printf("**************************END\n");	
	printf("name: %s\n", test_info.name());
  }
};


#if 0
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
	delete listeners.Release(listeners.default_result_printer());
	listeners.Append(new MyPrinter);

	return RUN_ALL_TESTS();
}
#endif

#define ENABLE_TEST  // Uncomment this line to enable the tests

#include "../../tests/googletest/googletest/include/gtest/gtest.h"
#include "../../car_maintenance_lib/include/car_maintenance_lib.h"  // Adjust this include path based on your project structure
using namespace std;

class CarTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Setup test data
  }

  void TearDown() override {
    // Clean up test data
  }
};

string testString;
int fail = -1;

TEST_F(CarTest, TestFileRead) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING3\n4-)TEXT STRING4\n";
  EXPECT_EQ(testString, file_read("test1.txt"));
}

TEST_F(CarTest, TestFileAppend) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING3\n4-)TEXT STRING4\n5-)TEXT STRING5\n";
  string appendString = "TEXT STRING5";
  file_append("test2.txt", appendString);
  EXPECT_EQ(testString, file_read("test2.txt"));
}

TEST_F(CarTest, TestFileEdit) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING EDIT\n4-)TEXT STRING4\n";
  string editString = "TEXT STRING EDIT";
  file_edit("test3.txt", 3, editString);
  EXPECT_EQ(testString, file_read("test3.txt"));
}

TEST_F(CarTest, TestFileDelete) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING3\n3-)TEXT STRING4\n";
  file_line_delete("test4.txt", 2);
  EXPECT_EQ(testString, file_read("test4.txt"));
}

TEST_F(CarTest, TestFileWrite) {
  testString = "0-)TEXT STRING WRITE\n";
  string writeString = "TEXT STRING WRITE";
  file_write("test5.txt", writeString);
  EXPECT_EQ(testString, file_read("test5.txt"));
}

TEST_F(CarTest, TestFileReadFail) {
  ASSERT_EQ("-1", file_read("test1f.txt"));
}

TEST_F(CarTest, TestFileAppendFail) {
  string appendString = "TEXT STRING5";
  ASSERT_EQ(fail, file_append("test2f.txt", appendString));
}

TEST_F(CarTest, TestFileEditFail) {
  string editString = "TEXT STRING EDIT";
  ASSERT_EQ(fail, file_edit("test3f.txt", 3, editString));
}

TEST_F(CarTest, TestFileDeleteFail) {
  ASSERT_EQ(fail, file_line_delete("test4f.txt", 2));
}

int main(int argc, char **argv) {
#ifdef ENABLE_TESTS
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}

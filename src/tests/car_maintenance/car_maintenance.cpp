/**
 * @file car_test.cpp
 * @brief Unit tests for the car maintenance library functions.
 */

#define ENABLE_TESTS  // Uncomment this line to enable the tests

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

/**
 * @brief Tests the file_read function.
 */
TEST_F(CarTest, TestFileRead) {
  testString = "0-)TEXT STRING0\r\n1-)TEXT STRING1\r\n2-)TEXT STRING2\r\n3-)TEXT STRING3\r\n4-)TEXT STRING4\r\n";
  EXPECT_EQ(testString, file_read("test1.bin"));
}

/**
 * @brief Tests the file_append function.
 */
TEST_F(CarTest, TestFileAppend) {
  testString = "0-)TEXT STRING0\r\n1-)TEXT STRING1\r\n2-)TEXT STRING2\r\n3-)TEXT STRING3\r\n4-)TEXT STRING4\r\n5-)TEXT STRING5\r\n";
  string appendString = "TEXT STRING5";
  file_append("test2.bin", appendString);
  EXPECT_EQ(testString, file_read("test2.bin"));
}

/**
 * @brief Tests the file_edit function.
 */
TEST_F(CarTest, TestFileEdit) {
  testString = "0-)TEXT STRING0\r\n1-)TEXT STRING1\r\n2-)TEXT STRING2\r\n3-)TEXT STRING EDIT\r\n4-)TEXT STRING4\r\n";
  string editString = "TEXT STRING EDIT";
  file_edit("test3.bin", 3, editString);
  EXPECT_EQ(testString, file_read("test3.bin"));
}

/**
 * @brief Tests the file_line_delete function.
 */
TEST_F(CarTest, TestFileDelete) {
  testString = "0-)TEXT STRING0\r\n1-)TEXT STRING1\r\n2-)TEXT STRING3\r\n3-)TEXT STRING4\r\n";
  file_line_delete("test4.bin", 2);
  EXPECT_EQ(testString, file_read("test4.bin"));
}

/**
 * @brief Tests the file_write function.
 */
TEST_F(CarTest, TestFileWrite) {
  testString = "0-)TEXT STRING WRITE\r\n";
  string writeString = "TEXT STRING WRITE";
  file_write("test5.bin", writeString);
  EXPECT_EQ(testString, file_read("test5.bin"));
}

/**
 * @brief Tests the file_read function in a fail case.
 */
TEST_F(CarTest, TestFileReadFail) {
  ASSERT_EQ("-1", file_read("test1f.bin"));
}

/**
 * @brief Tests the file_append function in a fail case.
 */
TEST_F(CarTest, TestFileAppendFail) {
  string appendString = "TEXT STRING5";
  ASSERT_EQ(fail, file_append("test2f.bin", appendString));
}

/**
 * @brief Tests the file_edit function in a fail case.
 */
TEST_F(CarTest, TestFileEditFail) {
  string editString = "TEXT STRING EDIT";
  ASSERT_EQ(fail, file_edit("test3f.bin", 3, editString));
}

/**
 * @brief Tests the file_edit function in a fail case (line number out of bounds).
 */
TEST_F(CarTest, TestFileEditFail_2) {
  string editString = "TEXT STRING EDIT";
  ASSERT_EQ(fail, file_edit("test3.bin", 100, editString));
}

/**
 * @brief Tests the file_line_delete function in a fail case.
 */
TEST_F(CarTest, TestFileDeleteFail) {
  ASSERT_EQ(fail, file_line_delete("test4f.bin", 2));
}

/**
 * @brief Tests the file_line_delete function in a fail case (line number out of bounds).
 */
TEST_F(CarTest, TestFileDeleteFail_2) {
  ASSERT_EQ(fail, file_line_delete("test4.bin", 100));
}

/**
 * @brief Main function to run the tests.
 */
int main(int argc, char **argv) {
#ifdef ENABLE_TESTS
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}

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
int success = 0;

/**
 * @brief Tests the file_read function.
 */
TEST_F(CarTest, TestFileRead) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING3\n4-)TEXT STRING4\n";
  EXPECT_EQ(testString, file_read("test1.bin"));
}

/**
 * @brief Tests the file_append function.
 */
TEST_F(CarTest, TestFileAppend) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING3\n4-)TEXT STRING4\n5-)TEXT STRING5\n";
  string appendString = "TEXT STRING5";
  file_append("test2.bin", appendString);
  EXPECT_EQ(testString, file_read("test2.bin"));
}

/**
 * @brief Tests the file_edit function.
 */
TEST_F(CarTest, TestFileEdit) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING EDIT\n4-)TEXT STRING4\n";
  string editString = "TEXT STRING EDIT";
  file_edit("test3.bin", 3, editString);
  EXPECT_EQ(testString, file_read("test3.bin"));
}

/**
 * @brief Tests the file_line_delete function.
 */
TEST_F(CarTest, TestFileDelete) {
  testString = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING3\n3-)TEXT STRING4\n";
  file_line_delete("test4.bin", 2);
  EXPECT_EQ(testString, file_read("test4.bin"));
}

/**
 * @brief Tests the file_write function.
 */
TEST_F(CarTest, TestFileWrite) {
  testString = "0-)TEXT STRING WRITE\n";
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
 * @brief Tests the file_edit function in a fail case (line number out of range).
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
 * @brief Tests the file_line_delete function in a fail case (line number out of range).
 */
TEST_F(CarTest, TestFileDeleteFail_2) {
  ASSERT_EQ(fail, file_line_delete("test4.bin", 100));
}

/**
 * @brief Tests the user_login function in a fail case
 */
TEST_F(CarTest, TestUserLoginFail) {
  EXPECT_EQ(fail, user_login("username", "passwordaa", "usertest.bin"));
}

/**
 * @brief Tests the user_change_password function in a fail case
 */
TEST_F(CarTest, TestUserChangePasswordFail) {
  EXPECT_EQ(fail, user_change_password("recoverykey","newpassword", "usertest.bin"));
}

/**
 * @brief Tests the user_register function.
 */
TEST_F(CarTest, TestUserRegister) {
  testString = "username/password/recoverykey";
  user_register("username","password","recoverykey","usertest.bin","Y");
  EXPECT_EQ(testString, file_read("usertest.bin"));
}

/**
 * @brief Tests the user_register function in a fail case
 */
TEST_F(CarTest, TestUserRegisterFail) {
  EXPECT_EQ(fail, user_register("username", "password", "recoverykey", "usertest.bin", "N"));
}

/**
 * @brief Tests the user_login function.
 */
TEST_F(CarTest, TestUserLogin) {
  EXPECT_EQ(success, user_login("username", "password", "usertest.bin"));
}

/**
 * @brief Tests the user_login function in a fail case
 */
TEST_F(CarTest, TestUserLoginFail_2) {
  EXPECT_EQ(fail, user_login("usernameaa", "passwordaa", "usertest.bin"));
}


/**
 * @brief Tests the user_change_password function.
 */
TEST_F(CarTest, TestUserChangePassword) {
  EXPECT_EQ(success, user_change_password("recoverykey", "newpassword", "usertest.bin"));
}

/**
 * @brief Tests the user_change_password function in a fail case
 */
TEST_F(CarTest, TestUserChangePasswordFail_2) {
  EXPECT_EQ(fail, user_change_password("recoverykeyaa","newpassword", "usertest.bin"));
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

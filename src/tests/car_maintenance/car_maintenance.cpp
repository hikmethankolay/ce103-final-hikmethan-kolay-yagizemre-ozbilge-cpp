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
 * @brief Tests the register_service_history_record function
 */
TEST_F(CarTest, TestRegisterService) {
  testString = "0-)VEHICLE MODEL | SERVICE KM | SERVICE PROVIDER | SERVICE COST\n1-)Audi   10500   Service   1500\n";
  register_service_history_record("service_history_test.bin","Audi",10500,"Service",1500);
  EXPECT_EQ(testString,file_read("service_history_test.bin"));
}

/**
 * @brief Tests the edit_service_history_record function
 */
TEST_F(CarTest, TestEditService) {
  testString = "0-)VEHICLE MODEL | SERVICE KM | SERVICE PROVIDER | SERVICE COST\n1-)Mercedes   12500   Service   1700\n";
  edit_service_history_record("service_history_test.bin", 1, "Mercedes", 12500, "Service", 1700);
  EXPECT_EQ(testString, file_read("service_history_test.bin"));
}
/**
 * @brief Tests the edit_service_history_record for fail case
 */
TEST_F(CarTest, TestEditServiceFail) {
  EXPECT_EQ(fail, edit_service_history_record("service_history_testfail.bin", 1, "Mercedes", 12500, "Service", 1700));
}

/**
 * @brief Tests the delete_service_history_record function
 */
TEST_F(CarTest, TestDeleteService) {
  testString = "0-)VEHICLE MODEL | SERVICE KM | SERVICE PROVIDER | SERVICE COST\n";
  delete_service_history_record("service_history_test.bin", 1);
  EXPECT_EQ(testString, file_read("service_history_test.bin"));
}
/**
 * @brief Tests the delete_service_history_record for fail case
 */
TEST_F(CarTest, TestDeleteServiceFail) {
  EXPECT_EQ(fail, delete_service_history_record("service_history_testfail.bin", 1));
}
/**
 * @brief Tests the register_expense_record function
 */
TEST_F(CarTest, TestRegisterExpense) {
  testString = "0-)CAR MODEL | EXPENSE DATE | EXPENSE TYPE | EXPENSE\n1-)Audi   10/10/2023   Brake   15000\n";
  register_expense_record("expense_logging_records_test.bin", "Audi", "10/10/2023", "Brake", 15000);
  EXPECT_EQ(testString, file_read("expense_logging_records_test.bin"));
}

/**
 * @brief Tests the edit_service_history_record function
 */
TEST_F(CarTest, TestEditExpense) {
  testString = "0-)CAR MODEL | EXPENSE DATE | EXPENSE TYPE | EXPENSE\n1-)Mercedes   11/11/2023   Oil   17000\n";
  edit_expense_record("expense_logging_records_test.bin", 1,"Mercedes", "11/11/2023", "Oil", 17000);
  EXPECT_EQ(testString, file_read("expense_logging_records_test.bin"));
}
/**
 * @brief Tests the edit_service_history_record for fail case
 */
TEST_F(CarTest, TestEditExpenseFail) {
  EXPECT_EQ(fail, edit_expense_record("service_history_testfailaaaa.bin", 1, "Audi", "10/10/2023", "Brake", 15000));
}

/**
 * @brief Tests the delete_service_history_record function
 */
TEST_F(CarTest, TestDeleteExpense) {
  testString = "0-)CAR MODEL | EXPENSE DATE | EXPENSE TYPE | EXPENSE\n";
  delete_expense_record("expense_logging_records_test.bin", 1);
  EXPECT_EQ(testString, file_read("expense_logging_records_test.bin"));
}
/**
 * @brief Tests the delete_service_history_record for fail case
 */
TEST_F(CarTest, TestDeleteExpenseFail) {
  EXPECT_EQ(fail, delete_expense_record("expense_logging_records_testaaa.bin", 1));
}

/**
 * @brief Tests the register_maintenance_reminder_record function
 */
TEST_F(CarTest, TestRegisterReminder) {
  testString = "0-)VEHICLE MODEL | SERVICE KM | PLANNED SERVICE TYPE\n1-)Audi   1000   Brake\n";
  register_maintenance_reminder_record("reminder_logging_records_test.bin","Audi",1000,"Brake");
  EXPECT_EQ(testString, file_read("reminder_logging_records_test.bin"));
}

/**
 * @brief Tests the edit_maintenance_reminder_record function
 */
TEST_F(CarTest, TestEditReminder) {
  testString = "0-)VEHICLE MODEL | SERVICE KM | PLANNED SERVICE TYPE\n1-)Mercedes   1100   Oil\n";
  edit_maintenance_reminder_record("reminder_logging_records_test.bin",1,"Mercedes", 1100, "Oil");
  EXPECT_EQ(testString, file_read("reminder_logging_records_test.bin"));
}
/**
 * @brief Tests the edit_service_history_record for fail case
 */
TEST_F(CarTest, TestEditReminderFail) {
  EXPECT_EQ(fail, edit_maintenance_reminder_record("reminder_logging_records_testaaa.bin", 1));
}

/**
 * @brief Tests the delete_service_history_record function
 */
TEST_F(CarTest, TestDeleteReminder) {
  testString = "0-)VEHICLE MODEL | SERVICE KM | PLANNED SERVICE TYPE\n";
  delete_maintenance_reminder_record("reminder_logging_records_test.bin",1);
  EXPECT_EQ(testString, file_read("reminder_logging_records_test.bin"));
}
/**
 * @brief Tests the delete_service_history_record for fail case
 */
TEST_F(CarTest, TestDeleteReminderFail) {
  EXPECT_EQ(fail, delete_maintenance_reminder_record("reminder_logging_records_testaaaa.bin", 1));
}

TEST_F(CarTest, TestRegisterFuel) {
  testString = "0-)CAR MODEL | FUEL CONSUMED(L/100KM)\n1-)BWM   5.000000\n";
  register_fuel_efficiency_record("fuel_efficiency_records_test.bin", "BWM", 50, 1000);
  EXPECT_EQ(testString, file_read("fuel_efficiency_records_test.bin"));
}

/**
 * @brief Tests the edit_maintenance_reminder_record function
 */
TEST_F(CarTest, TestEditFuel) {
  testString = "0-)CAR MODEL | FUEL CONSUMED(L/100KM)\n1-)Audi   6.000000\n";
  edit_fuel_efficiency_record("fuel_efficiency_records_test.bin",1, "Audi", 60, 1000);
  EXPECT_EQ(testString, file_read("fuel_efficiency_records_test.bin"));
}
/**
 * @brief Tests the edit_service_history_record for fail case
 */
TEST_F(CarTest, TestEditFuelFail) {
  EXPECT_EQ(fail, edit_maintenance_reminder_record("fuel_efficiency_records_testaaa.bin", 1));
}

/**
 * @brief Tests the delete_service_history_record function
 */
TEST_F(CarTest, TestDeleteFuel) {
  testString = "0-)CAR MODEL | FUEL CONSUMED(L/100KM)\n";
  delete_fuel_efficiency_record("fuel_efficiency_records_test.bin",1);
  EXPECT_EQ(testString, file_read("fuel_efficiency_records_test.bin"));
}
/**
 * @brief Tests the delete_service_history_record for fail case
 */
TEST_F(CarTest, TestDeleteFuelFail) {
  EXPECT_EQ(fail, delete_maintenance_reminder_record("fuel_efficiency_records_testaaa.bin", 1));
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

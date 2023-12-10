/**
 * @file car_maintenance_lib.h
 *
 * @brief Provides functions for file operations
 */
#ifndef CAR_MAINTENANCE_LIB_H
#define CAR_MAINTENANCE_LIB_H
#include <string>
/**
 * @brief Using the standard C++ namespace to simplify code with standard library elements.
 *
 */
using namespace std;

/**
 * @brief Opens a binary file, deletes all of its content and write given text to it.
 *
 *
 * @param file_name The name of the file to write.
 * @param text The text to write.
 * @return 0 on success.
 */
int file_write(string file_name, string text);

/**
 * @brief Opens a binary file, Reads all of its content, seperate line with "\n" and write them to console, also returns a string for unit tests.
 *
 *
 * @param file_name The name of the file to read from.
 * @return The contents of the file as a string.
 */
string file_read(string file_name);

/**
 * @brief Appends given text to a binary file with a automatic calculated line number. Calcultes new lines line number by finding last lines line number.
 *
 *
 * @param file_name The name of the file to append to.
 * @param text The text to append to the file.
 * @return 0 on success.
 */
int file_append(string file_name, string text);

/**
 * @brief This function Opens a binary file, finds the line that user wants to edit and replace it wih new text.
 *
 *
 * @param file_name The name of the file to edit.
 * @param line_number_to_edit The line number to edit.
 * @param new_line The new text to replace the existing line.
 * @return 0 on success.
 */
int file_edit(string file_name, int line_number_to_edit, string new_line);

/**
 * @brief This function Opens a binary file, deletes the line user wanted and make adjustments on line number acordingly.
 *
 *
 * @param file_name The name of the file to delete the line from.
 * @param line_number_to_delete The line number to delete.
 * @return 0 on success.
 */
int file_line_delete(string file_name, int line_number_to_delete);

/**
 * @brief This function is for user register
 *
 * Function creates a user.bin file and writes inputted username and password in it.
 *
 * @return 0 on success.
 * @return -1 on faill.
 */
int user_register(string new_username = "None", string new_password = "None", string new_recovery_key = "None", string user_file = "user.bin", string choice = "None");

/**
 * @brief This function is for user login
 *
 * Function read user.bin file and checks if username and password matchs with inputted username and password
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_login(string username = "None", string password = "None", string user_file = "user.bin");

/**
 * @brief This function changes password of user.
 *
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_change_password(string recovery_key = "None", string new_password = "None", string user_file = "user.bin");

/**
 * @brief This function prints service history records to console
 *
 *
 */
int show_record(string file_name);

/**
 * @brief This function register records to service_history_records.bin.
 *
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int register_service_history_record(string file_name = "service_history_records.bin", string vehicle_model = "None", int service_km = 1, int next_service_km = 1, int service_cost = 1);

/**
 * @brief This function register records to service_history_records.bin.
 *
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int register_expense_record(string file_name = "expense_logging_records.bin", int spare_part_expense = 1, int labor_expense = 1, int insurance_expense = 1);

#endif // CAR_MAINTENANCE_LIB_H

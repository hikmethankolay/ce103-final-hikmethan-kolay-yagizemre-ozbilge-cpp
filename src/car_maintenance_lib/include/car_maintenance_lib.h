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
 * @brief Writes the specified text to a binary file after prepending "0-)" and appending a newline.
 *
 * This function opens the specified binary file, deletes its contents, and writes the modified text in binary format.
 *
 * @param file_name The name of the file to write to.
 * @param text The text to write to the file.
 * @return 0 on success.
 */
int file_write(string file_name, string text);

/**
 * @brief Appends the specified text to a binary file, incrementing the line number.
 *
 * This function opens the specified binary file, finds the last line, increments its line number,
 * and appends the modified text in binary format.
 *
 * @param file_name The name of the file to append to.
 * @param text The text to append to the file.
 * @return 0 on success.
 */
int file_append(string file_name, string text);

/**
 * @brief Reads the contents of a binary file and returns them as a string.
 *
 * This function opens the specified binary file, reads its contents, and returns them as a string.
 *
 * @param file_name The name of the file to read from.
 * @return The contents of the file as a string.
 */
string file_read(string file_name);

/**
 * @brief Edits the specified line in a binary file with new text.
 *
 * This function opens the specified binary file, finds the line with the given line number, and replaces it with the new text.
 *
 * @param file_name The name of the file to edit.
 * @param line_number_to_edit The line number to edit.
 * @param new_line The new text to replace the existing line.
 * @return 0 on success.
 */
int file_edit(string file_name, int line_number_to_edit, string new_line);

/**
 * @brief Deletes the specified line in a binary file.
 *
 * This function opens the specified binary file, finds the line with the given line number, and deletes it.
 *
 * @param file_name The name of the file to delete the line from.
 * @param line_number_to_delete The line number to delete.
 * @return 0 on success.
 */
int file_line_delete(string file_name, int line_number_to_delete);

#endif // CAR_MAINTENANCE_LIB_H

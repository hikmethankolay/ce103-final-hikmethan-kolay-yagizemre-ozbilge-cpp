/**
 * @file car_maintenance_lib.h
 *
 * @brief Provides functions for file operations
 */

#ifndef CAR_MAINTENANCE_LIB_H
#define CAR_MAINTENANCE_LIB_H

#include <string>
using namespace std;

int file_write(string file_name, string text);

int file_append(string file_name, string text);

string file_read(string file_name);

int file_edit(string file_name, int line_number_to_edit, string new_line);

int file_line_delete(string file_name, int line_number_to_delete);

#endif // CAR_MAINTENANCE_LIB_H

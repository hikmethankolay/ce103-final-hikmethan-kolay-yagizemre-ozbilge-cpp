/**
 * @file car_maintenance_app.cpp
 * @brief Car maintenance Application main file
 */

#include <iostream>
#include <string>
#include <conio.h>
#include "../../car_maintenance_lib/include/car_maintenance_lib.h"  // Adjust this include path based on your project structure

/**
 * @brief Diplays the menu for operations.
 *
 */
void displayMenu(const char *options[], int size, int selected) {
  system("cls"); // Clears the console screen
  std::cout << "----------Main Menu----------\n";

  for (int i = 0; i < size; ++i) {
    if (i == selected) {
      std::cout << options[i] << " <--" << std::endl;
    } else {
      std::cout << options[i] << std::endl;
    }
  }
}

/**
 * @brief Car maintenance Application main function.
 *
 */
int main() {
  const char *menuOptions[] = {
    "1-)Login",
    "2-)Register",
    "3-)Change Password",
    "4-)Exit"
  };
  const int menuSize = sizeof(menuOptions) / sizeof(menuOptions[0]);
  int selectedOption = 0;
  char key;

  do {
    displayMenu(menuOptions, menuSize, selectedOption);
    key = _getch(); // Get a character from the console without waiting for Enter

    switch (key) {
      case 72: // Up arrow key
        selectedOption = (selectedOption - 1 + menuSize) % menuSize;
        break;

      case 80: // Down arrow key
        selectedOption = (selectedOption + 1) % menuSize;
        break;
    }
  } while (key != 13); // 13 is the ASCII code for Enter key

  // Handle selected option
  switch (selectedOption) {
    case 0:
      std::cout << "Login selected.\n";
      // Handle User Authentication
      break;

    case 1:
      std::cout << "Register selected.\n";
      // Handle Service History Tracking
      break;

    case 2:
      std::cout << "Change Password selected.\n";
      // Handle Maintenance Reminders
      break;

    case 3:
      return 0;
  }
}

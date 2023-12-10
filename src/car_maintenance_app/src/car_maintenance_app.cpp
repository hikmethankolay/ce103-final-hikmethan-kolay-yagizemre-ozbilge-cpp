/**
 * @file car_maintenance_app.cpp
 * @brief Car maintenance Application main file
 */

#include <iostream>
#include <string>
#include <conio.h>
#include "../../car_maintenance_lib/include/car_maintenance_lib.h"  // Adjust this include path based on your project structure


/**
 * @brief Car maintenance Application main function.
 *
 */
int main() {
login:
  int selectedOption;
  int selectedOption2;
  cout << "----------Login----------\n";
  cout << "1-)Login\n";
  cout << "2-)Register\n";
  cout << "3-)Change Password\n";
  cout << "4-)Exit\n";
  cout << "Make a choice(1-4)";
  cin >> selectedOption;

  switch (selectedOption) {
    case 1:
      user_login();

      if (user_login() == 0) {
main_menu:
        cout << "----------Main Menu----------\n";
        cout << "1-)Service History Tracking\n";
        cout << "2-)Maintenance Reminders\n";
        cout << "3-)Expense Logging:\n";
        cout << "4-)Fuel Efficiency Reports\n";
        cout << "5-)Exit\n";
        cout << "Make a choice(1-6)";
        cin >> selectedOption2;

        switch (selectedOption2)
        case 1:
      case 2:
      case 3:
      case 4:
      case 5: {
        default:
          goto main_menu;
        }
      } else {
        goto login;
      }

    case 2:
      user_register();
      goto login;

    case 3:
      user_change_password();
      goto login;

    case 4:
      return 0;

    default:
      goto login;
  }
}

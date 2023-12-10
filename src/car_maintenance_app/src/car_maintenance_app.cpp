#include <iostream>
#include <string>
#include "../../car_maintenance_lib/include/car_maintenance_lib.h"  // Adjust this include path based on your project structure

using namespace std;

int main() {
  bool run = true;

  do {
    int selectedOption;
    int selectedOption2;
    int selectedOption3;
    int selectedOption4;
    int selectedOption5;
    int selectedOption6;
    cout << "----------Login----------\n";
    cout << "1-)Login\n";
    cout << "2-)Register\n";
    cout << "3-)Change Password\n";
    cout << "4-)Exit\n";
    cout << "Make a choice(1-4):";
    cin >> selectedOption;

    switch (selectedOption) {
      case 1: {
        if (user_login() == 0) {
          cout << "\n----------Main Menu----------\n";
          cout << "1-)Service History Tracking\n";
          cout << "2-)Maintenance Reminders\n";
          cout << "3-)Expense Logging\n";
          cout << "4-)Fuel Efficiency Reports\n";
          cout << "5-)Exit\n";
          cout << "Make a choice(1-5):";
          cin >> selectedOption2;

          switch (selectedOption2) {
            case 1:
              cout << "\n----------Service History Tracking----------\n";
              cout << "1-)Show Service History Record\n";
              cout << "2-)Register Service History Record\n";
              cout << "3-)Edit Service History Record\n";
              cout << "4-)Delete Service History Record\n";
              cout << "5-)Previous Menu\n";
              cout << "Make a choice(1-5):";
              cin >> selectedOption3;

              if (selectedOption3 == 1) {
                show_record("service_history_records.bin");
              } else if (selectedOption3 == 2) {
                register_service_history_record();
              }

            case 2:
            case 3:
            case 4:
            case 5:
              run = false;

            default:
              break;
          }
        } else {
          continue;
        }

        break;
      }

      case 2:
        user_register();
        continue;

      case 3:
        user_change_password();
        continue;

      case 4:
        run = false;
        break;

      default:
        continue;
    }
  } while (run);

  return 0;
}

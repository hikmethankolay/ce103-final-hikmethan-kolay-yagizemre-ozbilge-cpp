#include <iostream>
#include <string>
#include "../../car_maintenance_lib/include/car_maintenance_lib.h"  // Adjust this include path based on your project structure

using namespace std;

int main() {
  bool run = true;

  do {
    int login_menu;
    int main_menu;
    int service_menu;
    int maintenance_reminder_menu;
    int expense_menu;
    int fuel_efficiency_menu;
    cout << "----------Login----------\n";
    cout << "1-)Login\n";
    cout << "2-)Register\n";
    cout << "3-)Change Password\n";
    cout << "4-)Exit\n";
    cout << "Make a choice(1-4):";
    cin >> login_menu;

    switch (login_menu) {
      case 1: {
        if (user_login() == 0) {
          do {
            cout << "\n----------Main Menu----------\n";
            cout << "1-)Service History Tracking\n";
            cout << "2-)Maintenance Reminders\n";
            cout << "3-)Expense Logging\n";
            cout << "4-)Fuel Efficiency Reports\n";
            cout << "5-)Exit\n";
            cout << "Make a choice(1-5):";
            cin >> main_menu;

            switch (main_menu) {
              case 1:
                cout << "\n----------Service History Tracking----------\n";
                cout << "1-)Show Service History Record\n";
                cout << "2-)Register Service History Record\n";
                cout << "3-)Edit Service History Record\n";
                cout << "4-)Delete Service History Record\n";
                cout << "5-)Previous Menu\n";
                cout << "Make a choice(1-5):";
                cin >> service_menu;

                if (service_menu == 1) {
                  show_record("service_history_records.bin");
                } else if (service_menu == 2) {
                  register_service_history_record();
                } else if (service_menu == 3) {
                  edit_service_history_record();
                } else if (service_menu == 4) {
                  delete_service_history_record();
                } else if (service_menu == 5) {
                  continue;
                }

              case 2:
                cout << "\n----------Maintenance Reminder Records----------\n";
                cout << "1-)Show Maintenance Reminder Records\n";
                cout << "2-)Register Maintenance Reminder Records\n";
                cout << "3-)Edit Maintenance Reminder Records\n";
                cout << "4-)Delete Maintenance Reminder Records\n";
                cout << "5-)Previous Menu\n";
                cout << "Make a choice(1-5):";
                cin >> maintenance_reminder_menu;

                if (maintenance_reminder_menu == 1) {
                  show_record("maintenance_reminder_records.bin");
                } else if (maintenance_reminder_menu == 2) {
                } else if (maintenance_reminder_menu == 3) {
                } else if (maintenance_reminder_menu == 4) {
                } else if (service_menu == 5) {
                  continue;
                }

              case 3:
                cout << "\n----------Expense Tracking Records----------\n";
                cout << "1-)Show Expense Tracking Records\n";
                cout << "2-)Register Expense Tracking Records\n";
                cout << "3-)Edit Expense Tracking Records\n";
                cout << "4-)Delete Expense Tracking Records\n";
                cout << "5-)Previous Menu\n";
                cout << "Make a choice(1-5):";
                cin >> expense_menu;

                if (expense_menu == 1) {
                  show_record("expense_records.bin");
                } else if (expense_menu == 2) {
                } else if (expense_menu == 3) {
                } else if (expense_menu == 4) {
                } else if (expense_menu == 5) {
                  continue;
                }

              case 4:
                cout << "\n----------Fuel Efficiency Records----------\n";
                cout << "1-)Show Fuel Efficiency Records\n";
                cout << "2-)Register Fuel Efficiency Records\n";
                cout << "3-)Edit Fuel Efficiency Records\n";
                cout << "4-)Delete Fuel Efficiency Records\n";
                cout << "5-)Previous Menu\n";
                cout << "Make a choice(1-5):";
                cin >> fuel_efficiency_menu;

                if (fuel_efficiency_menu == 1) {
                  show_record("fuel_efficiency_records.bin");
                } else if (fuel_efficiency_menu == 2) {
                } else if (fuel_efficiency_menu == 3) {
                } else if (fuel_efficiency_menu == 4) {
                } else if (fuel_efficiency_menu == 5) {
                  continue;
                }

              case 5:
                run = false;

              default:
                break;
            }
          } while (run);
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

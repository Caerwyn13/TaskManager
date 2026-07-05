#include <iostream>
#include <string>
#include "tasks.h"

using namespace std;

int main() {
    // Providing filename outputs the JSON to working directory
    const string taskFilePath = "tasks.json";
    TaskManager manager(taskFilePath);

    int choice = 0;
    do {
        cout << "\n=== TASK MANAGER ===\n";
        cout << "1. View Tasks\n";
        cout << "2. Add Task\n";
        cout << "3. Delete Task\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid selection. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                manager.viewTasks();
                break;
            case 2:
                manager.addTask();
                break;
            case 3:
                manager.deleteTask();
                break;
            case 4:
                cout << "Exiting application. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select 1-4.\n";
        }
    } while (choice != 4);

    return 0;
}

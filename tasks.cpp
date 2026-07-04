//
// Created by Caerwyn on 04/07/2026.
//

#include <iostream>
#include "tasks.h"

using namespace std;

// Displays all available information about given task
void printTask(const Task& task) {
    cout << "Task: " << task.title;
    cout << "\n  Description: " << task.description << "\n  Status: " << task.status << "\n  Priority: " << task.priority;
    cout << "\n  Deadline: ";
    if (task.deadline.empty()) { cout << "No deadline"; } else { cout << task.deadline; }

    cout << "\n  Tags: ";
    if (task.tags.empty()) {
        cout << "None";
    } else {
        for (size_t i = 0; i < task.tags.size(); ++i) {
            if (i > 0) {
                cout << ", ";
            }
            cout << task.tags[i];
        }
    }
    cout << endl << endl;
}
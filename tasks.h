//
// Created by Caerwyn on 04/07/2026.
//

#ifndef PERSONAL_DASHBOARD_TASKS_H
#define PERSONAL_DASHBOARD_TASKS_H
#include <string>
#include <vector>

using namespace std;

struct Task {
    string id;
    string title;
    string description;
    string status;
    vector<string> tags;
    string deadline;
    int priority{};
};

void printTask(const Task& task);

#endif //PERSONAL_DASHBOARD_TASKS_H

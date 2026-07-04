#include <iostream>
#include <string>
#include <vector>
#include "tasks.h"

using namespace std;

int main() {
    vector<Task> tasks = readTasksFromFile("C:/Users/Caerwyn/Desktop/Programming/C/Personal_Dashboard/tasks.json");

    addTask(tasks);

    for (const auto& task : tasks) {
        printTask(task);
    }


    return 0;
}
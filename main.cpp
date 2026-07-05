#include <iostream>
#include <string>
#include <vector>
#include "tasks.h"

using namespace std;

int main() {
    //TODO: Create selection menu
    //TODO: Allow for several commands (view tasks, add task) to be ran in one go
    //TODO: Add more commands (delete task, order tasks (in view tasks menu), change task metadata, etc.)
    const string taskFilePath = "tasks.json";
    vector<Task> tasks = readTasksFromFile(taskFilePath);

    addTask(tasks, taskFilePath);

    for (const auto& task : tasks) {
        printTask(task);
    }


    return 0;
}
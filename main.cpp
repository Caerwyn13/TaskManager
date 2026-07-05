#include <iostream>
#include <string>
#include <vector>
#include "tasks.h"

using namespace std;

int main() {
    const string taskFilePath = "tasks.json";
    vector<Task> tasks = readTasksFromFile(taskFilePath);

    addTask(tasks, taskFilePath);

    for (const auto& task : tasks) {
        printTask(task);
    }


    return 0;
}
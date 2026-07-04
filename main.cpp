#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "tasks.h"

using namespace std;
using json = nlohmann::json;

int main() {
    // Absolute path used as just "tasks.json" didn't work :(
    ifstream tasks_file("C:/Users/Caerwyn/Desktop/Programming/C/Personal_Dashboard/tasks.json");

    // Check if file has opened successfully
    if (!tasks_file.is_open()) {
        cerr << "Error opening tasks.json" << endl;
        return 1;
    }

    try {
        json data;
        tasks_file >> data;
        tasks_file.close();

        vector<Task> task_list;

        // Iterate through Tasks object
        if (data.contains("Tasks") && data["Tasks"].is_object()) {
            for (const auto& [task_id, task_details] : data["Tasks"].items()) {
                Task task;
                task.id = task_id;
                task.title = task_details.value("title", "Untitled Task");
                task.description = task_details.value("description", "");
                task.status = task_details.value("status", "TODO");
                task.priority = task_details.value("priority", 0);
                task.deadline = task_details.value("deadline", "No deadline");

                if (task_details.contains("tags") && task_details["tags"].is_array()) {
                    task.tags = task_details["tags"].get<vector<string>>();
                }

                task_list.push_back(task);
            }
        }

        // Print results to verify
        for (const auto& task : task_list) {
            printTask(task);
        }
    } catch (const json::parse_error& e) {
        cerr << "JSON Parsing error: " <<e.what() << endl;
        return 1;
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

struct Task {
    string id;
    string title;
    string description;
    string status;
    vector<string> tags;
    string deadline;
    int priority{};
};

int main() {
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
            cout << "Task: " << task.title << "\n  Tags: ";
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
    } catch (const json::parse_error& e) {
        cerr << "JSON Parsing error: " <<e.what() << endl;
        return 1;
    }

    return 0;
}
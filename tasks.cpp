//
// Created by Caerwyn on 04/07/2026.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>
#include "tasks.h"

#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;


// Helper function to split tags and trim spaces
vector<string> splitTags(const string& input) {
    vector<string> tags;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        size_t start = token.find_first_not_of(' ');
        size_t end = token.find_last_not_of(' ');
        if (start != string::npos && end != string::npos) {
            tags.push_back(token.substr(start, end - start + 1));
        }
    }
    return tags;
}

void addTask(vector<Task>& tasks) {
    string id, title, description, status, deadline, tagsInput;
    int priority;

    cout << "\nAdding a new Task:" << endl;

    cout << "Enter the title: ";
    getline(cin >> ws, title);

    cout << "Enter a description: ";
    getline(cin, description);

    cout << "Enter its current status (e.g., TODO): ";
    getline(cin, status);

    cout << "Enter its priority as a positive integer: ";
    cin >> priority;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

    cout << "Enter a deadline (leave blank for no deadline): ";
    getline(cin, deadline);

    cout << "Enter any tags for this task (separate with a comma): ";
    getline(cin, tagsInput);
    vector<string> tags = splitTags(tagsInput);

    // Determine next ID based on current vector size
    id = to_string(tasks.size());

    // Create temporary local Task object
    Task newTask{id, title, description, status, tags, deadline, priority};
    tasks.push_back(newTask);

    // LOAD EXISTING JSON FILE
    json fileData;
    if (ifstream inFile("tasks.json"); inFile.is_open()) {
        inFile >> fileData; // Read current file contents into the JSON object
        inFile.close();
    }

    // Ensure root "Tasks" object exists if file was empty
    if (!fileData.contains("Tasks")) {
        fileData["Tasks"] = json::object();
    }

    // UPDATE WITH THE NEW TASK DATA
    fileData["Tasks"][id] = newTask;

    // WRITE BACK TO FILE WITH PRETTY-PRINTING (2 spaces)
    if (ofstream outFile("tasks.json"); outFile.is_open()) {
        outFile << fileData.dump(2);
        outFile.close();
        cout << "\nTask successfully saved to tasks.json! (ID: " << id << ")\n";
    } else {
        cerr << "\nError: Could not save data to file!\n";
    }
}

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

vector<Task> readTasksFromFile(const string& path) {
    // Absolute path used as just "tasks.json" didn't work :(
    ifstream file(path);

    // Check if file has opened successfully
    if (!file.is_open()) {
        cerr << "Error opening tasks.json" << endl;
        return {};
    }
    try {
        nlohmann::json data;
        file >> data;
        file.close();

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
        return task_list;
    } catch (const json::parse_error& e) {
        cerr << "JSON Parsing error: " <<e.what() << endl;
        return {};
    }

}
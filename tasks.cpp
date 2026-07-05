#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>

#include "tasks.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

TaskManager::TaskManager(string path) : filePath(std::move(path)) {
    loadTasksFromFile();
}


vector<string> TaskManager::splitTags(const string& input) {
    vector<string> tags;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        const size_t start = token.find_first_not_of(" \t");
        if (const size_t end = token.find_last_not_of(" \t"); start != string::npos && end != string::npos) {
            tags.push_back(token.substr(start, end - start + 1));
        }
    }
    return tags;
}

void TaskManager::loadTasksFromFile() {
    ifstream file(filePath);
    if (!file.is_open()) {
        return; // File doesn't exist yet; start with an empty list
    }
    
    try {
        json data;
        file >> data;
        file.close();

        tasks.clear();
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
                tasks.push_back(task);
            }
        }
    } catch (const json::parse_error& e) {
        cerr << "JSON Parsing error: " << e.what() << endl;
    }
}

void TaskManager::saveTasksToFile() const {
    json fileData;
    fileData["Tasks"] = json::object();

    for (const auto& task : tasks) {
        fileData["Tasks"][task.id] = task;
    }

    if (ofstream outFile(filePath); outFile.is_open()) {
        outFile << fileData.dump(2);
    } else {
        cerr << "\nError: Could not save data to " << filePath << endl;
    }
}

void TaskManager::addTask() {
    string title, description, status, deadline, tagsInput;
    int priority;

    cout << "\n--- Adding a New Task ---" << endl;
    cout << "Enter title: ";
    getline(cin >> ws, title);

    cout << "Enter description: ";
    getline(cin, description);

    cout << "Enter status (e.g., TODO, WIP): ";
    getline(cin, status);

    cout << "Enter priority (integer): ";
    while (!(cin >> priority)) {
        cout << "Invalid input. Please enter an integer for priority: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter deadline (or press Enter to skip): ";
    getline(cin, deadline);
    if (deadline.empty()) deadline = "No deadline";

    cout << "Enter tags (comma separated): ";
    getline(cin, tagsInput);

    // Generate simple sequential ID
    const string id = to_string(tasks.size());

    tasks.push_back(Task{id, title, description, status, splitTags(tagsInput), deadline, priority});
    saveTasksToFile();
    cout << "Task successfully saved! (ID: " << id << ")\n";
}

void TaskManager::deleteTask() {
    if (tasks.empty()) {
        cout << "\nNo tasks available to delete.\n";
        return;
    }

    string id;
    cout << "\nEnter the ID of the task to delete: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (const auto it = ranges::remove_if(tasks, [&id](const Task& t) { return t.id == id; }).begin(); it != tasks.end()) {
        tasks.erase(it, tasks.end());

        // RE-INDEXING: Shift all IDs down sequentially to close the gap
        for (size_t i = 0; i < tasks.size(); ++i) {
            tasks[i].id = to_string(i);
        }

        saveTasksToFile();
        cout << "Task " << id << " deleted successfully. Remaining tasks re-indexed.\n";
    } else {
        cout << "Task ID not found.\n";
    }
}


void TaskManager::viewTasks() const {
    if (tasks.empty()) {
        cout << "\nYour task board is completely empty!\n";
        return;
    }
    cout << "\n================ CURRENT TASKS ================\n";
    for (const auto& task : tasks) {
        printTask(task);
    }
    cout << "===============================================\n";
}

void TaskManager::printTask(const Task& task) {
    cout << "[" << task.id << "] " << task.title << " | Status: " << task.status << " | Priority: " << task.priority << "\n";
    cout << "    Description: " << task.description << "\n";
    cout << "    Deadline:    " << task.deadline << "\n";
    cout << "    Tags:        ";
    if (task.tags.empty()) {
        cout << "None";
    } else {
        for (size_t i = 0; i < task.tags.size(); ++i) {
            cout << task.tags[i] << (i < task.tags.size() - 1 ? ", " : "");
        }
    }
    cout << "\n\n";
}

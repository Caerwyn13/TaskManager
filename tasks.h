#ifndef PERSONAL_DASHBOARD_TASKS_H
#define PERSONAL_DASHBOARD_TASKS_H

#include <string>
#include <vector>
#include "nlohmann/json.hpp"

struct Task {
    std::string id{};
    std::string title{};
    std::string description{};
    std::string status{};
    std::vector<std::string> tags{};
    std::string deadline{};
    int priority{0};
};

// JSON macro to automate conversion (excluding ID as it serves as the JSON object key)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Task, title, description, status, tags, deadline, priority)

class TaskManager {
    std::string filePath;
    std::vector<Task> tasks;

    static std::vector<std::string> splitTags(const std::string& input);
    void saveTasksToFile() const;
    void loadTasksFromFile();

public:
    explicit TaskManager(std::string path);

    void addTask();
    void deleteTask();
    void viewTasks() const;
    static void printTask(const Task& task) ;
};

#endif //PERSONAL_DASHBOARD_TASKS_H

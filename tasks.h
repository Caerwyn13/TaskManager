//
// Created by Caerwyn on 04/07/2026.
//

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

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Task, title, description, status, tags, deadline, priority)

void addTask(std::vector<Task>& tasks);
void printTask(const Task& task);
std::vector<Task> readTasksFromFile(const std::string& path);

#endif //PERSONAL_DASHBOARD_TASKS_H

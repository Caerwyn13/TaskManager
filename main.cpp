#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

struct Task {
    int id;
    string title;
    string description;
    string status;
    vector<string> tags;
    string deadline;
    int priority;
};

int main() {
    const json j = json::parse("{}");
    cout << "Hello World!" << endl;
}
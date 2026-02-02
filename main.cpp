#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Task {
    int id;
    string description;
    bool completed;
};
class TaskManager {
private:
    vector<Task> tasks;
    string filename;
    int nextId;
    
    HANDLE hConsole;
    
public:
    TaskManager(const string& file) : filename(file), nextId(1) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        loadTasks();
    }
    ~TaskManager() {
        saveTasks();
    }
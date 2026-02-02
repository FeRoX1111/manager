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
    void loadTasks() {
        ifstream file(filename);
        if (file.is_open()) {
            tasks.clear();
            Task task;
            while (file >> task.id >> task.completed) {
                file.ignore();
                getline(file, task.description);
                tasks.push_back(task);
                if (task.id >= nextId) nextId = task.id + 1;
            }
            file.close();
            
            SetConsoleTextAttribute(hConsole, 10); 
            cout << "Задачи загружены из файла: " << filename << endl;
            SetConsoleTextAttribute(hConsole, 7); 
        }
    }
    void saveTasks() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.id << " " << task.completed << " "
                     << task.description << endl;
            }
            file.close();
            
            SetConsoleTextAttribute(hConsole, 11); 
            cout << "Задачи сохранены в файл: " << filename << endl;
            SetConsoleTextAttribute(hConsole, 7); 
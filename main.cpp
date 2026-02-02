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
            } else {
            SetConsoleTextAttribute(hConsole, 12);
            cerr << "Ошибка сохранения файла!" << endl;
            SetConsoleTextAttribute(hConsole, 7); 
        }
    }
    
    void addTask(const string& description) {
        tasks.push_back({nextId++, description, false});
        
        SetConsoleTextAttribute(hConsole, 10); 
        cout << "Задача добавлена (ID: " << tasks.back().id << ")" << endl;
        SetConsoleTextAttribute(hConsole, 7); 
    void completeTask(int id) {
        auto it = find_if(tasks.begin(), tasks.end(),
                         [id](const Task& t) { return t.id == id; });
         if (it != tasks.end()) {
            it->completed = true;
            
            SetConsoleTextAttribute(hConsole, 14); 
            cout << "Задача " << id << " отмечена как выполненная" << endl;
            SetConsoleTextAttribute(hConsole, 7); 
        } else {
            SetConsoleTextAttribute(hConsole, 12); 
            cerr << "Задача с ID " << id << " не найдена!" << endl;
            SetConsoleTextAttribute(hConsole, 7); 
        }
    }
    void deleteTask(int id) {
        auto it = find_if(tasks.begin(), tasks.end(),
                         [id](const Task& t) { return t.id == id; });
        
        if (it != tasks.end()) {
            tasks.erase(it);
            
            SetConsoleTextAttribute(hConsole, 12); 
            cout << "Задача " << id << " удалена" << endl;
            SetConsoleTextAttribute(hConsole, 7); 
        } else {
            SetConsoleTextAttribute(hConsole, 12); // Красный
            cerr << "Задача с ID " << id << " не найдена!" << endl;
            SetConsoleTextAttribute(hConsole, 7); // Белый
        }
    }
    
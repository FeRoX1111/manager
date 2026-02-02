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
            SetConsoleTextAttribute(hConsole, 12); 
            cerr << "Задача с ID " << id << " не найдена!" << endl;
            SetConsoleTextAttribute(hConsole, 7); 
        }
    }
    void displayTasks() const {
        system("cls"); 
        
        SetConsoleTextAttribute(hConsole, 11); 
        cout << "========== СПИСОК ЗАДАЧ ==========" << endl;
        SetConsoleTextAttribute(hConsole, 7); 
        
        if (tasks.empty()) {
            cout << "Список задач пуст" << endl;
            return;
        }
        
        for (const auto& task : tasks) {
            if (task.completed) {
                SetConsoleTextAttribute(hConsole, 8); 
                cout << "[X] ";
            } else {
                SetConsoleTextAttribute(hConsole, 10); 
                cout << "[ ] ";
            }
            cout << "ID: " << task.id << " | ";
            cout << task.description << endl;
            
            SetConsoleTextAttribute(hConsole, 7); 
        
        SetConsoleTextAttribute(hConsole, 11); 
        cout << "==================================" << endl;
        SetConsoleTextAttribute(hConsole, 7); 
    }
    
    void displayMenu() {
        SetConsoleTextAttribute(hConsole, 14); 
        cout << "\n=== МЕНЕДЖЕР ЗАДАЧ ===" << endl;
        cout << "1. Показать все задачи" << endl;
        cout << "2. Добавить задачу" << endl;
        cout << "3. Отметить задачу как выполненную" << endl;
        cout << "4. Удалить задачу" << endl;
        cout << "5. Сохранить и выйти" << endl;
        cout << "======================" << endl;
        SetConsoleTextAttribute(hConsole, 7); 
        cout << "Выберите действие: ";
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    SetConsoleTitle("Менеджер задач");
    
    TaskManager manager("tasks.txt");
    int choice;
    string input;
    int taskId;
    
    do {
        manager.displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                manager.displayTasks();
                break;
                
            case 2:
                cout << "Введите описание задачи: ";
                getline(cin, input);
                manager.addTask(input);
                break;
                
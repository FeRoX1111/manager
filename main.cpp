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

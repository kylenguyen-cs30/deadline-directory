#ifndef DOIT_CPP
#define DOIT_CPP
#include "iostream"
#include "fstream"
#include "vector"
#include "chrono"
#include "ctime"
#include <limits>
#include "iomanip"
#include "sstream"
#include "cassert"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Task
{
    string description;
    string dueDate;
    vector<Task> subTask;

    Task(string desc, string due, vector<Task> sub = vector<Task>()) : description(desc), dueDate(due), subTask(sub) {}
};

void commands()
{
    cout << "1. Add Task "
         << " 2. Move Done!! "
         << " 3. What Date today? "
         << " 4. Move Back Todaychallenges "
         << " 5. Update "
         << " 6. Exit " << endl;
}
void addTasks(vector<Task> &todayChallenges);
void printList(vector<Task> &str);
void moveOverdueTasks(vector<Task> &todayChallenges, vector<Task> &unfinishedTask);
void writeFile(const vector<Task> &a, const vector<Task> &b, const vector<Task> &c);
void loadTasks( vector<Task>&a, vector<Task>&b, vector<Task>&c);
#endif // !DOIT_CPP

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
#include "cstdlib"

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
         << " 2. Move!! "
         << " 3. Quick save (moved to Update) "
         << " 4. Delete Task(still working on adding delete subtask)"
         << endl;

    cout << endl;

    cout << "5. Edit "
         << " 6. Update "
         << " 7. Exit "
         << endl;
}
void addTasks(vector<Task> &todayChallenges);
void printList(vector<Task> &str);
void moveOverdueTasks(vector<Task> &todayChallenges, vector<Task> &unfinishedTask);
void writeFile(const vector<Task> &a, const vector<Task> &b, const vector<Task> &c);
void loadTasks(vector<Task> &a, vector<Task> &b, vector<Task> &c);
string expandUserPath(const string &path);

// move
void fromTodayToDone(vector<Task> &a, vector<Task> &b);
void fromUnfishedToToday(vector<Task> &a, vector<Task> &b);
// remove task
void deleteTask(vector<Task> &a);
// auto all task in DONE list after 24 hours
void emptyAllDoneTask(vector<Task> &doneChallenges);
//edit task
void editTask(vector<Task>&task);
#endif // !DOIT_CPP

#include "header.hpp"

struct Task
{
    string description;
    string dueDate;
    bool isDone;
    vector<Task> subTask;
};
void displayMenu(vector<string> &todayChallenges);
void commands();
void displayTodayChallenges(vector<string> &todayChallenges);
void displayDonesList();
void displayUnfinished();

int main(int argc, char const *argv[])
{
    vector<string> todayChallenges;
    displayMenu(todayChallenges);
    return 0;
}

void commands()
{
    // Menu
    cout << "1. Add Task. (Subnote yes/no)" << endl;
    cout << "2. Check Node (Date Created, Extra Detail)" << endl;
    cout << "3. What Date today?" << endl;
    cout << "4. Move Task (Unfinished -> Toda Challenges)" << endl;
    cout << "5. Exit" << endl;
}

void displayMenu(vector<string> &todayChallenges)
{
    cout << "=================================================================================================================================================" << endl;
    cout << "JUST DO IT \n";
    cout << "=================================================================================================================================================" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    while (true)
    {
        cout << "=================================================================================================================================================" << endl;
        cout << "Today Challenges \n";
        displayTodayChallenges(todayChallenges);
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        cout << "DONES!!! \n";
        displayDonesList();
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        cout << "UNFINISHED \n";
        displayUnfinished();
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        commands();

        cout << endl;
        cout << endl;
        cout << endl;

        char choice;
        cout << "Please enter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {

            cout << "Add Task Action: " << endl;
            string str;
            cout << "Please enter your task : ";

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin, str);
            todayChallenges.push_back(str);
        }

        break;
        case '2':
            cout << "Check Task (Date created)" << endl;
            break;
        case '3':
        
            cout << "Today date " << endl;
            break;
        case '4':
            cout << "Test 4" << endl;
            break;
        case '5':
            cout << "Test 5" << endl;
            return;

        default:
            break;
        }
    }
}

void displayTodayChallenges(vector<string> &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        cout << i + 1 << ". " << str[i] << endl;
    }
}

void displayDonesList()
{
}

void displayUnfinished()
{
}
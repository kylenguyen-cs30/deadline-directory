#include "header.hpp"
struct Task
{
    string description;
    string dueDate;
    vector<Task> subTask;

    Task(string desc, string due, vector<Task> sub = vector<Task>()) : description(desc), dueDate(due), subTask(sub) {}
};

void printList(vector<Task> &str);

void commands()
{
    cout << "1. Add Task "
         << " 2. Move Done!! "
         << " 3. What Date today? "
         << " 4. Move Task "
         << " 5. Exit " << endl;
}

string getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}
void addTasks(vector<Task> &todayChallenges);

void displayMenu(vector<Task> &todayChallenges, vector<Task> &doneChallenges, vector<Task> &unfinishedTask)
{
    cout << "=================================================================================================================================================" << endl;
    cout << "JUST DO IT \n";
    cout << "=================================================================================================================================================" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    // unfinishedTask.push_back("feed my dog");
    // unfinishedTask.push_back("go for walk");

    while (true)
    {
        cout << "=================================================================================================================================================" << endl;
        cout << "Today Challenges \n";
        printList(todayChallenges);
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        cout << "DONES!!! \n";
        printList(doneChallenges);
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        cout << "UNFINISHED \n";
        printList(unfinishedTask);
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        commands();

        cout << endl;
        cout << endl;
        cout << endl;

        char choice;
        string input;
        bool validChoice = false;

        while (!validChoice)
        {
            cout << "Please enter your choice : ";
            getline(cin, input);

            // Check if the input is exactly one character and is a digit or a valid menu option
            if (input.length() == 1 && (isdigit(input[0]) || input[0] == '1' || input[0] == '2' || input[0] == '3' || input[0] == '4' || input[0] == '5'))
            {
                choice = input[0];
                validChoice = true;
            }
            else
            {
                cout << "Invalid choice. Please enter a valid menu option." << endl;
            }
        }

        switch (choice)
        {
        case '1':
        {
            // Add task
            addTasks(todayChallenges);
        }

        break;
        case '2':
        {

            cout << endl;
            cout << "Move Mode" << endl;
            cout << "Please enter the task number: ";
            int taskNum;
            cin >> taskNum;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (taskNum > (todayChallenges.size() + 1))
            {
                cout << "invalid input. Please try again !!. index size is bigger" << endl;
                break;
            }
            else
            {
                doneChallenges.push_back(todayChallenges[taskNum - 1]);
                todayChallenges.erase(todayChallenges.begin() + (taskNum - 1));
                cout << "Operation Successfull !!" << endl;
                cout << endl
                     << endl;
            }
        }
        break;
        case '3':

            cout << "Today date " << endl;

            break;
        case '4':
        {

            cout << "Move Mode" << endl;
            cout << "Please enter the task: " << endl;
            int taskNum;
            cin >> taskNum;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (taskNum > (unfinishedTask.size() + 1))
            {
                cout << "Invalid input. taskNum is bigger!!! " << endl;
                break;
            }
            else
            {
                todayChallenges.push_back(unfinishedTask[taskNum - 1]);
                unfinishedTask.erase(unfinishedTask.begin() + (taskNum - 1));
                cout << "Operation Successfull !!" << endl;
            }

            break;
        }
        case '5':
            cout << endl;
            cout << endl;
            cout << "Thank you for using my program!!!" << endl;
            return;

        default:
            break;
        }
    }
}

void addTasks(vector<Task> &todayChallenges)
{
    cout << "Add Task Mode " << endl;
    // Task Description
    string desc;
    cout << "Please enter your task : ";
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, desc);
    // Due Date
    string dueDate = getCurrentTime();
    // subtask question
    cout << "Is there any subtask ? (1. yes 2. no) " << endl;
    vector<Task> subTasks;
    int subTaskChoice;
    cin >> subTaskChoice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (subTaskChoice == 1)
    {
        string subDesc;
        cout << "Enter description for subtask: ";
        getline(cin, subDesc);
        string subDueDate = dueDate;
        subTasks.push_back(Task(subDesc, subDueDate));
        cout << "1. Continue (add another sub task) " << endl
             << "2. Stop (finish adding)" << endl
             << "3. Cancel (remove the last subttrack entered)" << endl;
        int choice;
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 2)
        {
            break;
        }
        else if (choice == 3 && !subTasks.empty())
        {
            subTasks.pop_back();
            if (subTasks.empty())
            {
                cout << "No subtask. Add subtask? (1. yes 2. no): ";
                cin >> subTaskChoice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    Task newTask = {desc, dueDate, subTasks};

    // capture the date

    todayChallenges.push_back(newTask);
}

void printList(vector<Task> &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        cout << i + 1 << ". " << str[i].description << " \t\t" << str[i].dueDate << endl;
    }
}
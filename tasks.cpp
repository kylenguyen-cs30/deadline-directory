#include "header.hpp"

string expandUserPath(const string &path)
{
    if (!path.empty() && path[0] == '~')
    {
        // get home directory from HOME environment variable
        char *home = getenv("HOME");
        if (home)
        {
            return string(home) + path.substr(1);
        }
        else
        {
            cout << "path : " << path << endl;
            return path;
        }
    }
    cout << "path : " << path << endl;
    return path;
}

std::chrono::system_clock::time_point stringToTimePoint(const string &dueDate)
{

    std::tm tm = {};
    std::stringstream ss(dueDate);
    ss >> std::get_time(&tm, "%Y-%m-%d %H-%M-%S");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return tp;
}

bool isDueMoreThan24hours(const string &dueDate)
{
    auto dueTimePoint = stringToTimePoint(dueDate);
    auto now = std::chrono::system_clock::now();
    auto hours = std::chrono::duration_cast<std::chrono::hours>(now - dueTimePoint).count();
    return hours > 24;
}

string getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

void displayMenu(vector<Task> &todayChallenges, vector<Task> &doneChallenges, vector<Task> &unfinishedTask)
{
    loadTasks(todayChallenges, doneChallenges, unfinishedTask);
    cout << "=================================================================================================================================================" << endl;
    cout << "JUST DO IT \n";
    cout << "=================================================================================================================================================" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    while (true)
    {
        moveOverdueTasks(todayChallenges, unfinishedTask);
        emptyAllDoneTask(doneChallenges);

        cout << "=================================================================================================================================================" << endl;
        cout << "Today Challenges \n";
        cout << endl;
        printList(todayChallenges);
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        cout << "DONES!!! \n";
        cout << endl;
        printList(doneChallenges);
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        cout << "UNFINISHED \n";
        cout << endl;
        printList(unfinishedTask);
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "=================================================================================================================================================" << endl;
        cout << "COMMANDS" << endl;
        commands();

        cout << endl;
        cout << endl;
        cout << endl;

        char choice;
        string input;
        bool validChoice = false;

        while (!validChoice)
        {
            cout << "Command : ";
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
                cin.clear();
                break;
            }
        }

        switch (choice)
        {
        case '1':
            // Add task
            addTasks(todayChallenges);
            cout << endl;
            cout << endl;
            break;
        case '2':
        {
            int num;
            cout << "Please choose directions\n";
            cout << "1. Today Challenge -> Done!! "
                 << "2. Unfinished -> Today Challenge" << endl;
            cin >> num;
            if (num == 1)
            {
                moveTask(doneChallenges, todayChallenges);
            }
            else
            {
                moveTask(todayChallenges, unfinishedTask);
            }
        }
        break;
        case '3':

            cout << "Quick save successfully" << endl;

            cout << endl;
            cout << endl;
            break;
        case '4':

            cout << "Delete Mode" << endl;
            cout << "1. Today Challenges "
                 << " 2. Unfinished Task" << endl;
            int choice;
            cin >> choice;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 1)
            {
                deleteTask(todayChallenges);
            }
            else
            {
                deleteTask(unfinishedTask);
            }

            cout << endl;
            cout << endl;
            break;

        case '5':
            cout << endl
                 << "You are editing on Today Challenges" << endl;

            editTask(todayChallenges);

            break;

        case '6':
            writeFile(todayChallenges, doneChallenges, unfinishedTask);
            moveOverdueTasks(todayChallenges, unfinishedTask);
            emptyAllDoneTask(doneChallenges);
            cout << "Update Successfully" << endl;

            cout << endl;
            cout << endl;
            break;
        case '7':
            writeFile(todayChallenges, doneChallenges, unfinishedTask);
            cout << endl;
            cout << endl;
            cout << "Have a good day!!!" << endl;
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
             << "3. Cancel (remove the last sub-task entered)" << endl;
        cout << "choice: ";
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
        else
        {
            cout << "Error please enter your choice again" << endl;
            cin.clear();
            cout << endl;
            cout << endl;
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
        cout << i + 1 << ". " << str[i].description << endl;
        if (!str[i].subTask.empty())
        {
            int n = str[i].subTask.size();
            for (int j = 0; j < n; j++)
            {
                cout << "\t" << i + 1 << "." << j + 1 << " " << str[i].subTask[j].description << endl;
            }
        }
    }
}

void moveOverdueTasks(vector<Task> &todayChallenges, vector<Task> &unfinishedTask)
{
    auto it = todayChallenges.begin();
    while (it != todayChallenges.end())
    {
        if (isDueMoreThan24hours(it->dueDate))
        {
            unfinishedTask.push_back(*it);
            it = todayChallenges.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void writeFile(const vector<Task> &a, const vector<Task> &b, const vector<Task> &c)
{
    string filePath = expandUserPath("~/Developer/cpp/deadline-director/doit-list/list.txt");
    std::ofstream outFile(filePath);
    if (!outFile)
    {
        cout << "Error: Unable to open file" << endl;
        return;
    }

    auto writeTasks = [&outFile](const vector<Task> &tasks, const string &listName)
    {
        outFile << listName << endl;
        for (const auto &task : tasks)
        {
            outFile << task.description << "\n"
                    << task.dueDate << "\n";
            if (!task.subTask.empty())
            {
                for (const auto &subtask : task.subTask)
                {
                    outFile << "\t" << subtask.description << "\n"
                            << "\t" << subtask.dueDate << "\n";
                }
            }
            outFile << "----\n";
        }
    };

    writeTasks(a, "Today Challenges");
    outFile << "===========\n";
    writeTasks(b, "Done Challenges");
    outFile << "===========\n";
    writeTasks(c, "Unfinished Challenges");
    outFile << "===========\n";

    outFile.close();
}

void loadTasks(vector<Task> &a, vector<Task> &b, vector<Task> &c)
{
    string filePath = expandUserPath("~/Developer/cpp/deadline-director/doit-list/list.txt");
    std::ifstream inFile(filePath);
    if (!inFile)
    {
        cout << "Error : Unable to open file" << endl;
        return;
    }

    string line;
    vector<Task> *currentList = nullptr;
    while (getline(inFile, line))
    {
        if (line == "Today Challenges")
        {
            currentList = &a;
        }
        else if (line == "Done Challenges")
        {
            currentList = &b;
        }
        else if (line == "Unfinished Challenges")
        {
            currentList = &c;
        }
        else if (line == "----" || line == "===========")
        {
            continue;
        }
        else if (currentList != nullptr)
        {
            // parse line
            string description = line;
            if (!getline(inFile, line))
                break;

            string dueDate = line;
            vector<Task> subTasks;
            while (inFile.peek() == '\t')
            {
                string subTaskDescription, subTaskDueDate;

                getline(inFile, line);
                subTaskDescription = line.substr(1);

                if (!getline(inFile, line))
                    break;
                subTaskDueDate = line.substr(1);
                subTasks.push_back(Task(subTaskDescription, subTaskDueDate));
            }
            currentList->push_back(Task(description, dueDate, subTasks));

            if (inFile.peek() == '-')
            {
                getline(inFile, line);
            }
        }
    }
}

void deleteTask(vector<Task> &a)
{
    cout << "Enter number: ";
    int i;
    cin >> i;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    a.erase(a.begin() + (i - 1));
}

void emptyAllDoneTask(vector<Task> &doneChallenge)
{
    auto it = doneChallenge.begin();
    while (it != doneChallenge.end())
    {
        if (isDueMoreThan24hours(it->dueDate))
        {
            it = doneChallenge.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void editTask(vector<Task> &task)
{
    // return if vector is empty
    if (task.size() == 0)
    {
        return;
    }

    cout << endl
         << "Enter the task number that you want to edit " << endl;
    cout << "Number: ";
    string num;
    cin >> num;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int taskNum = 0;
    int subTask = 0;

    if (num.size() == 1)
    {
        int taskNum = stoi(num);
    }
    else
    {
        const char *ch = num.c_str();
        int taskNum = ch[0];
        int subTasknum = ch[2];
    }

    // just change the current task
    if (subTask == 0)
    {
        int ans = 0;
        if (!task[taskNum].subTask.empty())
        {
            cout << endl
                 << "Attach the current sub task to the new task" << endl;
            cout << "1. Yes 2. No";
            cin >> ans;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (ans == 1)
        {
            // working on the logic
        }
        else
        {
            task.erase(task.end() + (taskNum - 1));
            addTasks(task);
        }
    }
    else
    {
        // change the subtask
    }
}

void moveTask(vector<Task> &a, vector<Task> &b)
{
    cout << endl;
    cout << "Move Mode\n";

    cout << "Please enter the number of task (e.g. 1,2,3): ";
    string taskNumList;
    cin >> taskNumList;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    vector<Task> temp;
    copyTask(b, temp);
    string token;

    for (char c : taskNumList)
    {
        if (c == ',')
        {
            continue;
        }
        else
        {
            int taskNum = c - '0';
            if (taskNum > b.size())
            {
                cout << "invalid input. Please try again !!. index size is bigger. Index : " << taskNum << endl;
            }
            else
            {
                temp[taskNum - 1].dueDate = getCurrentTime();
                a.push_back(temp[taskNum - 1]);
                b.erase(b.begin() + (taskNum - 1));
            }
        }
    }

    cout << "Operation Successfull !!" << endl;
    cout << endl
         << endl;
}

void copyTask(vector<Task> &source, vector<Task> &destination)
{
    for (const Task &sourceTask : source)
    {
        Task newTask = Task(sourceTask.description, sourceTask.dueDate);
        for (const Task &subTask : sourceTask.subTask)
        {
            Task newSubTask = Task(subTask.description, subTask.dueDate);
            newTask.subTask.push_back(newSubTask);
        }
        destination.push_back(newTask);
    }
}

#include "tasks.cpp"

Task createTask(const string &description, const string &dueDate)
{
  return Task(description, dueDate);
}

string timePointToString(const std::chrono::system_clock::time_point &tp)
{
  auto in_time_t = std::chrono::system_clock::to_time_t(tp);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H-%M-%S");
  return ss.str();
}

void populaceTasks(vector<Task> &tasks)
{
  auto now = std::chrono::system_clock::now();
  auto past25th = now - std::chrono::hours(25);
  auto past24th = now - std::chrono::hours(24);
  auto past23th = now - std::chrono::hours(23);
  auto future = now + std::chrono::hours(24);

  tasks.push_back(createTask("Task 25 hours passed", timePointToString(past25th) ));
  tasks.push_back(createTask("Task 24 hours passed", timePointToString(past24th)));
  tasks.push_back(createTask("Task 23 hours passed", timePointToString(past23th)));
  tasks.push_back(createTask("Future Task", timePointToString(future)));
}

int main(int argc, char *argv[])
{
  vector<Task> todayChallenges;
  vector<Task> unfinishedTask;

  populaceTasks(todayChallenges);

  moveOverdueTasks(todayChallenges, unfinishedTask);

  cout << "Today challenges after moving move overdue task:" << endl;
  printList(todayChallenges);

  cout << "\n unfinishedTask:" << endl;
  printList(unfinishedTask);
  return 0;
}

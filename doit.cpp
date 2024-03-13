#include "header.hpp"
#include "tasks.cpp"
int main(int argc, char const *argv[])
{
    vector<Task> todayChallenges;
    vector<Task> doneChallenges;
    vector<Task> unfinishedTask;
    displayMenu(todayChallenges, doneChallenges, unfinishedTask);
    return 0;
}

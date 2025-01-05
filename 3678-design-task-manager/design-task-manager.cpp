#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

class TaskManager {
private:
    // Store tasks in a set with (priority, taskId). Sorting by priority and taskId automatically.
    set<pair<int, int>> tasks;
    // Map taskId to (userId, priority).
    unordered_map<int, pair<int, int>> taskMap;

public:
    // Initialize the TaskManager with a list of tasks.
    TaskManager(vector<vector<int>>& initialTasks) {
        for (const auto& task : initialTasks) {
            int userId = task[0], taskId = task[1], priority = task[2];
            tasks.insert({priority, taskId});
            taskMap[taskId] = {userId, priority};
        }
    }

    // Add a new task for a specific user.
    void add(int userId, int taskId, int priority) {
        tasks.insert({priority, taskId});
        taskMap[taskId] = {userId, priority};
    }

    // Edit the priority of an existing task.
    void edit(int taskId, int newPriority) {
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            int oldPriority = it->second.second;
            tasks.erase({oldPriority, taskId});  // Remove the old entry from the set.
            tasks.insert({newPriority, taskId});  // Add the updated entry.
            it->second.second = newPriority;  // Update the priority in the map.
        }
    }

    // Remove a task by taskId.
    void rmv(int taskId) {
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            int priority = it->second.second;
            tasks.erase({priority, taskId});  // Remove the task from the set.
            taskMap.erase(it);  // Remove the task from the map.
        }
    }

    // Execute the task with the highest priority.
    int execTop() {
        if (tasks.empty()) return -1;  // No tasks available.
        auto topTask = *tasks.rbegin();  // Get the task with the highest priority.
        int priority = topTask.first, taskId = topTask.second;
        int userId = taskMap[taskId].first;  // Retrieve the userId.
        tasks.erase(topTask);  // Remove the task from the set.
        taskMap.erase(taskId);  // Remove the task from the map.
        return userId;
    }
};

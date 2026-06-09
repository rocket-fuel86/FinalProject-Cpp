#ifndef FINAL_TASK_DATA_H
#define FINAL_TASK_DATA_H

enum Priority {
    LOW,
    MEDIUM,
    HIGH,
};

struct Date {
    int year;
    int month;
    int day;
};

constexpr int MAX_STR = 100;

struct Task {
    int id;
    char title[MAX_STR];
    Priority priority;
    char description[MAX_STR];
    Date due_date;
};

Task createTask(
    int id,
    const char* title,
    Priority priority,
    const char* description,
    Date due_date
);

void addTaskToArray(
    Task task,
    Task*& task_array,
    int& size
);

void deleteTaskFromArrayById(
    int taskId,
    Task*& task_array,
    int& size
);

void editTaskInArrayById(
    int taskId,
    const Task& newTask,
    Task* task_array,
    int& size
);

bool contains(
    const char* text,
    const char* pattern
);

void filterByTitle(
    const char* pattern,
    Task* task_array,
    int size
);

void filterByPriority(
    Priority priority,
    Task* task_array,
    int size
);

void filterByDescription(
    const char* keyword,
    Task* task_array,
    int size
);

bool isAfter(
    const Date& a,
    const Date& b
);

bool isBefore(
    const Date& a,
    const Date& b
);

void filterByDateRange(
    Date from,
    Date to,
    Task* task_array,
    int size
);

void sortByPriority(
    Task* task_array,
    int size
);

void sortByDate(
    Task* task_array,
    int size
);

void saveTasksBin(
    const char* filename,
    Task* arr,
    int size
);

void loadTasksBin(
    const char* filename,
    Task*& arr,
    int& size
);

#endif //FINAL_TASK_DATA_H

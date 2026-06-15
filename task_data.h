#ifndef FINAL_TASK_DATA_H
#define FINAL_TASK_DATA_H

#include <iostream>

enum Priority {
    LOW,
    MEDIUM,
    HIGH,
};

struct Date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

constexpr int MAX_STR = 100;

struct Task {
    size_t id;
    char title[MAX_STR];
    Priority priority;
    char description[MAX_STR];
    Date due_date;
};

void printTask(const Task& t);

void printAll(Task* tasks, size_t size);

Task createTask(
    size_t id,
    const char* title,
    Priority priority,
    const char* description,
    Date due_date
);

void addTaskToArray(
    Task task,
    Task*& task_array,
    size_t& size
);

void deleteTaskFromArrayById(
    size_t taskId,
    Task*& task_array,
    size_t& size
);

void editTaskInArrayById(
    size_t taskId,
    const Task& newTask,
    Task* task_array,
    size_t& size
);

bool contains(
    const char* text,
    const char* pattern
);

void searchByTitle(
    const char* pattern,
    Task* task_array,
    size_t size
);

void searchByPriority(
    Priority priority,
    Task* task_array,
    size_t size
);

void searchByDescription(
    const char* keyword,
    Task* task_array,
    size_t size
);

bool isAfter(
    const Date& a,
    const Date& b
);

bool isBefore(
    const Date& a,
    const Date& b
);

void searchByDateRange(
    Date from,
    Date to,
    Task* task_array,
    size_t size
);

void sortByPriority(
    Task* task_array,
    size_t size
);

void sortByDate(
    Task* task_array,
    size_t size
);

void saveTasksBin(
    const char* filename,
    Task* arr,
    size_t size
);

void loadTasksBin(
    const char* filename,
    Task*& arr,
    size_t& size
);

#endif //FINAL_TASK_DATA_H

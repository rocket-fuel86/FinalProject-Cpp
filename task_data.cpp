#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include "task_data.h"

Task createTask(int id,
                const char* title,
                Priority priority,
                const char* description,
                Date due_date) {

    Task t;

    t.id = id;
    t.priority = priority;
    t.due_date = due_date;

    std::strcpy(t.title, title);
    std::strcpy(t.description, description);

    return t;
}

void addTaskToArray(Task task, Task*& task_array, int& size) {
    Task* newArray = new Task[size + 1];

    for (int i = 0; i < size; i++) {
        newArray[i] = task_array[i];
    }

    newArray[size] = task;

    delete[] task_array;

    task_array = newArray;
    size++;
}

void deleteTaskFromArrayById(int taskId, Task*& task_array, int& size) {
    if (size == 0) return;

    if (size == 1) {
        delete[] task_array;
        task_array = nullptr;
        size = 0;
        return;
    }

    Task* newArray = new Task[size - 1];

    int j = 0;
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (task_array[i].id == taskId && !found) {
            found = true;
            continue;
        }

        if (j < size - 1) {
            newArray[j++] = task_array[i];
        }
    }

    if (found) {
        delete[] task_array;
        task_array = newArray;
        size--;
    } else {
        delete[] newArray;
    }
}

void editTaskInArrayById(int taskId, const Task& newTask, Task* task_array, int& size) {
    for (int i = 0; i < size; i++) {
        if (task_array[i].id == taskId) {

            Task temp = newTask;
            temp.id = taskId;

            task_array[i] = temp;
            return;
        }
    }
}

bool contains(const char* text, const char* pattern) {
    return strstr(text, pattern) != nullptr;
}

void filterByTitle(const char* pattern, Task* task_array, int size) {
    for (int i = 0; i < size; i++) {
        if (contains(task_array[i].title, pattern)) {
            std::cout << task_array[i].id << " " << task_array[i].title << "\n";
        }
    }
}

void filterByPriority(Priority priority, Task* task_array, int size) {
    for (int i = 0; i < size; i++) {
        if (task_array[i].priority == priority) {
            std::cout << task_array[i].id << " " << task_array[i].title << "\n";
        }
    }
}

void filterByDescription(const char* keyword, Task* task_array, int size) {
    for (int i = 0; i < size; i++) {
        if (contains(task_array[i].description, keyword)) {
            std::cout << task_array[i].id << " " << task_array[i].title << "\n";
        }
    }
}

bool isAfter(const Date& a, const Date& b) {
    if (a.year != b.year) return a.year > b.year;
    if (a.month != b.month) return a.month > b.month;
    return a.day > b.day;
}

bool isBefore(const Date& a, const Date& b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

void filterByDateRange(Date from, Date to, Task* task_array, int size) {
    for (int i = 0; i < size; i++) {
        if (!isBefore(task_array[i].due_date, from) &&
            !isAfter(task_array[i].due_date, to)) {
                std::cout << task_array[i].id << " " << task_array[i].title << "\n";
            }
    }
}

void sortByPriority(Task* task_array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (task_array[j].priority > task_array[j + 1].priority) {
                std::swap(task_array[j], task_array[j + 1]);
            }
        }
    }
}

void sortByDate(Task* task_array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (isAfter(task_array[j].due_date, task_array[j + 1].due_date)) {
                std::swap(task_array[j], task_array[j + 1]);
            }
        }
    }
}

void saveTasksBin(const char* filename, Task* arr, int size) {
    FILE* file = fopen(filename, "wb");
    if (!file) return;

    fwrite(&size, sizeof(int), 1, file);
    fwrite(arr, sizeof(Task), size, file);

    fclose(file);
}


void loadTasksBin(const char* filename, Task*& arr, int& size) {
    FILE* file = fopen(filename, "rb");
    if (!file) return;

    if (fread(&size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return;
    }

    delete[] arr;
    arr = new Task[size];

    fread(arr, sizeof(Task), size, file);

    fclose(file);
}
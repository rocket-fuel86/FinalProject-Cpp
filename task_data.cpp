#include <cstring>
#include <cstdio>
#include <algorithm>
#include "task_data.h"

void printTask(const Task& t) {
    const char* pr = (t.priority == HIGH) ? "High" : (t.priority == MEDIUM) ? "Medium" : "Low";
    std::cout << "[" << t.id << "] " << t.title
        << " | " << pr
        << " | " << t.due_date.day << "." << t.due_date.month << "." << t.due_date.year
        << " | " << t.description << "\n";
}

void printAll(Task* tasks, size_t size) {
    if (size == 0) {
        std::cout << "No tasks.\n";
        return;
    }
    for (size_t i = 0; i < size; i++)
        printTask(tasks[i]);
}

bool contains(const char* text, const char* pattern) {
    return strstr(text, pattern) != nullptr;
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

Task createTask(size_t id,
                const char* title,
                Priority priority,
                const char* description,
                Date due_date) {

    Task t{};

    t.id = id;
    t.priority = priority;
    t.due_date = due_date;

    std::strcpy(t.title, title);
    std::strcpy(t.description, description);

    return t;
}

void addTaskToArray(Task task, Task*& task_array, size_t& size) {
    Task* newArray = new Task[size + 1];

    for (size_t i = 0; i < size; i++) {
        newArray[i] = task_array[i];
    }

    newArray[size] = task;

    delete[] task_array;

    task_array = newArray;
    size++;
}

void deleteTaskFromArrayById(size_t taskId, Task*& task_array, size_t& size) {
    if (size == 0) return;

    if (size == 1) {
        delete[] task_array;
        task_array = nullptr;
        size = 0;
        return;
    }

    Task* newArray = new Task[size - 1];

    size_t j = 0;
    bool found = false;

    for (size_t i = 0; i < size; i++) {
        if (task_array[i].id == taskId && !found) {
            found = true;
            continue;
        }

        newArray[j++] = task_array[i];
    }

    if (found) {
        delete[] task_array;
        task_array = newArray;
        size--;
    } else {
        delete[] newArray;
    }
}

void editTaskInArrayById(size_t taskId, const Task& newTask, Task* task_array, size_t& size) {
    for (size_t i = 0; i < size; i++) {
        if (task_array[i].id == taskId) {

            Task temp = newTask;
            temp.id = taskId;

            task_array[i] = temp;
            return;
        }
    }
}

void searchByTitle(const char* pattern, Task* task_array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (contains(task_array[i].title, pattern)) {
            printTask(task_array[i]);
        }
    }
}

void searchByPriority(Priority priority, Task* task_array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (task_array[i].priority == priority) {
            printTask(task_array[i]);
        }
    }
}

void searchByDescription(const char* keyword, Task* task_array, size_t size) {
    for (int i = 0; i < size; i++) {
        if (contains(task_array[i].description, keyword)) {
            printTask(task_array[i]);
        }
    }
}

void searchByDateRange(Date from, Date to, Task* task_array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (!isBefore(task_array[i].due_date, from) && !isAfter(task_array[i].due_date, to)) {
            printTask(task_array[i]);
        }
    }
}

void sortByPriority(Task* task_array, size_t size) {
    if (size == 0) return;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (task_array[j].priority < task_array[j + 1].priority) {
                std::swap(task_array[j], task_array[j + 1]);
            }
        }
    }
}

void sortByDate(Task* task_array, size_t size) {
    if (size == 0) return;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (isAfter(task_array[j].due_date, task_array[j + 1].due_date)) {
                std::swap(task_array[j], task_array[j + 1]);
            }
        }
    }
}

void saveTasksBin(const char* filename, Task* arr, size_t size) {
    FILE* file = fopen(filename, "wb");
    if (!file) return;

    fwrite(&size, sizeof(size_t), 1, file);
    fwrite(arr, sizeof(Task), size, file);

    fclose(file);
}


void loadTasksBin(const char* filename, Task*& arr, size_t& size) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        size = 0;
        arr = nullptr;
        return;
    }

    size_t expected_size = 0;
    if (fread(&expected_size, sizeof(size_t), 1, file) != 1 || expected_size <= 0) {
        fclose(file);
        size = 0;
        arr = nullptr;
        return;
    }

    delete[] arr;
    arr = new Task[expected_size];

    size_t read_elements = fread(arr, sizeof(Task), expected_size, file);


    if (read_elements != expected_size) {
        size = read_elements;
        if (size == 0) {
            delete[] arr;
            arr = nullptr;
        }
        else {
            Task* shrinked = new Task[size];
            for (size_t i = 0; i < size; i++) shrinked[i] = arr[i];
            delete[] arr;
            arr = shrinked;
        }
    }
    else {
        size = expected_size;
    }

    fclose(file);
}
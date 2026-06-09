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

struct Task {
    int id;
    const char* title;
    Priority priority;
    const char* description;
    Date due_date;
};

#endif //FINAL_TASK_DATA_H

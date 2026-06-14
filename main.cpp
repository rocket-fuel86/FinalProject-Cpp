#include <iostream>
#include "task_data.h"
#include "ui_functions.h"

int main() {
    Task* tasks = nullptr;
    int size = 0;
    int nextId = 1;

    loadTasksBin("tasks.dat", tasks, size);
    if (size > 0) nextId = tasks[size - 1].id + 1;

    int choice;
    do {
        showMenu();
        std::cin >> choice;

        if (choice == 1) {
            Task t = inputTask(nextId++);
            addTaskToArray(t, tasks, size);
            saveTasksBin("tasks.dat", tasks, size);

        }
        else if (choice == 2) {
            printAll(tasks, size);
            std::cout << "ID for editing: ";
            int id; std::cin >> id;
            Task t = inputTask(id);
            editTaskInArrayById(id, t, tasks, size);
            saveTasksBin("tasks.dat", tasks, size);

        }
        else if (choice == 3) {
            printAll(tasks, size);
            std::cout << "ID for deleting: ";
            int id; std::cin >> id;
            deleteTaskFromArrayById(id, tasks, size);
            saveTasksBin("tasks.dat", tasks, size);

        }
        else if (choice == 4) {
            printAll(tasks, size);

        }
        else if (choice == 5) {
            Task* copy = new Task[size];
            for (int i = 0; i < size; i++) copy[i] = tasks[i];
            sortByPriority(copy, size);
            printAll(copy, size);
            delete[] copy;

        }
        else if (choice == 6) {
            Task* copy = new Task[size];
            for (int i = 0; i < size; i++) copy[i] = tasks[i];
            sortByDate(copy, size);
            printAll(copy, size);
            delete[] copy;
        }

    } while (choice != 0);

    delete[] tasks;
    return 0;
}
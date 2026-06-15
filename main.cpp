#include "ui_functions.h"

int main() {
    Task* tasks = nullptr;
    size_t size = 0;
    size_t nextId = 1;

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
            std::cout << "\nID for editing: ";
            int id; std::cin >> id;
            Task t = inputTask(id);
            editTaskInArrayById(id, t, tasks, size);
            saveTasksBin("tasks.dat", tasks, size);
        }
        else if (choice == 3) {
            printAll(tasks, size);
            std::cout << "\nID for deleting: ";
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
        else if (choice == 7) {
            std::cin.ignore();
            std::cout << "Title: ";
            char title[MAX_STR]; std::cin.getline(title, MAX_STR);
            searchByTitle(title, tasks, size);
        }
        else if (choice == 8) {
            int pr;
            std::cout << "Priority (1-High, 2-Medium, 3-Low): ";
            while (!(std::cin >> pr) || pr < 1 || pr > 3) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Invalid choice. Please enter 1, 2, or 3: ";
            }
            Priority p = (pr == 1) ? HIGH : (pr == 2) ? MEDIUM : LOW;
            searchByPriority(p, tasks, size);
        }
        else if (choice == 9) {
            std::cin.ignore();
            std::cout << "Keyword: ";
            char keyword[MAX_STR]; std::cin.getline(keyword, MAX_STR);
            searchByDescription(keyword, tasks, size);
        }
        else if (choice == 10) {
            std::cout << "Enter date range: " << std::endl;
            std::cout << "From: ";
            Date from = inputDate();
            std::cout << "To: ";
            Date to = inputDate();
            searchByDateRange(from, to, tasks, size);
        }
    } while (choice != 0);

    delete[] tasks;
    return 0;
}
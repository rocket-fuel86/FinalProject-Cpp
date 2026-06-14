#include "ui_functions.h"
#include <iostream>
#include <cstring>
#include <limits>

void showMenu() {
    std::cout << "\n=== TODO LIST ===\n";
    std::cout << "1. Add task\n";
    std::cout << "2. Edit task\n";
    std::cout << "3. Delete task\n";
    std::cout << "4. Show all tasks\n";
    std::cout << "5. Show by priority\n";
    std::cout << "6. Show by date\n";
    std::cout << "0. Exit\n";
    std::cout << "Select: ";
}

void printTask(const Task& t) {
    const char* pr = (t.priority == HIGH) ? "High" : (t.priority == MEDIUM) ? "Medium" : "Low";
    std::cout << "[" << t.id << "] " << t.title
        << " | " << pr
        << " | " << t.due_date.day << "." << t.due_date.month << "." << t.due_date.year
        << " | " << t.description << "\n";
}

void printAll(Task* tasks, int size) {
    if (size == 0) {
        std::cout << "No tasks.\n";
        return;
    }
    for (int i = 0; i < size; i++)
        printTask(tasks[i]);
}

Date inputDate() {
    Date d;

    std::cout << "Day: ";
    while (!(std::cin >> d.day) || d.day < 1 || d.day > 31) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Invalid input. Enter Day (1-31): ";
    }

    std::cout << "Month: ";
    while (!(std::cin >> d.month) || d.month < 1 || d.month > 12) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter Month (1-12): ";
    }

    std::cout << "Year: ";
    while (!(std::cin >> d.year) || d.year < 1900 || d.year > 2100) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a valid Year (e.g., 2026): ";
    }


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return d;
}

Task inputTask(int id) {
    char title[MAX_STR], desc[MAX_STR];
    int pr;


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Name: ";
    std::cin.getline(title, MAX_STR);

    std::cout << "Description: ";
    std::cin.getline(desc, MAX_STR);

    std::cout << "Priority (1-High, 2-Medium, 3-Low): ";
    while (!(std::cin >> pr) || pr < 1 || pr > 3) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Invalid choice. Please enter 1, 2, or 3: ";
    }

    Priority p = (pr == 1) ? HIGH : (pr == 2) ? MEDIUM : LOW;

    std::cout << "Date:\n";
    Date d = inputDate();

    return createTask(id, title, p, desc, d);
}
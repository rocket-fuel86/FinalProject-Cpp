#ifndef FINAL_UI_FUNCTIONS_H
#define FINAL_UI_FUNCTIONS_H

#include "task_data.h"

void showMenu();
void printTask(const Task& t);
void printAll(Task* tasks, int size);
Task inputTask(int id);
Date inputDate();

#endif
#ifndef TASK_H
#define TASK_H
#define MAX_LEN 101

#include <stdbool.h>

// Define the Task structure
typedef struct Task {
    int id;
    char desc[MAX_LEN];
    bool status;
} Task;

#endif

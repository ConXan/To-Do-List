#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/task.h"
#include "../include/fun1.h"
#include "../include/fun2.h"

void mainMenu(void);

int main() {
    int choice, test;
    char ch;

    printf("Welcome to Task Manager / To-do list!\n\n");
    while (1) {
        mainMenu();
        scanf("%d", &choice);
        test = getchar();
        printf("\n");
        while (choice < 1 || choice > 6) {
            printf("Invalid input, please try again or exit.\n");
            scanf("%d", &choice);
            test = getchar();
            printf("\n");
        } 
        if (choice == 6) { //Exit
            return 0;
        } else {
            switch (choice) {
                case 1: //Add
                    Task * newTask = (Task *)malloc(sizeof(Task));
                    if (newTask == NULL) {
                        fprintf(stderr,"Error with malloc\n");
                        return 1;
                    }
                    test = addTask(newTask);
                    if (test) {
                        fprintf(stderr,"Error, task wasn't added\n");
                        return 1;
                    } else {
                        printf("\n");
                        printf("Task added successfully!\n");
                    }
                    free(newTask);
                    break;
                case 2: //Deletion
                    int num;
                    test = printList();
                    if (test) {
                        fprintf(stderr,"Error, task list couldn't be loaded\n");
                        return 1;
                    }

                    printf("\nPlease enter the number of the task you want to delete from the list\n"); 
                    scanf("%d", &num);
                    test = getchar();
                    test = removeTask(num);
                    if (test == 1) {
                        fprintf(stderr,"Error, task wasn't removed\n");
                        return 1;
                    } else if (test == 2) {
                        break;
                    } else {
                        printf("\n");
                        printf("Task removed successfully!\n");
                    }
                    break;
                case 3: //Update
                    Task * task = (Task *)malloc(sizeof(Task));
                    if (task == NULL) {
                        fprintf(stderr,"Error with malloc\n");
                        return 1;
                    }
                    int numm;
                    test = printList();
                    if (test) {
                        fprintf(stderr,"Error, task list couldn't be loaded\n");
                        return 1;
                    }

                    printf("\nPlease enter the number of the task you want to update\n"); 
                    scanf("%d", &numm);
                    test = getchar();
                    test = updateTask(numm, task);
                    if (test == 2) {
                        fprintf(stderr,"Error, task's status updated successfully, but task wasn't removed\n");
                        return 1;
                    }

                    free(task);
                    break;
                case 4:
                    test = printList();
                    if (test) {
                        fprintf(stderr,"Error, task list couldn't be loaded\n");
                        return 1;
                    }
                    break;
                case 5:
                    test = takeback();
                    if (test == -2) {
                        fprintf(stderr,"Error, can't take back last action\n");
                        return 1;
                    } else if (test == -1) {
                        printf("Last action was a takeback, you can't undo again\n");
                        break;
                    } else if (test == 0) {
                        printf("Success, list's last state was restored\n");
                        break;
                    }
            }
        }
        printf("You want to exit or continue? Y/n\n");
        scanf("%c", &ch);
        test = getchar();
        while (ch != 'n' && ch != 'N' && ch != 'Y' && ch != 'y') {
            printf("\n");
            printf("Invalid input, please select either 'y' for yes or 'n' for no\n");
            scanf("%c", &ch);
            test = getchar();
        }
        if (ch == 'N' || ch == 'n') {
            return 0;
        }
        printf("\n");
    }
}

void mainMenu() {
    printf("Choose an operation:\n");
    printf("1. Add new task\n");
    printf("2. Remove a task\n");
    printf("3. Update a task (status/description)\n");
    printf("4. Print all the tasks\n");
    printf("5. Undo last action\n");
    printf("6. Exit\n");   
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/task.h"
#include "../include/fun2.h"

#define MAX_TOTAL 130 //rank (ex 3.) + description (max length 100) + DONE (optional)

char buffer[MAX_TOTAL];
char str[MAX_LEN];

int endsDone(char *);

//Function to print the task list
int printList(void) {
    FILE * fp = fopen("data/main.txt","r");
    if (fp == NULL) {
        return 1;
    }

    FILE * back = fopen("data/back.txt","r+");
    if (back == NULL) {
        fprintf(stderr,"Error, try again\n");
        fclose(fp);
        return 1;
    }  

    if (fgets(buffer,sizeof(buffer),fp) == NULL) {
        printf("List is currently empty, please add a task first\n\n");
        fclose(fp);
        fclose(back);
        return 0;
    }
    rewind(fp);
    printf("To-do list:\n");
    while (fgets(buffer,sizeof(buffer),fp) != NULL) {
        printf("%s",buffer);
    }
    printf("\n");

    //Last task is 'Print list'
    fprintf(back,"%d",3);

    fclose(fp);
    fclose(back);
    return 0;
}

//Function to update the task
int updateTask(int num, Task * task) {
    int c, cnt;
    FILE * temp = fopen("data/count.txt","r");
    if (temp == NULL) {
        fprintf(stderr,"Error, try again\n");
        return 1;
    }
    FILE * fp = fopen("data/main.txt","r");
    if (fp == NULL) {
        fprintf(stderr,"Error opening file\n");
        fclose(temp);
        return 1;
    }

    FILE * tmp = fopen("data/temp.txt","w");
    if (fp == NULL) {
        fprintf(stderr,"Error opening file\n");
        fclose(temp);
        fclose(fp);
        return 1;
    }

    FILE * back = fopen("data/back.txt","r+");
    if (back == NULL) {
        fprintf(stderr,"Error, try again\n");
        return 1;
    }

    fscanf(temp,"%d",&cnt);
    rewind(temp);
    
    if (cnt == 0) {
        printf("List is currently empty, please add a task first\n");
        fclose(tmp);
        fclose(temp);
        fclose(fp);
        return 2;
    }
    
    while (num < 1 || num > cnt) {
        printf("\n");
        fprintf(stderr, "Invalid input, please choose a number in [1,%d]\n", cnt);
        scanf("%d", &num);
        c = getchar();
    }

    int lines;
    char cpy[MAX_TOTAL]; //Variable to store the specific description
    lines = 1;
    task->status = true;
    while (lines < num) {
        fgets(buffer,sizeof(buffer),fp);
        lines ++;
    }
    fgets(buffer,sizeof(buffer),fp);
    snprintf(cpy,MAX_TOTAL,"%s",buffer); //String copying always with snprintf()
    rewind(fp);

    if (endsDone(buffer)) { //Checks whether the selected task is already marked DONE
        printf("\n");
        printf("This task is already finished, you can't update its description nor its status\n");
        fclose(tmp);
        fclose(temp);
        fclose(fp);
        return 3;
    }

    printf("\n");
    printf("Which part of the task you want to update? Please enter the corresponding number\n");
    printf("1. Status (mark done)\n");
    printf("2. Description\n");

    int id, choice;
    scanf("%d", &choice);
    c = getchar();
    while (choice != 1 && choice != 2) {
        printf("\n");
        printf("Invalid input, please choose either 1 or 2\n");
        scanf("%d", &choice);
        c = getchar();
    }

    if (choice == 1) {
        printf("\n");
        printf("Do you also want to remove this task? Y/n\n");
        char ch;
        scanf("%c", &ch);
        c = getchar();
        while (ch != 'n' && ch != 'N' && ch != 'Y' && ch != 'y') {
            printf("\n");
            printf("Invalid input, please select either 'y' for yes or 'n' for no\n");
            scanf("%c", &ch);
            c = getchar();
        }
        printf("\n");
        if (ch == 'y' || ch == 'Y') {
            int test = removeTask(num);
            if (test == 1) {
                fprintf(stderr,"Error, task wasn't removed\n");
                fclose(tmp);
                fclose(temp);
                fclose(fp);
                return 2;
            }
            printf("Task's status was updated successfully\n");
            printf("Task was removed successfully\n\n");
        } else if (ch == 'n' || ch == 'N') {
            lines = 1;
            while (lines < num) { //Write up to the previous task of the selected one
                fgets(buffer,sizeof(buffer),fp);
                fputs(buffer,tmp);
                lines ++;
            }
            fgets(buffer,sizeof(buffer),fp);
            sscanf(cpy,"%d. %[^\n]100s", &id, str); //Extract the id number and dexcription of the task
            snprintf(buffer,sizeof(buffer), "%d. %s \x1b[31mDONE\x1b[0m\n", id, str); //Adds DONE with red color to the end of the description
            fputs(buffer,tmp);

            //Print the rest of the list if there is any
            while (fgets(buffer,sizeof(buffer),fp) != NULL) { 
                fputs(buffer,tmp);
            }

            //Method for having access to the previous state of the list
            rename("data/main.txt","data/prev.txt");
            rename("data/temp.txt","data/main.txt");
            printf("Task's status was updated successfully\n");
            fflush(stdout);
        }
    } else if (choice == 2) {
        printf("\nProvide task description (100 characters max!)\n");
        fflush(stdout);

        if (fgets(task->desc,sizeof(task->desc),stdin) == NULL) {
            fprintf(stderr,"Failed to read string\n");
            return 1;
        }

        lines = 1;
        while (lines < num) {
            fgets(buffer,sizeof(buffer),fp);
            fputs(buffer,tmp);
            lines ++;
        }
        snprintf(buffer,sizeof(buffer),"%d. %s",num,task->desc);
        fputs(buffer,tmp);
        fgets(buffer,sizeof(buffer),fp);
        while (fgets(buffer,sizeof(buffer),fp) != NULL) {
            fputs(buffer,tmp);
        }

        printf("\nTask's description was updated successfully\n");

        rename("data/main.txt","data/prev.txt");
        rename("data/temp.txt","data/main.txt");
    }

    //Last task is an update
    fprintf(back,"%d",4);

    fclose(back);
    fclose(tmp);
    fclose(temp);
    fclose(fp);
    return 0;
}

int endsDone(char * str) {
    int len = strlen(str);
    if (len < 4) {
        return 0;
    }
    if (str[len-2] == 'm' && str[len-3] == '0') { //Checks if the last 2 characters of the string are m0, meaning the task is DONE (see line 163)
        return 1;
    }

    return 0;
}

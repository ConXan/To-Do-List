#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/task.h"
#include "../include/fun1.h"

#define MAX_TOTAL 130

int addTask(Task * task) {
    char buffer[MAX_TOTAL];
    char str[MAX_LEN];
    
    printf("Provide task description (100 characters max!)\n");
    fflush(stdout);
   
    FILE * fp = fopen("main.txt","a+");
    if (fp == NULL) {
        fprintf(stderr,"Error opening main file\n");
        return 1;
    }
    
    FILE * tmp = fopen("prev.txt","w+");
    if (tmp == NULL) {
        fprintf(stderr,"Error opening secondary file\n");
        fclose(fp);
        return 1;
    }
    
    FILE * temp = fopen("count.txt","r+");
    if (temp == NULL) {
        fprintf(stderr,"Error, try again\n");
        fclose(fp);
        fclose(tmp);
        return 1;
    }

    FILE * back = fopen("data/back.txt","r+");
    if (back == NULL) {
        fprintf(stderr,"Error, try again\n");
        fclose(fp);
        fclose(tmp);
        fclose(temp);
        return 1;
    }

    int count;
    
    if (fgets(task->desc,sizeof(task->desc),stdin) == NULL) {
        fprintf(stderr,"Failed to read string\n");
        fclose(fp);
        fclose(tmp);
        fclose(temp);
        return 1;
    }

    
    fscanf(temp,"%d",&count);
    rewind(temp);

    //for prev
    while (fgets(buffer,sizeof(buffer),fp) != NULL) {
        fputs(buffer,tmp);
    }

    task->id = ++count;
    task->status = false; // Task not finished
    snprintf(buffer,sizeof(buffer),"%d. %s",task->id,task->desc);
    int len = strlen(buffer);
    if (buffer[len-1] != '\n') {
        buffer[len-1] == '\n';
    }
    fputs(buffer,fp);
    fprintf(temp,"%d",task->id);

    fprintf(back,"%d",1);

    fclose(fp);
    fclose(temp);
    fclose(tmp);
    fclose(back);
    return 0;
}

int removeTask(int num) {
    int id, i, cnt, c, test;
    char buffer[MAX_TOTAL];
    char str[MAX_LEN];

    FILE * temp = fopen("count.txt","r+");
    if (temp == NULL) {
        fprintf(stderr,"Error, try again\n");
        return 1;
    }

    fscanf(temp,"%d",&cnt);
    rewind(temp);
    
    if (cnt == 0) {
        printf("List is currently empty, please add a task first\n");
        fclose(temp);
        return 2;
    }
    
    while (num < 1 || num > cnt) {
        printf("\n");
        fprintf(stderr, "Invalid input, please choose a number in [1,%d]\n", cnt);
        scanf("%d", &num);
        c = getchar();
    }

    FILE * fp = fopen("main.txt","a+");
    if (fp == NULL) {
        fprintf(stderr,"Error opening file\n");
        fclose(temp);
        return 1;
    }

    FILE * tmp = fopen("temp.txt","w+");
    if (tmp == NULL) {
        fprintf(stderr,"Error opening file\n");
        fclose(fp);
        fclose(temp);
        return 1;
    }

    FILE * back = fopen("data/back.txt","r+");
    if (back == NULL) {
        fprintf(stderr,"Error, try again\n");
        fclose(fp);
        fclose(tmp);
        fclose(temp);
        return 1;
    }

    char ** ar = (char **)malloc(cnt*sizeof(char *));
    if (ar == NULL) {
        fprintf(stderr,"malloc failed\n");
        fclose(fp);
        fclose(temp);
        fclose(tmp);
        return 1;
    }
    for (i = 0; i < cnt; i ++) {
        ar[i] = (char *)malloc(MAX_TOTAL*sizeof(char));
        if (ar[i] == NULL) {
            fprintf(stderr,"malloc failed\n");
            i --;
            while (i > -1) {
                free(ar[i]);
                i --;
            }
            fclose(fp);
            fclose(temp);
            fclose(tmp);
            return 1;
        }
    }

    i = 0;
    while (i < cnt && fgets(buffer,sizeof(buffer),fp) != NULL) {
        snprintf(ar[i], MAX_TOTAL,"%s",buffer);
        i ++;
    }

    //write up to line we have to remove - 1
    for (i = 0; i < num-1; i ++) {
        fputs(ar[i],tmp);
    }

    for (i = num; i < cnt; i ++) {
        sscanf(ar[i],"%d. %[^\n]100s", &id,str);
        snprintf(ar[i],MAX_TOTAL,"%d. %s",id-1,str);
    }

    for (i = num; i < cnt; i ++) {
        fputs(ar[i],tmp);
        fputc('\n',tmp);
    }

    fprintf(temp,"%d",--cnt);
    fprintf(back,"%d",2);

    rename("main.txt","prev.txt");
    rename("temp.txt","main.txt");


    for (i = 0; i < cnt; i ++) {
        free(ar[i]);
    }
    free(ar);
    fclose(temp);
    fclose(back);
    fclose(tmp);
    fclose(fp);
    return 0;
}

int takeback(void) {
    FILE * back = fopen("data/back.txt","r+");
    if (back == NULL) {
        fprintf(stderr,"Error, try again\n");
        return -2;
    }

    FILE * tmp = fopen("count.txt","r+");
    if (tmp == NULL) {
        fprintf(stderr,"Error, try again\n");
        fclose(back);
        return -2;
    }

    int count, num;
    fscanf(back,"%d",&num);
    rewind(back);

    if (num == 5) { //last ac was takeback
        fclose(back);
        fclose(tmp);
        return -1;
    } else if (num == 0 || num == 3) { //last ac print list
        fclose(back);
        fclose(tmp);
        return -2;
    }

    fscanf(tmp,"%d",&count);
    rewind(tmp);
    if (num == 1) { //add was last action
        fprintf(tmp,"%d",--count);
    } else if (num == 2) { //rm was last ac
        fprintf(tmp,"%d",++count); 
    }

    rename("main.txt","temp.txt");
    rename("prev.txt","main.txt");
    rename("temp.txt","prev.txt");
    fprintf(back,"%d",5);
    fclose(back);
    fclose(tmp);
    return 0;
}

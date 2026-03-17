#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUBJECTS 10
#define MAX 100

typedef struct {
    int id;
    char name[50];
    int marks[SUBJECTS]; 
    int total;
    float percentage;
    char grade;
} Student;


Student students[MAX];
int count = 0;
char adminPass[20] = "admin123";

void loadPassword();
int main() {
    loadPassword();
    
    int choice;
    while(1) {
        printf("\n--- Welcome to Datanaut ---\n");
        printf("1. Admin Mode\n2. Student Mode\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch(choice) {
            case 1: adminMode(); break;
            case 2: studentMode(); break;
            case 3: saveData(); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void loadPassword() {
    FILE *fp = fopen("admin.txt", "r");

    if (fp == NULL) {
        // first time → default password
        strcpy(adminPass, "admin123");

        fp = fopen("admin.txt", "w");
        fprintf(fp, "%s", adminPass);
        fclose(fp);
    } else {
        fscanf(fp, "%s", adminPass);
        fclose(fp);
    }
} 
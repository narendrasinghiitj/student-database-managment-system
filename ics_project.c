#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUBJECTS 10
#define MAX 100

typedef struct
{
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
void changePassword();
void addstudent();

int main()
{
    loadPassword();

    int choice;
    while (1)
    {
        printf("\n--- Welcome to Datanaut ---\n");
        printf("1. Admin Mode\n2. Student Mode\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            adminMode();
            break;
        case 2:
            studentMode();
            break;
        case 3:
            saveData();
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void loadPassword()
{
    FILE *fp = fopen("admin.txt", "r");

    if (fp == NULL)
    {
        // first time → default password
        strcpy(adminPass, "admin123");

        fp = fopen("admin.txt", "w");
        fprintf(fp, "%s", adminPass);
        fclose(fp);
    }
    else
    {
        fscanf(fp, "%s", adminPass);
        fclose(fp);
    }
}
void changePassword()
{
    char oldPass[50], newPass[50];

    printf("Enter old password: ");
    scanf("%s", oldPass);

    if (strcmp(oldPass, adminPass) == 0)
    {
        printf("Enter new password: ");
        scanf("%s", newPass);

        FILE *fp = fopen("admin.txt", "w");
        fprintf(fp, "%s", newPass);
        fclose(fp);

        strcpy(adminPass, newPass);

        printf("Password changed successfully!\n");
    }
    else
    {
        printf("Wrong password!\n");
    }
}


void addStudent() {
    if(count >= MAX) {
        printf("Student limit reached!\n");
        return;
    }
    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    while(getchar()!='\n');
    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    s.total = 0;
    for(int i=0; i<3; i++) {
        printf("Enter marks for subject %d: ", i+1);
        scanf("%d", &s.marks[i]);
        s.total += s.marks[i];
    }
    s.percentage = s.total / 3.0;
    s.grade = calculateGrade(s.percentage);

    students[count++] = s;
    printf("Student added successfully!\n");
    saveStudentToFile(s);
  }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "students.dat"

typedef struct
{
    char id[20];
    char name[50];
    char dob[15];
    char subjects[10][20];
    int numSubjects;
    int credits[10];
    int total;
    float percentage;
    char grade;
    float cgpa;
} Student;

Student students[MAX];
int count = 0;
char adminPass[20] = "admin123";

void loadData();
void saveData();
void displayStudent(Student s);
void displayAll();
void loadPassword();
void changePassword();
void addStudent();
void adminMode();
void studentMode();
void saveData();
char calculateGrade();
void saveStudentToFile();
void updateStudent();
void deleteStudent();
void loadStudents();
void showDashboard();


void saveData() { printf("saveData called\n"); }
char calculateGrade() { return 'A'; }
void saveStudentToFile() { printf("saveStudentToFile called\n"); }
void updateStudent() { printf("updateStudent called\n"); }
void deleteStudent() { printf("deleteStudent called\n"); }
void loadStudents() { printf("loadStudents called\n"); }
void showDashboard() { printf("showDashboard called\n"); }
void studentMode() { printf("studentMode called\n"); }

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

void displayStudent(Student s) {
    printf("---------STUDENT-DETAILS---------");
    printf("\nID: %s\nName: %s\nDOB: %s\n",s.id, s.name, s.dob);

printf("\nSubjects | Marks | Credits:\n");
for(int i=0; i<s.numSubjects; i++) {
    printf("%s : %d | %d\n", (s.subjects+i),(s.marks+i),*(s.credits+i));
}

printf("\nTotal: %d\nPercentage: %.2f\nGrade: %c\nCGPA: %.2f\n",s.total, s.percentage, s.grade,s.cgpa);
       printf("***********");
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
  } void adminMode() {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);
    if(strcmp(password, adminPass) != 0) {
        printf("Incorrect password! Access denied.\n");
        return;
    }

    int choice;
    while(1) {
        printf("\n--- Admin Mode ---\n");
        printf("1. Add Student\n2. Update Student Details\n3. Delete Student\n");
        printf("4. Display All Students\n5. Dashboard\n6. Change Admin Password\n7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: loadStudents(); break;
            case 5: showDashboard(); break;
            case 6: changePassword(); break;
            case 7: return;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
void saveData() {
    FILE *fp = fopen(FILE_NAME, "wb");

    if(fp == NULL) {
        printf("Error saving data!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), count, fp);

    fclose(fp);
}
char calculateGrade(float percentage) {
    if (percentage >= 90)
        return 'A';
    else if (percentage >= 80)
        return 'B';
    else if (percentage >= 70)
        return 'C';
    else if (percentage >= 60)
        return 'D';
    else if (percentage >= 50)
        return 'E';
    else
        return 'F';
}

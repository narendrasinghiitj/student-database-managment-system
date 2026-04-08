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
    int marks[10];
    int credits[10];
    int marks[10];
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
void hashPassword(char *str);

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
}
    
Student students[MAX];
int count = 0;
char adminPass[20] = "admin123";

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
    printf("%s : %d | %d\n", *(s.subjects+i),*(s.marks+i),*(s.credits+i));
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
    int *m = s.marks;
    int *c = s.credits;
    printf("Enter Student ID: ");
    scanf("%s", &s.id);
    while(getchar()!='\n');
    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Date of Birth(dd/mm/yyyy):");
    scanf("%s",s.dob);
    printf("Enter number of Subjects;");
    scanf("%d",&s.numSubjects);

    students[count++] = s;
    printf("Student added successfully!\n");
    saveStudentToFile(s);
  } 
  void updateStudent() {
    char id[20];
    int found = 0;

    printf("Enter ID to update: ");
    scanf("%s", id);

    for(int i=0; i<count; i++) {
        if(strcmp(students[i].id, id) == 0) {

            found = 1;

            while(getchar()!='\n');

            printf("Enter new name: ");
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            float totalGP = 0;
            int totalCredits = 0;

            students[i].total = 0;

    for(int j = 0; j < students[i].numSubjects; j++) {

            printf("Enter subject %d name: ", j+1);
            scanf("%s", students[i].subjects[j]);

            printf("Enter marks for %s: ", students[i].subjects[j]);
            scanf("%d", &students[i].marks[j]);

            printf("Enter credits for %s: ", students[i].subjects[j]);
            scanf("%d", &students[i].credits[j]);

            students[i].total += students[i].marks[j];

            float gp = getGradePoint(students[i].marks[j]);
            totalGP += gp * students[i].credits[j];
            totalCredits += students[i].credits[j];
}

            students[i].cgpa = totalGP / totalCredits;
            students[i].percentage = students[i].total / (float)students[i].numSubjects;

           
            printf("Updated successfully!\n");
            break;
        }
    }

    if(!found) printf("Student not found!\n");

    saveData();
}
 
  
  void adminMode() {
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

//studentmode

void studentMode() {
    char id[20], dob[15];
    int found = 0;

    printf("Enter Student ID: ");
    scanf("%s", id);

    printf("Enter DOB (dd/mm/yyyy): ");
    scanf("%s", dob);

    for(int i=0; i<count; i++) {
        if(strcmp(students[i].id, id) == 0) {
            if(strcmp(students[i].dob, dob) == 0) {
                displayStudent(students[i]);
            } else {
                printf("Incorrect DOB!\n");
            }
            found = 1;
            break;
        }
    }

    if(!found) printf("Student not found!\n");
}

void loadData() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if(fp == NULL){
        count=0;
        return;
    }
    fread(&count, sizeof(int), 1, fp);
    fread(students, sizeof(Student), count, fp);
    if(count<0||count>MAX){
        count=0;
    }

    fclose(fp);
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
float getGradePoint(int p){
    if(p >= 90) return 10;
    else if(p >= 80) return 9;
    else if(p >= 70) return 8;
    else if(p >= 60) return 7;
    else if(p >= 50) return 6;
    else if(p >= 40) return 5;
    else if(p >= 30) return 4;
    else if(p >= 20) return 3;
    else if(p >= 10) return 2;

    else return 0;
}
void clearAllData() {
    FILE *fp = fopen(FILE_NAME, "wb");

    if(fp != NULL) {
        int zero = 0;
        fwrite(&zero, sizeof(int), 1, fp);
        fclose(fp);
    }

    count = 0;

    printf("All data cleared!\n");
}
void searchStudent() {
    char id[20];
    int found = 0;

    printf("Enter Student ID to search: ");
    scanf("%s", id);

    for(int i = 0; i < count; i++) {

        if(strcmp(students[i].id, id) == 0) {

            printf("\nStudent Found:\n");
            displayStudent(students[i]);   // direct access (no pointer)

            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Student not found!\n");
    }
}
void searchStudent() {
    char id[20];
    int found = 0;

    printf("Enter Student ID to search: ");
    scanf("%s", id);

    for(int i = 0; i < count; i++) {

        if(strcmp(students[i].id, id) == 0) {

            printf("\nStudent Found:\n");
            displayStudent(students[i]);   // direct access (no pointer)

            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Student not found!\n");
    }
}
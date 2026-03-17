// student-database-managment-system
//A Simple Student DataBase Management System in c using file handling to store and manage student records such as roll numbers, name,deparment and marks.
#include<stdio.h>
#define passkey 0000

int main(){
   int key;
  printf("====student managment system====\n");
  printf("enter key : ");
  scanf("%d",&key);
  if(key != passkey){
    printf("wrong key");
    return 0;
    }
    else{
    printf("permission granted");
    }
    return 0;
    }

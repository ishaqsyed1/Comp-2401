#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "struct.h"
#include "student.h"

/**************************************************************/
/* Print a student

input:
p - Single person

output:
person - prints out the student and their stats
*/
void printStudents(struct Person p){
  char temp[50];
  int gpa1 = p.stu.gpa;
  int nc = p.stu.numCourses;
  float tf = p.stu.tuitionFees;

  char *fir = p.firstName;
  char *fam = p.familyName;
  char *phone = p.telephone;

  sprintf(temp, "%s %s", fir, fam);
  printf("%-33s", temp);
  printf("GPA:  %d, Courses: %d, Tuition: %.2f\n", gpa1, nc, tf);
}

/**************************************************************/
/* Prints all the students

input:
p - array of person
numb - size needed

output:
person - It sends the person to printStudents();
*/
void printAllStudents(struct Person p[], int numb){
  int a;
  for (a = 0; a < numb; a++){
    if (p[a].emplyeeOrStudent == 1){
      printStudents(p[a]);
    }
  }
  printf("\n");
  printf("\n");
}
/**************************************************************/
/* Prints the chosen student

input:
p - array of person
size - the size needed

output:
student - Prints the chosen student
*/
void printStudentByFamilyName(struct Person p[], int size){
  int counter = 0;
	int check = 1;
  int a;
	while(check != 0){
		printf("Please enter the Student Family Name you want to search with:  ");
		char searchName[100];
    scanf("%s", searchName);

			for(a = 0; a < size; a++){
				if(p[a].emplyeeOrStudent == 1 && strcmp(p[a].familyName,searchName) == 0){
					printStudents(p[a]);
          counter += 1;
		    }
			}

			printf("----Search is completed----\n");
			check = 0;
	}
  if (counter == 0){
    printf("No one with that family name was found!\n");
  }

}

#include "stdio.h"
#include "stdlib.h"
#include "struct.h"

#include "populateRecords.h"
#include "student.h"
#include "employee.h"

#define NUM_RECORDS 20

void menu(struct Person person[]);
void quitCheck();
void summaryOfRecords(struct Person p[], int numb);

int main(int argc, char* argv[])
{
  struct Person person[NUM_RECORDS];
  populateRecords(person, NUM_RECORDS);
  menu(person);
  return 0;
}
/**************************************************************/
/* Gives the user a menu to choose from

input:
person - array of person to send to other functions

output:
None - Program does not return anything, runs until user exits
*/
void menu(struct Person person[])
{
  //char choice[30];
  unsigned int choice;
  int flag = 0;
  while(flag == 0){
    printf("\n");
    printf("1. Print all employees\n");
    printf("2. Print all students\n");
    printf("3. Search students using family name\n");
    printf("4. Summary of data\n");
    printf("0. Quit\n");
    printf("\n");

    printf("Choice: ");
    scanf("%u", &choice);

    switch (choice) {
      case 0:
        quitCheck();
        break;
      case 1:
        printAllEmployees(person, NUM_RECORDS);
        break;
      case 2:
        printAllStudents(person, NUM_RECORDS);
        break;
      case 3:
        printStudentByFamilyName(person, NUM_RECORDS);
        break;
      case 4:
        summaryOfRecords(person, NUM_RECORDS);
        break;
      default:
          printf("That is not a valid option\n");
    }

  }


}

/**************************************************************/
/* Checks if the user wants to quit

input:
Nothing

output:
None - Program does not return anything
*/
void quitCheck(){
  printf("You are about to quit, is this what you want to do? (y/n)\n");
  char final[10];

  scanf("%s", final);
  if (strcmp(final,"y") == 0){
    exit(0);
  }
  else if (strcmp(final,"n") == 0){
  }
  else{
    printf("That is not one of the options\n");
  }
}

/**************************************************************/
/* Summarizes all of the records and stats

input:
person - array of persons, to access the stats
numb - size of array

output:
None - Program does not return anything, runs until user exits
*/
void summaryOfRecords(struct Person p[], int numb){

	int totalRecords = 0;

	int students = 0;
	int totalGPA = 0;
	int courses = 0;
	int tuition = 0;

	int employees = 0;
	int minimum = 15;
	int maximum = 0;
	int years = 0;
	int salary = 0;

  float finalGPA;
  float finalCourses;
  float finalTuition;

  float finalYears;
  float finalSalary;

	int a;
	for(a = 0; a < numb; a++){

		if(p[a].emplyeeOrStudent == 1){
			totalGPA += p[a].stu.gpa;
			courses += p[a].stu.numCourses;
			tuition += p[a].stu.tuitionFees;
      students++;
    }

    else{
			years += p[a].emp.yearsService;
			salary += p[a].emp.salary;

			if(p[a].emp.level > maximum){
				maximum = p[a].emp.level;
			}

			if(p[a].emp.level < minimum){
				minimum = p[a].emp.level;
			}
      employees++;
		}
    totalRecords++;
	}

	finalGPA = totalGPA/students;
	finalCourses = courses/students;
	finalTuition = tuition/students;
  finalYears = years/employees;
  finalSalary = salary/employees;

  printf("----OUTPUT----\n");
	printf("Total number of records: %d\n", totalRecords);
	printf("Student Stats:\n");
	printf("Number of Students: %d\n", students);
	printf("Average GPA: %.2f", finalGPA);
	printf(", Average Number of courses: %.2f", finalCourses);
	printf(", Average Tutition Fees: %.2f\n", finalTuition);
	printf("Employees Stats:\n");
	printf("Number of Employees: %d", employees);
	printf("  Min Level: %d", minimum);
	printf("	Max Level: %d\n", maximum);
	printf("Average Years of Service:  %.2f", finalYears);
	printf(", Average Salary:  %.2f\n\n", finalSalary);
  printf("----END OF SUMMARY----\n");

}

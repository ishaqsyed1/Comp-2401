#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "struct.h"
#include "employee.h"

/**************************************************************/
/* Print an employee

input:
p - Single person

output:
person - prints out the employee and their stats
*/
void printEmployees(struct Person p){
  char temp[50];
  float sal = p.emp.salary;
  int ys = p.emp.yearsService;
  int lev = p.emp.level;

  char *fir = p.firstName;
  char *fam = p.familyName;
  char *phone = p.telephone;

  sprintf(temp, "%s %s", fir, fam);
  printf("%-33s", temp);
  printf("Years:  %d, Level: %d, Salary: %.2f \n", ys, lev, sal);
}

/**************************************************************/
/* Prints all the employees

input:
p - array of person
numb - size needed

output:
person - It sends the employees to printEmployees();
*/
void printAllEmployees(struct Person p[], int numb){
  int a;
  for (a = 0; a < numb; a++){
    if (p[a].emplyeeOrStudent == 0){
      printEmployees(p[a]);
    }
  }
  printf("\n");
  printf("\n");
}

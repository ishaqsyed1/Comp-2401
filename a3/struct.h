
#ifndef struct_h
#define struct_h
#define NAME_SIZE 15
#define TELEPHONE_SIZE 10

struct Student{
  unsigned int gpa:4;
  unsigned int numCourses:6;
  float tuitionFees;
};

struct Employee{
  float salary;
  unsigned int yearsService:6;
  unsigned int level:4;
};

struct Person{
  char firstName[15];
  char familyName[15];
  char telephone[10];
  unsigned int emplyeeOrStudent:1;
  union {
  	struct Student stu;
  	struct Employee emp;
  };
};

#endif

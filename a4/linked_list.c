
/*
File name is linked_list.c
 Purpose: file contains functions for manipulating singly linked list

 Created By
 Doron Nussbaum 2016

 Modifications:
 November 2017 - minor modifications


 Copyright 2017

 */

/******************************************************************/
// INCLUDE

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list.h"


/************************************************************************/
// Define



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
id - id of person
firstName - first name of person
familyName - family name of person

input/output
head - head of linked list

return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/

PersonalInfo *insertToList(PersonalInfo **head, unsigned int id, char *firstName, char *familyName)
{
  PersonalInfo *newNode = (PersonalInfo*) malloc(sizeof(PersonalInfo));
  newNode->id = id;
  strcpy(newNode->firstName, firstName);
  strcpy(newNode->familyName, familyName);
  newNode->next = (*head);
  (*head) = newNode;

}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node

Input
node - the node after which the new node must be added to the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/


PersonalInfo *insertAfter(PersonalInfo *node, unsigned int id, char *firstName, char *familyName)
{
  if (node == NULL){
    printf("This node cannot be null!\n");
    return;
  }
  else{
    PersonalInfo *node2 = (PersonalInfo*) malloc(sizeof(PersonalInfo));
    node2->id = id;
    strcpy(node2->firstName,firstName);
    strcpy(node2->familyName,familyName);
    node2->next = node->next;
    node->next = node2;
    return node2;
  }

}

/************************************************************************/
/*
Purpose: create a new node and insert it into the end of the list
Input
head - the head of the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/


PersonalInfo *insertLast(PersonalInfo **head, unsigned int id, char *firstName, char *familyName)
{
	PersonalInfo *first = (PersonalInfo*) malloc(sizeof(PersonalInfo));
   	PersonalInfo *end = *head;
    	
    	strcpy(first->firstName, firstName);
    	strcpy(first->familyName, familyName);
	first->id = id;
   	first->next = NULL;
    
   	if(*head == NULL) {
    	 	*head = first;
    	   	return NULL;
   	}	
	else{
   		while(end->next != NULL){
        		end = end->next;
    		}
	}
	end->next = first;
   	return (first);
}


/************************************************************************/
/*
Purpose: search for the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


PersonalInfo *searchByName(PersonalInfo *head, char *firstName)
{
  if (head == NULL){
    return NULL;
  }
  else{
    PersonalInfo *checker = NULL;
    int flag = 0;
    checker = head;

    while(flag == 0){
      if(strcmp(checker->firstName, firstName) == 0){
        flag = 1;
        return checker;
      }
      else if(checker->next == NULL){
        flag = 1;
        return NULL;
      }
      else{
        checker = checker->next;
      }
    }
    return NULL;
  }
}

/************************************************************************/
/*
Purpose: search for the first node with the matching id
Input
head - the head of the list
id - id of person person

return
a pointer to the node that was allocated.

NULL - if no node was found or list empty

*/


PersonalInfo *searchById(PersonalInfo *head, unsigned int id)
{
  if (head == NULL){
    return NULL;
  }
  else{
    PersonalInfo *checker = NULL;
    int flag = 0;
    checker = head;

    while(flag == 0){
      if(checker->id == id){
        flag = 1;
        return checker;
      }
      else if(checker->next == NULL){
        flag = 1;
        return NULL;
      }
      else{
        checker = checker->next;
      }
    }
    return NULL;
  }
}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(PersonalInfo **head, unsigned int *id, char *firstName, char *familyName)

{
	if(*head == NULL){
		return 1;
	}
	else{

		PersonalInfo *node = *head;
		*head = node->next;

		strcpy(firstName, node->firstName);
		strcpy(familyName, node->familyName);
		*id = node->id;

		free(node);
		return 0;
	}

}


/***************************************************************/

/*
Purpose: delete the last node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteLast(PersonalInfo **head, unsigned int *id, char *firstName, char *familyName)
{
	PersonalInfo *node = *head;
  	PersonalInfo *temp;
  	if(node == NULL){
    		return 1;
  	}
  	else if(node->next==NULL){
		*head = node->next;
		strcpy(firstName, node->firstName);
		strcpy(familyName, node->familyName);
		*id = node->id;
    		return 0;
  	}
  	else{
    		while(node->next->next != NULL){
      			node=node->next;
    		}
		temp = node->next;
    		node->next=NULL;
		return 0;
  	}
}



/************************************************************************/

/*
Purpose: delete the record after the given node
Input
node - a node in the list

output
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0 if node was deleted
1 if node was not deleted (either input node is NULL or input node was the lastnode in the list)

*/



int deleteAfter(PersonalInfo *node, unsigned int *id, char *firstName, char *familyName)

{
  if (node != NULL && node->next != NULL){
    PersonalInfo *node2 = node->next;

    node->next = node2->next;
    *id = node2->id;
    strcpy(firstName, node2->firstName);
    strcpy(familyName, node2->familyName);

    free(node2);
    return 0;
  }
  else{
    return 1;
  }
}

/************************************************************************/

/*
Purpose: delete the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0  if node was deleted
1 if node was not found (e.g., list is empty, no such node exists)

*/


int deleteNodeByName(PersonalInfo **head, char *firstName, char *familyName, unsigned int *id)
{
	if (*head == NULL){
		return 1;
  	}
  	else{
  		if((*head)->firstName == NULL){
			return 1;
		}
		PersonalInfo *checker = NULL;
		PersonalInfo *last = NULL;
		int flag = 0;
		checker = *head;

    		while(flag == 0){
      			if(strcmp(checker->firstName, firstName) == 0){
        			flag = 1;
				if (last != NULL){
					last->next = checker->next;
					free(checker);
				}
				else{
					if(checker->next == NULL){
						*head = NULL;
						free(checker);
					}
					else{
					*head = checker->next;
					free(checker);
					}
				}
				return 0;

			}
			else if(checker->next == NULL){
				flag = 1;
			}
			else{
				last = checker;
				checker = checker->next;
			}
		}
		
		return 1;
	}
	
}
/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(PersonalInfo **head)
{
  if (head == NULL){
	return;
  }
  else{
		if((*head)->firstName == NULL){
			*head = NULL;
			return;
		}
		PersonalInfo *temp = NULL;
		temp = *head;

		PersonalInfo *following = NULL;
    		int flag = 0;
		

		while (flag == 0){
			if(temp->next == NULL){
				flag = 1;
				free(temp);
				//temp->next = NULL;
			}else{
				following = temp->next;
				free(temp);
				//temp->next = NULL;
				temp = following;
			}
		}
	}
	*head = NULL;
}



/************************************************************************/
/*
Purpose: prints the fields of a node
input:
node - a pointer to a given node

*/


void printNode(PersonalInfo *node)
{
	printf("%-20s %-20s %7d \n",node->firstName, node->familyName, node->id);

}


/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
*/


void printList(PersonalInfo *head)
{
  int flag = 0;
  if(head == NULL){
		return;
  }
  else{
		PersonalInfo *temp = NULL;
		temp = head;

		while (flag == 0){
			printNode(temp);
			if(temp->next == NULL){
				flag = 1;
			}
      else{
				temp = temp->next;
			}
		}
	}
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list
input
head - the head of the list

return
the number of nodes in the list

*/


int listSize(PersonalInfo *head)
{
	int number = 0;
	int flag = 0;
  	if(head == NULL){
		return number;
  	}
  	else{
		PersonalInfo *temp = NULL;
		temp = head;

		while (flag == 0){
      			number += 1;
			if(temp->next == NULL){
				flag = 1;
			}
     			else{
				temp = temp->next;
			}
		}
		return number;
	}
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list with a matching firstName
input
head - the head of the list

return
the number of nodes in the list that match the firstName


*/


int countRecords(PersonalInfo *head, char *firstName)
{
	int number = 0;
	int flag = 0;

	if(head == NULL){
		return number;
	}
  	else{
		PersonalInfo *temp = NULL;

		temp = head;
		while (flag == 0) {
			if(strcmp(temp->firstName,firstName) == 0){
				number++;
			}
			if(temp->next == NULL){
				flag = 1;
			}
      			else{
				temp = temp->next;
			}
		}
		return number;
	}

}




/************************************************************************/
/*

Purpose: removes all duplicates records from the list.  Duplicate records are determined by their first name.
You can assume that the listed is sorted by first name.

input
head - the head of the  list



*/




void removeDuplicates(PersonalInfo *head)
{
	PersonalInfo *temp = head, *p;
	if (temp == NULL){
		return;
  	}

  	while (temp->next != NULL) {
    		if (strcmp(temp->firstName, temp->next->firstName) == 0) {
      			p = temp->next->next;
      			free(temp->next);
      			temp->next = p;
    		}
    	else{
      		temp = temp->next;
    	}
  	}
}

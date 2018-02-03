

/*



File receive.c





Purpose: simulate the receiveing end of a message over the network.



The program converts a message encodded as an array of short integers into characters.

The input message uses 1-bit error correction code.

As part of the simulation, the program also corrects any 1-bit errors in the receiving message.





Revision:

a. Initial code - Doron Nussbaum





*/





/************************************************************************/



// INCLUDE FILES



#include "stdio.h"

#include "stdlib.h"

#include "string.h"

#include "assert.h"

#include "bit_manipulation.h"





/************************************************************************/

//MACROS  / DEFINES







#define XSTR(A) STR(A)

#define STR(A) #A

#define MAX_INPUT_LENGTH 8192

#define MAX_MSG_LENGTH 2048

#define P1_MASK 0xaa8   // 0b0101010101000

#define P2_MASK 0xcc8	// 0b0110011001000

#define P4_MASK 0x10e0	// 0b1000011100000

#define P8_MASK 0x1e00  // 0b1111000000000





/************************************************************************/

// FUNCTION PROTOTYPES





void short2Char(short encodedChar, char *c);

void correctCode(short *num);

void readEncodedMessage(short *buf, int len, int *numRead);









/**************************************************************************/



int main(int argc, char *argv[])



{

	int rc = 0;		// return code



	char s[MAX_MSG_LENGTH] = { '\0' };  // message

	short encodedMsg[MAX_MSG_LENGTH];

	int numRead = 0;  // number of characters in the message

	int i;



	// read the message

	printf("Please enter the transmitted message: ");

	readEncodedMessage(encodedMsg, MAX_MSG_LENGTH, &numRead);







	// print the corrected message

	printf("\n\n Transmitted Message:\n");

	for (i = 0; i < numRead; i++) {

		char c;

		short2Char(encodedMsg[i], &c);

		printf("%c", c);

    }

    printf("\n");



    // correct the message

	for (i = 0; i < numRead; i++) {

		correctCode(&encodedMsg[i]);

	}



	// print the corrected message

	printf("\n\n Corrected Transmitted Message:\n");

	for (i = 0; i < numRead; i++) {

		char c;

		short2Char(encodedMsg[i], &c);

		printf("%c", c);

	}

	printf("\n");



	return(0);

}





/***********************************************************************************/

/* reads a message from the user



input

len - maximum length of mesage that should be read



output

receivedMsg - contains the message

numRead - the number of characters in the message



*/





void readEncodedMessage(short *receivedMsg, int len, int *numRead)

{

	int i;

	int rc;

	char s[MAX_INPUT_LENGTH+1];

	char *token = NULL;

	*numRead = 0;



	s[MAX_INPUT_LENGTH] = '\0';

	scanf("%"XSTR(MAX_INPUT_LENGTH)"[^\n]s", s);

	token = strtok(s, " ");



	for (i = 0; token != NULL  &&  i < len;token = strtok(NULL, " "), i++) {

		rc = sscanf(token, "%hd", &receivedMsg[i]);

	}



	*numRead = i; // set the number of read integers



    // empty the input buffer

    for( ; getchar() != '\n'; );





}









/*************************************************************************/

/* collect of a short bits 3,5,6,7,9,10,11,12  to bits 0-7 of a char



input

encodedNum - a short with the bits of c



output

c - the char that is embedded in encodedNum



*/





void short2Char(short encodedNum, char *c)



{

	short mask = 0x0001;

	int i;

	int bitSet;

	int test;

	*c = 0;

	for (i = 0; i < 8; i++) {

		switch (i) {

		case 0:

			//setCharBit(3, c);

			test = 3;

			break;

		case 1:

		case 2:

		case 3:

			//setCharBit(4 + i, c);

			test = 4+i;

			break;

		case 4:

		case 5:

		case 6:

		case 7:

			//setCharBit(5 + i, c);

			test = 5+i;

			break;

		default:

			printf("This should not happen !!!!\n");

			assert(0);

		}

		bitSet = isShortBitSet(encodedNum, test);

		if (bitSet == 0) continue;

		setCharBit(i, c);

	}

		// set the correct bit in char

		// for each bit i do

		// if the corrsponding bit in the encodedChar is set

		// set the bit at the char c

}





/*************************************************************************************/





/* purpose:

performs error corrrections, if needed on the short integer



The function first checks the parity bits for error.

If there is an error then it fixes it.



input

num - the address of the short number

*/





void correctCode(short *num)



{

	int mask;

	int sum;

	int counter;

	int bitNumber = 0; //  bit number with the error bit

	int parity;		// a parity bit either 0 or 1

	int storedParity; // the parity bit in the encoded char



	//Reset the initial parity

	parity = 0;

	storedParity = isShortBitSet(*num, 1);

	counter = numOfBits(*num & P1_MASK);

	if(counter % 2 != 0){

		parity = 1;

	}

	if(parity != storedParity){

		bitNumber += 1;

	}

		// check parity bit p1

    // get the bits related to P1 using P1_MASK

    // count the bits

    // determine if the parity bit should have been set

		// get the parity for P1_MASK that is stored in *num

    // compare the calculated parity with the stored parity

    // if the two parities are different add 2^0 to bitNumber



		parity = 0;

		storedParity = isShortBitSet(*num, 2);

		counter = numOfBits(*num & P2_MASK);

		if(counter % 2 != 0){

			parity = 1;

		}

		if(parity != storedParity){

			bitNumber += 2;

		}



		// simlilary check parity bit p2

    // calculate the parity for P2

    // compare the calculated parity with the stored parity

		// if the two parities are different add 2^1 to bitNumber



		parity = 0;

		storedParity = isShortBitSet(*num, 4);

		counter = numOfBits(*num & P4_MASK);

		if(counter % 2 != 0){

			parity = 1;

		}

		if(parity != storedParity){

			bitNumber += 4;

		}

		// check parity bit p4

    // calculate the parity for P4

    // compare the calculated parity with the stored parity

		// if the two parities are different add 2^2 to bitNumber



		parity = 0;

		storedParity = isShortBitSet(*num, 8);

		counter = numOfBits(*num & P8_MASK);

		if(counter % 2 != 0){

			parity = 1;

		}

		if(parity != storedParity){

			bitNumber += 8;

		}

		// check parity bit p8

    // calculate the parity for P8

    // compare the calculated parity with the stored parity

		// if the two parities are different add 2^3 to bitNumber







    // if necessary flip the bit at position bitNumber

		flipBitShort(bitNumber, num);

}



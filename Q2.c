#include "exam.h"

int recStrcmp(char* st1, char* st2)
{
	/******** DON'T CHANGE ********/
	fx1(); // do not change!!!
	/******************************/
	
	/*Write your code down here*/	

	//if thus far, characterwise, st1 and st2 were equal,
	//but there are no more characters in st2, it means s1 is greater
	if (*st1 && !*st2) {
		return 1;
	}
	//the mirror case 
	if (!*st1 && *st2) {
		return -1;
	}
	//if we reached null terminator for both string,
	//then they are equal, since otherwise,
	//one of the previous stop conditions would have been met.
	if (!(*st1 && *st2)) {
		return 0;
	}
	//If we got here, means both st1 and st2 have characters to compare

	//If equal, need to continue req, with pointers+1
	if(*st1 == *st2){
		return recStrcmp(st1 + 1, st2 + 1);
	}
	//else, we can return a value,
	//since one character is lexicographically greater then the other

	if (*st1 < *st2) {
		return -1;
	}
	else {
		return 1;
	}
}

#include "exam.h"

int* processDigits(int numbers[], int size)
{
	/*Initialise array to be zeros*/
	int* arr = (int*)malloc(10 * sizeof(int));
	for (int j = 0; j < 10; j++) {
		arr[j] = 0;
	}
	for (int i = 0; i < size; i++) {
		int num = numbers[i];
		/*Traversing over the digits of the number numbers[i]*/
		while (num) {
			int dig = num % 10;
			/*Instructions demanded we only care about appearances of digits 1-9*/
			if (num) {
				arr[dig] = 10* arr[dig] + dig;
			}
			num /= 10;
		}
	}
	return arr;
}
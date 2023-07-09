#include "exam.h"

// the function calculates the distance between location 1 to location 2; feel free to use it
float distance( Location l1, Location l2 )
{
	return (float)sqrt( pow( l1.x - l2.x, 2 ) + pow( l1.y - l2.y, 2 ) );
}


Business** searchBusiness(EasyApp* easyApp,  char* email, int category, int subcategory, int *resultsSize)
{
    return NULL;
}

int deleteEasyUser(EasyApp* easy, char *email)
{
    return -1;
}
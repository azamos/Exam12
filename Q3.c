#include "exam.h"

// the function calculates the distance between location 1 to location 2; feel free to use it
float distance( Location l1, Location l2 )
{
	return (float)sqrt( pow( l1.x - l2.x, 2 ) + pow( l1.y - l2.y, 2 ) );
}


Business** searchBusiness(EasyApp* easyApp,  char* email, int category, int subcategory, float radius, int *resultsSize)
{
    /*Initialize to zero */
    *resultsSize = 0;
    /*Will hold the fitting businesses*/
    Business** queried = NULL;;
    /*First, in order to gain access to the user's preferences 
    and history arrays, I must locate the User's instance in easyApp*/
    User* user = NULL;
    for (int i = 0; i < easyApp->usersSize; i++) {
        if (strcmp(email, easyApp->users[i]->email)) {
            user = easyApp->users[i];
            break;//Once found, look no further.
        }
    }
    if (!user) {
        return NULL;
    }
    /*First, find matching queries in User's preferences array*/
    for (int i = 0; i < user->preferencesSize; i++) {
        Business* prefered = user->preferences[i];
        if (category == prefered->category &&
            subcategory == prefered->subCategory &&
            distance(user->currentLocation, prefered->loc) <= radius) {
            queried = (Business**)realloc(queried,
                (sizeof(Business*))*(1+*resultsSize));
            queried[*resultsSize] = prefered;
            (*resultsSize)++;
        }
    }
    /*Second step: find matching queries in User's history array,
    But only if their id is not already in the queried array*/
    for (int i = 0; i < user->historySize; i++) {
        Business* visited = user->history[i];
        /*First we check if visited is a match,
        and if so, only then we check if it is already in queried*/
        if (category == visited->category &&
            subcategory == visited->subCategory &&
            distance(user->currentLocation, visited->loc) <= radius) {
            int isPrefered = 0;//to signify if already in queried, due to it also beign a prefered bussiness.
            for (int j = 0; j < *resultsSize; j++) {
                if (strcmp(visited->id, queried[j]->id)==0) {
                    isPrefered = 1;
                    break;
                }
            }
            if(!isPrefered){
                queried = (Business**)realloc(queried,
                    (sizeof(Business*)) * (1 + *resultsSize));
                queried[*resultsSize] = visited;
                (*resultsSize)++;
            }
        }
    }
    /*Finally, go over all of the Bussinesses in easyApp,
    and again, add them only if not in the queried array from the previous insertion loops*/
    for (int i = 0; i < easyApp->businessesSize; i++) {
        Business* listed = easyApp->businesses[i];
        /*First we check if listed is a match,
        and if so, only then we check if it is already in queried*/
        if (category == listed->category &&
            subcategory == listed->subCategory &&
            distance(user->currentLocation, listed->loc) <= radius) {
            int isQueried = 0;//to signify if already in queried.
            for (int j = 0; j < *resultsSize; j++) {
                if (strcmp(listed->id, queried[j]->id) == 0) {
                    isQueried = 1;
                    break;
                }
            }
            if (!isQueried) {
                queried = (Business**)realloc(queried,
                    (sizeof(Business*)) * (1 + *resultsSize));
                queried[*resultsSize] = listed;
                (*resultsSize)++;
            }
        }
    }
    return queried;
}

int deleteEasyUser(EasyApp* easy, char *email)
{
    /*step 1: locate User's instance in easy's users list*/
    User* user = NULL;
    for (int i = 0; i < easy->usersSize; i++) {
        if (strcmp(email, easy->users[i]->email)) {
            user = easy->users[i];
            break;
        }
    }
    if (!user) {
        return 0;//Not found
    }
    /*Else, the user was found.
    Step 2: Remove it from the easy's app Users list,
    and decrease the number of users.
    Since it was not specified that the order of the users in the app's list matters,
    I will simply switch with last place, and then reallocate the list to size-1.*/
    User** users = easy->users;
    int n = easy->usersSize;
    for (int i = 0; i < n; i++) {
        if (strcmp(user->email, users[i]->email) == 0) {
            /*Swapping places*/
            users[i] = users[n - 1];
            users[n - 1] = user;//Allready got a reference to users[i], from earlier
            //Now, to remove users[n-1], by reallocating
            easy->users = (User**)realloc(users, sizeof(User*) * (n - 1));
            easy->usersSize--;
            break;//Stop searching
            
        }
    }
    /*finally, last step: free the memory taken by user.
    Step 3: release dynamically allocated fields.
    These fields are: fullName, email,history and preferences.
    Note, that for the lists, only the list itself needs to be freed.
    The instances of Bussiness that they point to, SHOULD not be freed,
    since their existence is not dependant on the existence of one User or another.*/
    free(user->fullName);
    free(user->email);
    free(user->history);
    free(user->preferences);
    /*And finally, free the instance of the User itself*/
    free(user);
    return 1;
}
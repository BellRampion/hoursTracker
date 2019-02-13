#include <stdio.h>
//Program to track hours for various activities

//ALGORITHM DESIGN
/*
-Print available filenames for activities' hours logs
-Get which one the user wants
-Print current hours
-Add new hours
-Store back in file (overwrite)
-Print message for success
*/
//Macros
#define MAXLENGTH 10000

//Prototype statements
int bgetline(char s[], int putNl);
double stringToF(char s[]);
void printFilesMenu(void);

int main(){
    char activityName[MAXLENGTH];
    char userInput[MAXLENGTH];
    char fileline[MAXLENGTH];
    double currentHours;
    double newHours;
    double totalHours;
    FILE *activityFile;
    int call; //throwaway caller

    //Print options, get which one the user wants
    printFilesMenu();
    call = bgetline(activityName, 0);

    //Open file and get hours
    activityFile = fopen(activityName, "r");
    if (fgets(fileline, MAXLENGTH, activityFile) == NULL)
    {
        fprintf(stderr, "ERROR: Nothing in file.\n");
        return -1;
    }
    //Print current hours
    else {
        //Assume the file only contains the hours, no text
        currentHours = stringToF(fileline);
        printf("Current hours: %.2f\n", currentHours);
    }

    //Get new hours and add them to total
    printf("Please enter the additional hours: \n");
    call = bgetline(userInput, 0);
    newHours = stringToF(userInput);
    totalHours = currentHours + newHours;
    printf("Total hours: %.2f\n", totalHours);

    //Close file, re-open for writing, and write totalHours to file
    fclose(activityFile);
    activityFile = fopen(activityName, "w");
    fprintf(activityFile, "%.2f", totalHours);

    //Print closing message
    printf("Finished!\n");

    fclose(activityFile);
    return 0;
} //end of main

//Gets a line from std input
int bgetline(char s[], int putNl){
	int c, i;

	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i)
		s[i] = c;
    //If there is a newline and the caller wants a newline, add it
	if (c == '\n' && putNl == 1)
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

//Converts a string to a double
double stringToF(char s[]){

    double val, power;
    int i, sign;
    i = 0;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for (val = 0.0; (s[i] >=48) && (s[i] <= 57); i++){ //If the character is a numeral,
        val = 10.0 * val + (s[i] - '0'); //the value is equal to 10 times the current value (to move it up one place) plus the numeral converted from ASCII
    }
    if (s[i] == '.')
    {
        i++;
    }
    for (power = 1.0; (s[i] >=48) && (s[i] <= 57); i++){
        val = 10.0 * val + (s[i] - '0'); //the value is equal to 10 times the current value (to move it up one place) plus the numeral converted from ASCII
        power *= 10.0;
    }

    return sign * val / power; //returns the string converted to a double
}

//Prints a list of available files
void printFilesMenu(void){
    char fileline[MAXLENGTH];
    FILE *filesList;
    int iter = 1;

    filesList = fopen("fileOptions.txt", "r");

    while (fgets(fileline, MAXLENGTH, filesList) != NULL){
        printf("%i. %s", iter, fileline);
        iter++;
    }
    printf("Please enter the name of the file you would like to open: \n");
    return;
}

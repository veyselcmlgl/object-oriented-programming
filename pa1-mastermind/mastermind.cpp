#include <iostream>
#include <cstdlib>  // used for srand() and rand()
#include <time.h>   // used for time()
#include <cstring>  // used for some of C string functions

using namespace std;

// This function creates unique numbers with 'digitNumber' digits. 
void random_generator(char* number, int digitNumber) {
    char digits[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e'};
    bool used[15] = {false}; // Represents if a digit is used or not
    int i = 0;
    int d;

    while(i < digitNumber) {
        if(i==0) d = rand() % 15 + 1;      // Creating a digit between 1-15 for first digit of number.
        else d = rand() % 15;                       // Creating other digits between 0-15.
        if( used[d] ) continue;                     
        used[d] = true;
        number[i] = digits[d];                 // generating the number step by step.
        i++;
    }
    
    number[digitNumber] = '\0'; // Null-terminate the string
}

// Used for checking if array contains unique elements or not.
bool isUnique(const char* arr) {
    for(int i=0; i<strlen(arr); i++) {
        for(int j=i+1; j<strlen(arr); j++) {
            if(arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

// This function checks if input is appropriate for the rules in documentation.
// Used for checking user input is valid or not.
bool isValidInput(const char* input) {
    // Check if the length of the input is valid
    if (strlen(input) >= 16) {
        return false;
    }

    // Check if the first character is not '0'
    if (input[0] == '0') {
        return false;
    }

    for (int i = 0; input[i] != '\0'; ++i) {
        char c = input[i];
        // If the character is not a valid digit (0-9 or a-e), return false
        if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'e')) {
            return false;
        }
    }

    if(!isUnique(input)) {
        return false;
    }

    return true;
}

// This function checks argv[2] if it is valid or not for program.
bool checkArg(const char* arg) {
    
    if(strlen(arg) > 2) {
        return false;
    }

    if(strlen(arg) == 1) {
        if(!(arg[0] > '0' && arg[0] <='9')) {
            return false;
        }
    }
    else if (strlen(arg) == 2) {
        if(!(arg[0] == '1' && (arg[1] >= '0' && arg[1] <= '5'))) {
            return false;
        }
    }

    return true;
}

// I wrote a simple atoi() function
// This function gets the number out of a char array.
// For example array is "12" then res will be 12.
int myAtoi(char* str)
{
	// Initialize result
	int res = 0;

	// Iterate through all characters and calculate integer value
	for (int i = 0; str[i] != '\0'; ++i)
		res = res * 10 + str[i] - '0';

	return res;
}

// This function performs the game.
// inputs of this function are coming from program call.
void mastermind(int argc, char **argv)
{
    // Declaring variables.

    // I have implemented the same code using dynamic memory allocation for secretNumber variable.
    // But I took them in comments since I do not know if we are allowed to use new[] and delete[].
    // Current program uses partially filled array.

    // char* secretNumber   /* related to dynamic version */

    const int MAX_SIZE = 20; // To control size of userInput and secretNumber variables.
    char secretNumber[MAX_SIZE];
    int countExact = 0;
    int countMisplaced = 0;
    int i=0, j=0;
    int lapCount=0;
    int flag = 1;           // used for ending loop at appropriate condition.
    char userInput[MAX_SIZE];     // used for reading input as char array with cin.
    
    // Checking if parameters are missing or not from program call.
    // If so prints E0 and exits.
    if(argc!=3)
    {
        cout << "E0\n";
        exit(1);
    }
    // Checking if parameters are valid or not from program call.
    // If they are valid, then program generates the appropriate secretNumber.
    // If they are not valid, prints E0 and exits.
    if(argv[1][1]=='r' && argv[1][0]=='-' && strlen(argv[1])==2 && checkArg(argv[2]))
    {
        //secretNumber = new char[myAtoi(argv[2]) + 1];    /* related to dynamic version */

        random_generator(secretNumber, myAtoi(argv[2]));    // creaating secretNumber randomly with respect to
                                                            // digit number from program call

        //cout << "Number is : " << secretNumber << endl;  /* for debugging purposes */
    }
    else if(argv[1][1]=='u' && argv[1][0]=='-' && strlen(argv[1])==2 && isValidInput(argv[2]))
    {
        //secretNumber = new char[strlen(argv[2]) + 1];    /* related to dynamic version */

        strcpy(secretNumber, argv[2]);  // creating secretNumber from program call

        //cout << "Number is : " << secretNumber << endl;  /* for debugging purposes */
    }
    else
    {
        cout << "E0\n";
        exit(1);
    }

    // Used do-while loop to keep game continue.
    do
    {
        cin >> userInput;

        // Checking if user input is a valid one.
        // If not prints E2 and exits.
        if(!isValidInput(userInput))
        {
            cout <<"E2\n";
            exit(1);
        }

        // Checking if the number of digits of the secret number
        // and the number entered by the user are the same.
        // If not prints E1 and exits.
        if(strlen(userInput) != strlen(secretNumber))
        {
            cout << "E1\n";
            exit(1);
        }

        // Calculating count of numbers in exact place and misplaced at each iteration.
        countExact = 0;
        countMisplaced = 0;
        for(i=0; i<strlen(userInput); i++)
        {
            if(userInput[i]==secretNumber[i]) countExact++;
            for(j=0; j<strlen(secretNumber); j++)
            {
                if(userInput[i]==secretNumber[j]) countMisplaced++;
            }
        }
        countMisplaced = countMisplaced - countExact;
        cout << countExact << " " << countMisplaced << endl;

        lapCount++;     // Incrementing lap count at each loop.

        // Prints appropriate message on screen if user finds the secret number.
        if(countExact == strlen(secretNumber))
        {
            flag = 0;
            cout << "FOUND " << lapCount << endl;
        }
        // Prints appropriate message on screen if user can not find 
        // the secret number in 100 turns.
        if(lapCount == 100)
        {
            flag = 0;
            cout << "FAILED" << endl;
        }
    } while (flag);
    
    //delete[] secretNumber;     /* related to dynamic version */

}

int main(int argc, char *argv[])
{
    //Function calls.
    srand(time(NULL));
    mastermind(argc, argv);

    return 0;
}

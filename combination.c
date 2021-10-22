// Sir when you will create a file please add an extra empty line at the end of inputs
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void powerSet(int *numbers, char *letters, int setSize, bool isChar, bool isDigit, FILE *out) // declaring function to calculate the power set
{
    int powerSetSize = pow(2, setSize); //calculating the number of elements in the power set

    printf("[");
    fprintf(out, "[");

    for (int mask = 0; mask < powerSetSize; mask++)
    {
        printf("[");
        fprintf(out, "[");

        bool flag = false;

        for (int i = 0; i < setSize; i++)
        {
            if (mask & (1 << i))
            {
                if (flag)
                {
                    printf(", ");
                    fprintf(out, ", ");
                }

                if (isChar) //if set contains alphabets
                {
                    printf("'%c'", letters[i]); //printing the elements enclosed in a single inverted commas
                    fprintf(out, "'%c'", letters[i]);
                }
                else
                {
                    printf("%d", numbers[i]); //printing the elements enclosed in a single inverted commas
                    fprintf(out, "%d", numbers[i]);
                }

                flag = true;
            }
        }

        if (mask == powerSetSize - 1)
        {
            printf("]");
            fprintf(out, "]");
        }
        else
        {
            printf("], ");
            fprintf(out, "], ");
        }
    }

    printf("]\n");
    fprintf(out, "]\n");
}

void printError(FILE *out) // function to display the error msg
{
    printf("Error, input is not in correct format. Use [] with elements separated by , . E.g., [1, 2, 3]\n"); // printing the error msg on screen
    fprintf(out, "%s", "Error, input is not in correct format. Use [] with elements separated by , . E.g., [1, 2, 3]\n"); // printing the error msg in output file
}

int main()
{
    FILE *in = fopen("input.txt", "r");   // open input file in read mode as input.txt file already present
    FILE *out = fopen("output.txt", "w"); // open output file in write mode

    if (in == NULL) //showing error msg if input.txt file does not exist
    {   
        printf("Error! Could not open file\n");
        exit(-1);
    } 

    char input[50]; // declaring char input to read line by line from the file 

    char letters[7]; // declaring char letters to store alphabets 
    int numbers[7],count=0; // declaring char number to store digits

    int cntnum, cntcomma, cntletters;

    fgets(input, 50, in); // reading from the file 'in' and storing in input

    while (!feof(in)) // loop untill the end of file is not reached
    {
        cntnum = 0, cntcomma = 0, cntletters = 0;
        if (input[0] != '[' || (input[strlen(input) - 3] != ']' && input[strlen(input) - 2] != ']')) //checking if 1st character is '[' and last is ']' if not then printing error
        {
            printError(out);
            goto jump;
        }

        for (int i = 0; i < strlen(input) - 1; i++)
        {
            if (input[i] == '-') //checking if input character is minus sign
            {
                if (!isdigit(input[i + 1])||(input[i + 1]>'8'))//checking if the input character is a number if previous input character was minus sign
                {
                    printError(out);
                    goto jump;
                }

                numbers[cntnum++] = -1 * (input[i + 1] - '0');//storing that character in numbers array
                i++;
            }
            else if (isalpha(input[i]))// checking if character is alphabet or not
                letters[cntletters++] = input[i];
            else if (isdigit(input[i])&&(input[i]<='8'))// checking if character is positive number or not
                numbers[cntnum++] = input[i] - '0';
            else if (input[i] == ',')// checking if a character is a comma or not
                cntcomma++;
        }

        if (cntnum != 0 && cntletters == 0 && cntcomma == cntnum - 1)
            powerSet(numbers, letters, cntnum, false, true, out);// finding the power set if the input has only numbers
        else if (cntletters != 0 && cntnum == 0 && cntcomma == cntletters - 1)
            powerSet(numbers, letters, cntletters, true, false, out);// finding the power set if the input has only alphabets
        else
            printError(out);

    jump:
        fgets(input, 50, in);
    }

    fclose(in); //closing the file opened in read mode
    fclose(out); //closing the file opened in write mode

    return 0;
}

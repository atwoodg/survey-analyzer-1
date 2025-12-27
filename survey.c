//Gabriel Atwood
//V00985797
//October 6th, 2025

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 50
#define MAX_CHARS 2000

//struct to hold strings and the number of strings in the 2D array
typedef struct {
    char array[MAX_LINES][MAX_CHARS];
    int size;
} Strings;

//Function to determine the format of the output based on first line giving 0 or 1 combination
//Takes in full 2D array of input
//Returns integer based on formatting style collected: 1=(1,0); 2=(0,1); 3=(1,1)
int format(char lines[][MAX_CHARS]) {

    //Setting variables to tokenize by comma
    char delimiter[] = ",";
    char format[2];
    char *token = strtok(lines[0], delimiter);

    //putting integer values into own array spots and changing to ints
    format[0] = atoi(token);
    token = strtok(NULL, delimiter);
    format[1] = atoi(token);

    //Finding format
    if (format[0] == 1 && format[1] == 0) {
        return 1;
    } else if (format[0] == 0 && format[1] == 1) {
        return 2;
    } else {
        return 3;
    }
}

//Function to tokenize any line into 2D array using specified delimeter
//Takes in pointer to a string of text and delimeter to seperate the string
//Returns type Strings struct which is a 2D array of strings and its size (number of rows)
Strings tokenize(char *line, char delimeter[]) {
    Strings tokenized;
    tokenized.size = 0;
    char* token;

    //while loop building tokenized (2D array)
    token = strtok(line, delimeter);
    while (token != NULL) {
        while (*token == ' ') token++; //skipping leading spaces
        strcpy(tokenized.array[tokenized.size], token);
        token = strtok(NULL, delimeter);
        tokenized.size++;
    }

    return tokenized;
}

/*
  Function to fill 2D array with counts of responses (columns) to each question (rows)
  Takes in responses (Strings struct type of all responses [columns] to each question [rows])
  and questions (Strings struct type of questions as strings)
  and options (Strings struct type of possible options respondents can choose when answering)
  and proportions(2d array to be filled with count of option selections to each question)
*/
void proportions(Strings responses, Strings questions, Strings options, int proportions[questions.size][options.size]) {

    //Filling prop with 0's
    for (int i = 0; i < questions.size; i++) {
        for (int j = 0; j < options.size; j++) {
            proportions[i][j] = 0;
        }
    }

    for (int j = 0; j < responses.size; j++) { //Outer loops through all responses and tokenizes them into struct
        Strings ops = tokenize(responses.array[j], ",");

        for (int k = 0; k < ops.size; k++) { //Inner loops through each individual response in question j
            for (int i = 0; i < options.size; i++) {
                if (strcmp(ops.array[k], options.array[i]) == 0) {//Comparing answer options to respondents answer to increment array of proportions in correct spot
                    proportions[k][i] += 1;
                }
            }
        }
    }
}

//Function to calculate the average response of each question using scale 1-4 and fill array
//Takes in same parameters as proportions, except extra array to be filled
void averages(Strings responses, Strings questions, Strings options, int proportions[questions.size][options.size], double avgs[questions.size][1]) {

    for (int q = 0; q < questions.size; q++) {//Looping through survey questions
        avgs[q][0] = 0;
        int total = 0;


        for (int i = 0; i < options.size; i++) {
            avgs[q][0] += proportions[q][i]*(i+1); //For question q, multiplying each answer option in proportions by scale number and adding to vote total
            total += proportions[q][i]; //Adding actual question total (not using scale) for calculation
        }
        avgs[q][0] = avgs[q][0]/(total); //Calculating average for each question by dividing scaled version by unscaled (number of respondents)
    }
}

//Function to print basic survey header
//Takes in Strings struct responses to print (in case number of respondents changes)
void outputInfo(Strings responses) {

    printf("ECS Student Survey\n");
    printf("SURVEY RESPONSE STATISTICS\n\n");
    printf("NUMBER OF RESPONDENTS: %d\n\n", responses.size);

}

//Function to print (1,0) survey information format
//Takes in Strings struct type to access all necessary strings and survey values
void output10(Strings responses, Strings questions, Strings options, int props[questions.size][options.size]) {

    printf("#####\n");
    printf("FOR EACH QUESTION/ASSERTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");

    for (int q = 0; q < questions.size; q++) { //Loop through questions to print questions with its number
        printf("%d. %s\n", q + 1, questions.array[q]);
        for (int o = 0; o < options.size; o++) { //Loop through array of proportions to show answer distribution
            printf("%d.00: %s\n", props[q][o]*10, options.array[o]);
        }
        if (q < questions.size - 1) {printf("\n");} //Correcting newlines to match 
    }
}

//Function to print survey information format (0,1)
//Takes in Strings struct type to access all necessary strings and survey values
void output01(Strings responses, Strings questions, Strings options, int props[questions.size][options.size]) {
    double avgs[questions.size][1];
    averages(responses, questions, options, props, avgs); //Uses averages function for correct output

    printf("#####\n");
    printf("FOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT)\n\n");

    for (int q = 0; q < questions.size; q++) { //Loops through questions and averages to print (same indexes)
        printf("%d. %s - %.2f\n", q + 1, questions.array[q], avgs[q][0]);
    }
}

//Main function
int main() {

    //Inititalizing buffer for max strings
    char buffer[MAX_CHARS];
    char lines[MAX_LINES][MAX_CHARS];
    int i = 0;

    //while loop that gets each line in file and checks if it is a comment, if not, it adds it to the 2D array
    while (fgets(buffer, MAX_CHARS, stdin) != NULL) {
        if (buffer[0] != '#') {
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(lines[i], buffer);
            i += 1;
        }
    }

    //Format of output
    int output = format(lines);

    //Reading in questions/assertions
    Strings questions = tokenize(lines[1], ";");
    Strings options = tokenize(lines[2], ",");

    Strings responses;
    responses.size = 0;
    for (int i = 3; i < 13; i++) {
        strcpy(responses.array[responses.size++], lines[i]);
    }

    int props[questions.size][options.size];
    proportions(responses, questions, options, props);

    //Output
    if (output == 1) {
        outputInfo(responses);
        output10(responses, questions, options, props);
    }
    if (output == 2) {
        outputInfo(responses);
        output01(responses, questions, options, props);
    }
    if (output == 3) {
        outputInfo(responses);
        output10(responses, questions, options, props);
        printf("\n");
        output01(responses, questions, options, props);
    }

    return 0;
}

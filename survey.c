#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function to determine the format of the output based on first line giving 0 or 1 combination
int format(char lines[][500]) {

    //Setting variables to tokenize by comma
    int fmt;
    char delimiter[] = ",";
    char format[2];
    char *token = strtok(lines[0], delimiter);

    //putting integer values into own array spots
    format[0] = atoi(token);
    token = strtok(NULL, delimiter);
    format[1] = atoi(token);

    //Finding format
    if (format[0] == 0 && format[1] == 0) {
        return 1;
    } else if (format[0] == 1 && format[1] == 0) {
        return 2;
    } else if (format[0] == 0 && format[1] == 1) {
        return 3;
    } else if (format[0] == 1 && format[1] == 1) {
        return 4;
    }
}

int main() {

    char buffer[1000];
    char lines[30][1000];
    int i = 0;

    //Takes input line by line, checks for comments, and adds to array
    while (fgets(buffer, 1000, stdin) != NULL) {
        if (buffer[0] != '#') {
            strcpy(lines[i], buffer);
            i += 1;

        }
    }


    for (int j = 0; j < i; j++) {
        printf("%s", lines[j]);
    }

    return 0;



}

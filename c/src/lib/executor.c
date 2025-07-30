#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int RESULT_SIZE = 0xFFF;

char* execute(char command[]) {

    //allocate
    char* result = malloc(RESULT_SIZE); // Allocate memory for the result


    //run command
    //https://stackoverflow.com/questions/646241/c-run-a-system-command-and-get-output
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL){
        perror("failed to run command");
        strncpy(result,"failed to run command", RESULT_SIZE-1);
        return result;
    }
    while(fgets(result, RESULT_SIZE, fp) != NULL) {
        printf("%s", result);
    }

    pclose(fp);

    return result;
}


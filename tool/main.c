#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define NUM_OF_ARGUMENTS 4

#define FLAG 1
#define SOURCE 2
#define TARGET 3

#define ERROR 1

char invert(char c);

int main(int argc, char **argv) {
    if (argc != NUM_OF_ARGUMENTS) {
        return ERROR;
    }

    char* flag = argv[FLAG];

    // If flag is not -e and not -i return error
    if (strcmp(flag, "-e") != 0 && strcmp(flag, "-i") != 0){  // 0 is the return value if the strings are equal
        return ERROR;
    }

    // Read the source file:
    char* source = argv[SOURCE];
    FILE* sourceFile = fopen(source, "r");
    if (sourceFile == NULL) {  // File does not exist
        return ERROR;
    }
    RLEList list = asciiArtRead(sourceFile);
    fclose(sourceFile);

    // Write to target file:
    char* target = argv[TARGET];
    FILE* targetFile = fopen(target, "w");
    if (strcmp(flag, "-e") == 0){
        asciiArtPrintEncoded(list, targetFile);
    } else {  // flag is -i
        RLEListMap(list, invert);
        asciiArtPrint(list, targetFile);
    }
    fclose(targetFile);

    // Clear memory:
    RLEListDestroy(list);

    return 0;
}

char invert(char c){
    if(c == ' ')
        return '@';
    if(c == '@')
        return ' ';

    return c;
}
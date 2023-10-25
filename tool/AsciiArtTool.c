#include <stdlib.h>
#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* in_stream) {
    RLEList list = RLEListCreate();
    char currentChar;
    while(1 == fscanf(in_stream, "%c", &currentChar)){
        RLEListAppend(list, currentChar);
    }

    return list;
}

// Assuming the user opens out_stream with valid permissions and closes afterwards
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size = RLEListSize(list);
    RLEListResult result;

    for (int i = 0; i < size; ++i) {
        char currentChar = RLEListGet(list, i, &result);
        if (fputc(currentChar, out_stream) == EOF){
            return RLE_LIST_ERROR;
        }
    }

    return result;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;

    char* encodedList = RLEListExportToString(list, &result);
    if (fputs(encodedList, out_stream) == EOF) {
        return RLE_LIST_ERROR;
    }
    free(encodedList);

    return result;
}

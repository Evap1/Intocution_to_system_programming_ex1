#include <malloc.h>

#include "RLEList.h"

struct RLEList_t{
    char character;
    int count;
    RLEList next;
};

//implement the functions here
RLEList RLEListCreate(){
    RLEList newList = malloc(sizeof (*newList));
    if (newList == NULL) {
        return NULL;
    }
    newList->character = 0;
    newList->count = 0;
    newList->next = NULL;
    return newList;
}

void RLEListDestroy(RLEList list){
    if (list == NULL) {
        return;
    }

    // Destroy the next node, then free the current:
    RLEListDestroy(list->next);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value){
    if (list == NULL || !value){
        return RLE_LIST_NULL_ARGUMENT;
    }

    // Go to the end of the list:
    while(list->next != NULL) {
        list = list->next;
    }

    // If character of last node is value, just increase the count:
    if(list->character == value){
        list->count++;
        return RLE_LIST_SUCCESS;
    }

    // If not, create another node with count 1:
    list->next = RLEListCreate();
    if (list->next == NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    list->next->character = value;
    list->next->count = 1;

    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list){
    if (list == NULL) {
        return -1;
    }

    int count = 0;

    while(list != NULL) {
        count += list->count;
        list = list->next;
    }

    return count;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index < 0 || index >= RLEListSize(list)){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int count = 0;
    // Go to the node previous to the relevant one:
    while(list->next != NULL && count + list->next->count <= index){
        list = list->next;
        count += list->count;
    }

    if (list->next->count == 1){
        // Remove the relevant node:
        RLEList temp = list->next->next;
        list->next->next = NULL;
        RLEListDestroy(list->next);
        list->next = temp;
    } else {
        list->next->count--;
    }

    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if (list == NULL){
        if (result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if (index < 0 || index >= RLEListSize(list)){
        if (result != NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }

    int count = 0;
    // Go to the node previous to the relevant one:
    while(list->next != NULL && count + list->next->count <= index){
        list = list->next;
        count += list->count;
    }

    if (result != NULL) {
        *result = RLE_LIST_SUCCESS;
    }
    return list->next->character;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list != NULL){
        list->character = map_function(list->character);
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}

// CAUTION: User of the function must free the string after use
char* RLEListExportToString(RLEList list, RLEListResult* result){
    if (result == NULL){
        return NULL;
    }
    if (list == NULL){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int nodesCount = 0;
    RLEList tempList = list->next; // Skip the dummy node;
    while(tempList != NULL){
        nodesCount++;
        tempList = tempList->next;
    }

    int* digitCounts = calloc(nodesCount, sizeof(int));
    if(digitCounts == NULL){
        *result = RLE_LIST_ERROR;
        return NULL;
    }

    tempList = list->next; // Skip the dummy node;
    int i = 0, digitCount = 0;
    while(tempList != NULL){
        for (int n = tempList->count; n > 0; n /= 10) {
            digitCounts[i]++;
        }
        digitCount += digitCounts[i];
        tempList = tempList->next;
        i++;
    }

    const int CHARS_PER_NODE = 2;
    char* string = malloc(CHARS_PER_NODE * nodesCount + nodesCount + 1);
    if(string == NULL){
        *result = RLE_LIST_ERROR;
        return NULL;
    }

    tempList = list->next; // Skip the dummy node;
    int strI = 0, nodesI = 0;
    while(tempList != NULL){
        string[strI] = tempList->character;
        strI++;

        int power = 1;
        for (int k = 0; k < digitCounts[nodesI]; ++k) {
            power *= 10;
        }
        for (int j = power; j > 1; j /= 10) {
            int currentDigit = (((tempList->count) % power) / (power / 10)) + '0';
            string[strI] = (char) currentDigit;
            strI++;
        }

        string[strI] = '\n';
        strI++;

        tempList = tempList->next;
        nodesI++;
    }
    string[strI] = '\0';

    free(digitCounts);
    *result = RLE_LIST_SUCCESS;
    return string;
}


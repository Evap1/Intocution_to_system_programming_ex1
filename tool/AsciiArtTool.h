
#ifndef EX1_ASCIIARTTOOL_H
#define EX1_ASCIIARTTOOL_H

#include "RLEList.h"


/**
* Ascii Art Tool
*
* Implements a tool for working with ascii art files and encoding them.
*
* The following functions are available:
*   asciiArtRead	        - Reads an ascii art file to a RLEList.
*   asciiArtPrint		    - Prints a RLEList of ascii art to a file.
*   asciiArtPrintEncoded    - Prints a RLEList of ascii art to a file in encoded format.
*/


/**
* asciiArtRead: Reads an ascii art file to a RLEList.
*
* The function reads an input file of ascii art and saves it as a RLEList.
* Note that the user must provide an open file and close it afterwards.
*
* @param in_stream - The input file
*
* @return
* 	A new RLEList containing the ascii art.
*/
RLEList asciiArtRead(FILE* in_stream);

/**
* asciiArtPrint: Prints a RLEList of ascii art to a file.
*
* The function prints the provided ascii art list to an output file.
* Note that the user must provide an open file and close it afterwards.
*
* @param list - The ascii art list
* @param out_stream - The output file
*
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_ERROR if an error occurred
* 	RLE_LIST_SUCCESS if the list has been printed successfully
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
* asciiArtPrintEncoded: Prints a RLEList of ascii art to a file in encoded format.
*
* The function prints the provided ascii art list to an output file in encoded format.
* Note that the user must provide an open file and close it afterwards.
*
* @param list - The ascii art list
* @param out_stream - The output file
*
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_ERROR if an error occurred
* 	RLE_LIST_SUCCESS if the list has been printed successfully
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //EX1_ASCIIARTTOOL_H

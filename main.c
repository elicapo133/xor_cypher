#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "xor.h"

int main(int argc, char** argv)
{
    char input_file_name[256];
    char* output_file_name = malloc(256); // This is a pointer because there's a case where we need it to be null
    char key[256];
    
    if (argc < 3 || argc > 4)
    {
        printf("Usage: %s <input_file> [output_file] <key>\n", argv[0]);
        printf("In case no output file is provided, input file will be used as output.\n");

        free(output_file_name);

        return 0;
    }
    else if (argc == 3)
    {
        strcpy(input_file_name, argv[1]);
        strcpy(key, argv[2]);
        output_file_name = NULL;
   
        printf("---- XOR CIPHER ----\n");
        printf("[En|De]crypting file '%s' with key '%s'.\n\n", input_file_name, key);
    }
    else if (argc == 4)
    {
        strcpy(input_file_name, argv[1]);
        strcpy(output_file_name, argv[2]);
        strcpy(key, argv[3]);
   
        printf("---- XOR CIPHER ----\n");
        printf("[En|De]crypting file '%s' with key '%s', writing to file '%s'.\n\n", input_file_name, key, output_file_name);
    }


    if (encrypt_file(input_file_name, output_file_name, key, strlen(key))) printf("File encrypted succesfully.\n");
    else printf("Something went wrong :/.\n");

    free(output_file_name);

    return 0;
}



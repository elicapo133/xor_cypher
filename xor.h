#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void _xor(void* input, size_t input_size, void* key, size_t key_size, void* output);
bool encrypt_file(const char* input_filename, const char* output_filename, void* key, const size_t key_size);

// Xor files. If output is NULL, output will be directed to input file
bool encrypt_file(const char* input_filename, const char* output_filename, void* key, const size_t key_size)
{
    void* buffer;
    FILE* input_file = fopen(input_filename, "rb");
    FILE* output_file;

    if (input_file == NULL) return false;

    fseek(input_file, 0, SEEK_END);
    size_t input_file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    buffer = malloc(input_file_size);
    fread(buffer, input_file_size, 1, input_file);
    fclose(input_file);

    // This check is done here so that we can safely open the same file again in case input and output files are actually the same
    if (output_filename == NULL) output_file = fopen(input_filename, "wb");
    else output_file = fopen(output_filename, "wb");

    _xor(buffer, input_file_size, key, key_size, buffer);
    fwrite(buffer, input_file_size, 1, output_file);
    fclose(output_file);

    free(buffer);

    return true;
}

// Main function for xoring
void _xor(void* input, size_t input_size, void* key, size_t key_size, void* output)
{
    // We use a buffer in case input or key use the same pointer as the output... which may cause errors
    void* buffer = malloc(input_size);

    for (int i = 0; i < input_size; i++)
        *((uint8_t*) buffer + i) = *((uint8_t*) input + i) ^ *((uint8_t*) key + (i % key_size));

    memcpy(output, buffer, input_size);
    free(buffer);
    
    return;
}


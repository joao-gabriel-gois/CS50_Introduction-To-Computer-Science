#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 1) Prmitive boolean support
typedef uint8_t bool;
const bool false = 0;
const bool true = 1;

// 2) Actual Data Types
typedef uint8_t BYTE;
const int CHUNK_SIZE = 512 * sizeof(BYTE);

// 3) Main Logic Prototype
void get_images_from_input(FILE *input);


// 4) Entry Point
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./recover input.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    get_images_from_input(input);
    return 0;
}


// 5) Main Logic Details
void get_images_from_input(FILE *input)
{
    BYTE chunk[CHUNK_SIZE];
    FILE *output;
    char *filename;
    bool is_writting = false;
    int n = 0;

    while (fread(&chunk, CHUNK_SIZE, 1, input))
    {
        // CHECK IF IT IS A JPG HEADER
        if (chunk[0] == 0xFF && chunk[1] == 0xD8 && chunk[2] == 0xFF && (chunk[3] & 0xF0) == 0xE0)
        {
            // set incremental filename (for different imgs)
            if (is_writting)
            {
                fclose(output);
                free(filename);
                is_writting = false;
                n++;
            }

            filename = malloc(sizeof("000.jpg"));
            sprintf(filename, "%03i.jpg", n);

            output = fopen(filename, "w");
            fwrite(&chunk, CHUNK_SIZE, 1, output);
            is_writting = true;
        }

        else if (is_writting)
        {
            fwrite(&chunk, CHUNK_SIZE, 1, output);
        }
    }

    // for good practice, in case it would be a persistant state
    is_writting = false;

    free(filename);
    fclose(input);
    fclose(output);
}

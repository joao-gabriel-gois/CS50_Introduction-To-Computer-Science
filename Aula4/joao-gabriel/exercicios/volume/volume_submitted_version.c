// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;
typedef int16_t sample;
// Number of bytes in .wav header
const int HEADER_SIZE = 44;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copying header from input file to output file
    byte header[HEADER_SIZE];
    fread(&header, HEADER_SIZE, 1, input);
    fwrite(&header, HEADER_SIZE, 1, output);

    // Writing altered sample just after read one by oneS
    sample buffer;
    while (fread(&buffer, sizeof(sample), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(sample), 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;
typedef int16_t sample;

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

    // Writting Header
    byte header[HEADER_SIZE];
    fread(&header, HEADER_SIZE, 1, input);
    fwrite(&header, HEADER_SIZE, 1, output);

    // Getting the final position of file to get its size
    //   then calculating only body size and setting file back
    //   to header position
    fseek(input, 0, SEEK_END);
    int f_total_size = ftell(input);
    int f_body_size = f_total_size - HEADER_SIZE;
    fseek(input, HEADER_SIZE, SEEK_SET);

    // Setting buffer array, iterating through it, reading
    //    current sample from input and then adding it to
    //    buffer array after applying the scale factor
    //    after it, finally closing input file
    sample buffer[f_body_size / 2];
    for (int i = 0; i < f_body_size / 2; i++)
    {
        fread(&buffer[i], sizeof(sample), 1, input);
        buffer[i] *= factor;
    }
    fclose(input);

    // Writting from buffer to output file and then closing it
    fwrite(&buffer, f_body_size, 1, output);
    fclose(output);

    return 0;
}

// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;
typedef uint16_t sample;
// Number of bytes in .wav header
const int HEADER_SIZE = 44;
const sample SAMPLE_MAX_SIZE = 255 * 256 + 255;

sample get_float_mult(sample ith, float factor);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4) {
      printf("Usage: ./volume input.wav output.wav factor\n");
      return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
      printf("Could not open file.\n");
      return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
      printf("Could not open file.\n");
      return 1;
    }

    float factor = atof(argv[3]);

    // Copying header from input file to output file
    fseek(input, 0, SEEK_END);
    long int file_size = ftell(input);
    long int file_body_size = file_size - HEADER_SIZE;
    fseek(input, 0, SEEK_SET);
    
    // i. saving header
    byte* header = malloc(sizeof(byte) * HEADER_SIZE);
    fread(header, sizeof(byte), HEADER_SIZE, input);
    fwrite(header, sizeof(byte), HEADER_SIZE, output);
    //free(header);

    sample* samples = malloc(sizeof(byte) * file_body_size);
    fseek(input, HEADER_SIZE - 1, SEEK_SET);
    // iii.c) then read from that point on and save samples
    fread(samples, sizeof(sample), file_body_size / 2, input);

    //fseek(input, HEADER_SIZE, SEEK_SET);
    fseek(output, HEADER_SIZE - 1, SEEK_SET);
  
    int i = 0;
    while (i < file_body_size) {
      if (i % 2 == 0) {     
        int current_sample_index = i / 2;


        long int result = ((float) 10 * factor * (float) samples[current_sample_index]) / 10;
        sample final_result = result;
        // samplelized_bytes_pair = (unsigned) samplelized_bytes_pair * (unsigned) factor > SAMPLE_MAX_SIZE
        //   ? SAMPLE_MAX_SIZE
        //   : (unsigned) samplelized_bytes_pair * factor;
        // sample s2 = (sample) first_number * 256 + second_number;
// printf("first byte: %i, second byte: %i. samplelized1: %i, samplelized2: %i\n", first_number, second_number, samplelized_bytes_pair, s2);
        
        // int result =   samplelized_bytes_pair; // > SAMPLE_MAX_SIZE
        //     ? samplelized_bytes_pair
        //     : (float) (factor * samplelized_bytes_pair);


        fwrite(&final_result, sizeof(sample), 1, output);
      }
      i++;
    }
    
    // then finally writing modified samples
    
    // printf("Current 'output' position: %li\n\n", ftell(output));

    // Close files
    fclose(input);
    fclose(output);
    //Free heap
    // free(header);
    //free(samples);

    return 0;
}

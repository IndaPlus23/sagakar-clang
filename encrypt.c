#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int hash(unsigned char *str);

int main(int argc, char const *argv[])
{
    // Parse arguments
    if(argc < 3 || argc > 4) {
        printf("Error: incorrect number of arguments\n");
        printf("Usage: %s [-d] <filename> <key>\n", argv[0]);
        return 1;
    }
    int arg_index = 1;
    int decrypting = 0;
    if(argc == 4) {
        arg_index ++;
        if(!strcmp(argv[1],"-d")) {
            decrypting = 1;
        }
    }
    const char* file_name_in = argv[arg_index];
    char key[100];
    strcpy(key, argv[arg_index + 1]);

    // Ensure name of input file is < 100 characters
    if (strlen(file_name_in) > 100) {
        printf("Error: input filename too long\n");
        printf("Maximum length is 100 characters\n");
        return 2;
    }
    
    // Ensure seed is within [5, 100]
    if ((strlen(key) < 5) || (strlen(key) > 100)) {
        printf("Error: invalid key length\n");
        printf("Key length must be within [5, 100]\n");
        return 3;
    }

    // Open input file
    FILE *infile = fopen(file_name_in, "r");
    if (infile == NULL) {
        printf("Error: could not open input file");
        return 4;
    }

    // Open output file with correct prefix
    char file_name_out[110];
    if (decrypting) {
        strcpy(file_name_out, "decrypted_");
    }
    else {
        strcpy(file_name_out, "encrypted_");
    }
    strcat(file_name_out, file_name_in);
    FILE *outfile = fopen(file_name_out, "w+");
    if (outfile == NULL) {
        printf("Error: could not open output file");
        return 5;
    }

    // Seed the PRNG
    srand(hash(key));

    // Read the input file and XOR every byte with a pseudorandom byte
    char read_buffer[100];
    char write_buffer[100];
    while (fgets(read_buffer, 100, infile)) {
        for (int i = 0; i < strlen(read_buffer); i++) {
            char random_byte = (char)rand();
            write_buffer[i] = read_buffer[i] ^ random_byte;
        }
        write_buffer[strlen(read_buffer)] = '\0';
        fputs(write_buffer, outfile);
    }
    fflush(outfile);

    return 0;
}

// Hashes a string using the djb2 algorithm
// Originally invented by Daniel J. Bernstein in 1991
// Cited from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(unsigned char *str) {
        int hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
}

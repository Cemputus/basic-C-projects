#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_FILE_NAME 100
#define MAX_BUFFER_SIZE 1000
#define ENCRYPTION_KEY 5

// Function to encrypt a file
void encryptFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile, *outputFile;
    char ch; 

    // Open the input file for reading
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    // Open the output file for writing
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return;
    }

    // Encrypt each character and write to the output file
    while ((ch = fgetc(inputFile)) != EOF) {
        ch = ch + ENCRYPTION_KEY;
        fputc(ch, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("File encrypted successfully.\n");
}

// Function to decrypt a file
void decryptFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile, *outputFile;
    char ch;

    // Open the input file for reading
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    // Open the output file for writing
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return;
    }

    // Decrypt each character and write to the output file
    while ((ch = fgetc(inputFile)) != EOF) {
        ch = ch - ENCRYPTION_KEY;
        fputc(ch, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("File decrypted successfully.\n");
}

int main() {
    char inputFileName[MAX_FILE_NAME];
    char outputFileName[MAX_FILE_NAME];
    int choice;

    do {
        printf("\nFile Encryption/Decryption Tool\n");
        printf("1. Encrypt a file\n");
        printf("2. Decrypt a file\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the file to encrypt: ");
                scanf("%s", inputFileName);
                printf("Enter the name of the encrypted file: ");
                scanf("%s", outputFileName);
                encryptFile(inputFileName, outputFileName);
                break;
            case 2:
                printf("Enter the name of the file to decrypt: ");
                scanf("%s", inputFileName);
                printf("Enter the name of the decrypted file: ");
                scanf("%s", outputFileName);
                decryptFile(inputFileName, outputFileName);
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void receiveFile(int clientSocket, const char *fileName) {
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Open or create the file for writing
    file = fopen(fileName, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Receive file content
    while (recv(clientSocket, buffer, sizeof(buffer), 0) > 0) {
        fwrite(buffer, 1, sizeof(buffer), file);
    }

    fclose(file);
    printf("File received successfully.\n");
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char fileName[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server on port %d.\n", PORT);

    // Get the file name from the user
    printf("Enter the file name to receive: ");
    scanf("%s", fileName);

    // Send the file name to the server
    send(clientSocket, fileName, sizeof(fileName), 0);

    // Receive the server's response
    recv(clientSocket, fileName, sizeof(fileName), 0);

    if (strcmp(fileName, "FileNotFound") == 0) {
        printf("File not found on the server.\n");
    } else if (strcmp(fileName, "FileFound") == 0) {
        // Receive the file
        receiveFile(clientSocket, fileName);
    }

    close(clientSocket);

    return 0;
}

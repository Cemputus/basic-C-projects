#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Receive file name
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    file = fopen(buffer, "rb");

    if (file == NULL) {
        perror("File not found");
        send(clientSocket, "FileNotFound", sizeof("FileNotFound"), 0);
    } else {
        send(clientSocket, "FileFound", sizeof("FileFound"), 0);

        // Send file content
        while (fread(buffer, 1, sizeof(buffer), file) > 0) {
            send(clientSocket, buffer, sizeof(buffer), 0);
        }

        fclose(file);
        printf("File sent successfully.\n");
    }

    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a connection
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        // Handle client in a separate function
        handleClient(clientSocket);
    }

    close(serverSocket);

    return 0;
}

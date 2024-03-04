#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void *receiveMessages(void *arg) {
    int clientSocket = *((int *)arg);
    char buffer[BUFFER_SIZE];

    // Receive and display messages
    while (recv(clientSocket, buffer, sizeof(buffer), 0) > 0) {
        if (strcmp(buffer, "AuthenticationSuccess") == 0) {
            printf("Authentication successful. You can start chatting.\n");
        } else if (strcmp(buffer, "AuthenticationFailed") == 0) {
            printf("Authentication failed. Please choose a different username.\n");
            exit(EXIT_FAILURE);
        } else if (strcmp(buffer, "InvalidCommand") == 0) {
            printf("Invalid command. Use /private <username> to send a private message.\n");
        } else {
            printf("%s\n", buffer);
        }
    }

    printf("Disconnected from the server.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

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

    printf("Connected to the server on port %d.\n", PORT);

    // Send the client's username to the server
    char username[50];
    printf("Enter your username: ");
    scanf("%s", username);
    send(clientSocket, username, sizeof(username), 0);

    // Receive the server's response
    char response[BUFFER_SIZE];
    recv(clientSocket, response, sizeof(response), 0);

    if (strcmp(response, "AuthenticationSuccess") == 0) {
        printf("Authentication successful. You can start chatting.\n");
    } else if (strcmp(response, "AuthenticationFailed") == 0) {
        printf("Authentication failed. Please choose a different username.\n");
        exit(EXIT_FAILURE);
    }

    // Create a thread to receive messages
    pthread_t thread;
    pthread_create(&thread, NULL, receiveMessages, (void *)&clientSocket);

    // Send messages to the server
    char buffer[BUFFER_SIZE];
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);

        if (buffer[0] == '/') {
            // Handle commands
            char command[10];
            char recipient[50];

            sscanf(buffer, "%s %s", command, recipient);

            if (strcmp(command, "/private") == 0) {
                printf("Enter your private message: ");
                fgets(buffer, sizeof(buffer), stdin);

                char privateMessage[BUFFER_SIZE];
                snprintf(privateMessage, sizeof(privateMessage), "/private %s %s", recipient, buffer);
                send(clientSocket, privateMessage, strlen(privateMessage) + 1, 0);
            } else {
                printf("Invalid command. Use /private <username> to send a private message.\n");
            }
        } else {
            send(clientSocket, buffer, strlen(buffer) + 1, 0);
        }
    }

    close(clientSocket);

    return 0;
}

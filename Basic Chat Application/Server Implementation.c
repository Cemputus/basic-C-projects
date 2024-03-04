#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

// Structure to store client information
struct ClientInfo {
    int socket;
    char username[50];
};

struct ClientInfo clients[MAX_CLIENTS];
int numClients = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to broadcast a message to all clients except the sender
void broadcastMessage(char *message, char *senderUsername) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < numClients; i++) {
        if (strcmp(clients[i].username, senderUsername) != 0) {
            send(clients[i].socket, message, strlen(message) + 1, 0);
        }
    }

    pthread_mutex_unlock(&mutex);
}

// Function to handle private messages
void sendPrivateMessage(char *message, char *senderUsername, char *receiverUsername) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < numClients; i++) {
        if (strcmp(clients[i].username, receiverUsername) == 0) {
            send(clients[i].socket, message, strlen(message) + 1, 0);
            break;
        }
    }

    pthread_mutex_unlock(&mutex);
}

// Function to handle authentication
int authenticateClient(int clientSocket, char *username) {
    // Check if the username is already taken
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < numClients; i++) {
        if (strcmp(clients[i].username, username) == 0) {
            pthread_mutex_unlock(&mutex);
            return 0;  // Username already taken
        }
    }

    pthread_mutex_unlock(&mutex);

    // Send authentication success message to the client
    send(clientSocket, "AuthenticationSuccess", sizeof("AuthenticationSuccess"), 0);

    return 1;  // Authentication successful
}

void *handleClient(void *arg) {
    struct ClientInfo *clientInfo = (struct ClientInfo *)arg;
    int clientSocket = clientInfo->socket;

    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE + 50];

    // Receive and broadcast messages
    while (recv(clientSocket, buffer, sizeof(buffer), 0) > 0) {
        if (buffer[0] == '/') {
            // Handle commands
            char command[10];
            char recipient[50];

            sscanf(buffer, "%s %s", command, recipient);

            if (strcmp(command, "/private") == 0) {
                char privateMessage[BUFFER_SIZE];
                snprintf(privateMessage, sizeof(privateMessage), "[Private from %s]: %s", clientInfo->username, buffer + 9);
                sendPrivateMessage(privateMessage, clientInfo->username, recipient);
            } else {
                send(clientSocket, "InvalidCommand", sizeof("InvalidCommand"), 0);
            }
        } else {
            snprintf(message, sizeof(message), "[%s]: %s", clientInfo->username, buffer);
            broadcastMessage(message, clientInfo->username);
        }
    }

    // Remove the client when they disconnect
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < numClients; i++) {
        if (clients[i].socket == clientSocket) {
            printf("Client [%s] disconnected.\n", clients[i].username);

            // Shift remaining clients to fill the gap
            for (int j = i; j < numClients - 1; j++) {
                clients[j] = clients[j + 1];
            }

            numClients--;
            break;
        }
    }

    pthread_mutex_unlock(&mutex);
    close(clientSocket);
    free(clientInfo);

    return NULL;
}

int main() {
    int serverSocket;
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
    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a connection
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        // Receive the client's username
        char username[50];
        recv(clientSocket, username, sizeof(username), 0);

        // Authenticate the client
        if (!authenticateClient(clientSocket, username)) {
            send(clientSocket, "AuthenticationFailed", sizeof("AuthenticationFailed"), 0);
            close(clientSocket);
            continue;
        }

        printf("Connection accepted from %s:%d. Client [%s] connected.\n",
               inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), username);

        // Send authentication success message to the client
        send(clientSocket, "AuthenticationSuccess", sizeof("AuthenticationSuccess"), 0);

        // Create a new thread to handle the client
        pthread_t thread;
        struct ClientInfo *clientInfo = malloc(sizeof(struct ClientInfo));
        clientInfo->socket = clientSocket;
        strcpy(clientInfo->username, username);

        pthread_create(&thread, NULL, handleClient, (void *)clientInfo);
        pthread_detach(thread);

        // Add the client to the array
        pthread_mutex_lock(&mutex);
        clients[numClients++] = *clientInfo;
        pthread_mutex_unlock(&mutex);
    }

    close(serverSocket);

    return 0;
}

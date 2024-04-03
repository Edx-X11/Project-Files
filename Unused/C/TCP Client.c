#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char const* argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[BUFFER_SIZE] = {0};

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send multiple messages to the server
    for (int i = 0; i < 5; i++) {
        // Send message to server
        send(sock, hello, strlen(hello), 0);
        printf("Message sent to server: %s\n", hello);

        // Receive message from server
        valread = read(sock, buffer, BUFFER_SIZE);
        printf("Server response: %s\n", buffer);

        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Pause for a short time before sending the next message
        sleep(1);
    }

    // Close the socket
    close(sock);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;

    printf("Server listening on port %d...\n", port);
    bytes_received = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_address, &client_address_len);
    /*while (1) {
        bytes_received = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_address, &client_address_len);
        if (bytes_received == -1) {
            perror("Error receiving data");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Received from %s:%d: %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buffer);

        if (strcmp(buffer, "Shutdown receiver") == 0) {
            printf("Exit command received. Closing the server.\n");
            break;
        }
    }*/
    buffer[bytes_received] = '\0'; 
    printf("Received from %s:%d: %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buffer);

    close(server_socket);

    return 0;
}

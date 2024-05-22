#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 6511
#define SERVER_IP "172.31.196.71"
#define SERVER_PORT 6510

int main() {
    struct sockaddr_in client, server;
    int sd,slen=sizeof(server);
    char str[512], str1[512];

    // Zero out the structure
    bzero((char *)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);

    // Zero out the structure
    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("socket creation failed");
        return 1;
    }

    // Connect to server
    if (connect(sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connection failed");
        close(sd);
        return 1;
    }

    do {
        printf("Enter a message to send to the server: ");
        scanf("%s", str);
        send(sd, str, strlen(str) + 1, 0);
    
        // Receive message from server and store it in str1
        memset(str1,0,512);
        recv(sd,str1,512,0);
        printf("Received message from server again: %s\n", str1);
    } while (strcmp(str, "stop") != 0);

    close(sd);
    return 0;
}



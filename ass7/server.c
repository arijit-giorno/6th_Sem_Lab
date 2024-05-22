#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<time.h>

#define SERVER_IP "172.31.196.71"
#define SERVER_PORT 6510

int main() {
    struct sockaddr_in client, server;
    int sd, nsd, clen = sizeof(client);
    char str[512];
    time_t t1;
    char* ptr;
    // Zero out the structure
    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Create socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0) {
        perror("socket creation failed");
        return 1;
    }

    // Bind the socket
    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        close(sd);
        return 1;
    }

    // Listen for incoming connections
    listen(sd, 5);

    while (1) {
        do {
            memset(str, 0, 512);
            recvfrom(sd, str, 512, 0, (struct sockaddr *)&client, &clen);
            printf("Received message from client: %s\n", str);
            printf("Client IP: %s\n", inet_ntoa(client.sin_addr));
            printf("Client Port: %d\n", ntohs(client.sin_port));
            //send the recieved message to the client
           sendto(sd,str,strlen(str)+1,0,(struct sockaddr*)&client,clen);
        } while (strcmp(str, "stop") != 0);

        close(nsd);
    }

    close(sd);
    return 0;
}


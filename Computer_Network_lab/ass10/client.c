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
    int i,j,w,sd,slen=sizeof(server),count;
    char str[512], buff[512],ack[512];

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
        printf("Enter window size: ");
        scanf("%d",&w);
        j=0;
        count=0;
        for(i=0;i<strlen(str);i++){
            if(j<w){
                buff[j]=str[i];
                j++;
            }
            if(j==w||i==strlen(str)-1){
                buff[j]='\0';
                send(sd, buff, strlen(buff) + 1, 0);
                memset(ack,0,512);
                recv(sd,ack,512,0);
                printf(" %s : %d\n", ack,count++); 
                j=0;
            }
        }
        
    } while (strcmp(str, "stop") != 0);

    close(sd);
    return 0;
}



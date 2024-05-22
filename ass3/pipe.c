#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void main() {
    char S1[1024], S2[1024];
    int fd1, n, fd2[2], pid;
    
    fd1 = open("a.txt", O_RDONLY, 0764);  // a.txt is an existing file.
    n = read(fd1, S1, sizeof(S1));
    pipe(fd2);
    
    pid = fork();
    if (pid == -1) {
        printf("Unsuccessful process creation\n");
        exit(1);
    } else if (pid == 0) {  // in child process
        close(fd2[1]);
        n = read(fd2[0], S2, sizeof(S2));
        S2[n] = '\0';
        printf("\nReading from pipe\n");
        puts(S2);
    } else {  // in parent process
        close(fd2[0]);
        write(fd2[1], S1, n);
    }
}

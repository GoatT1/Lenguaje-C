#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char * argv[])
{
    int socket_descriptor;
    struct sockaddr_in server;
    char messaRX[200];
    char messaTX[200];

    socket_descriptor = socket(AF_INET,SOCK_STREAM,0);

    if (socket_descriptor == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    //Connect

    if(connect(socket_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("connected");

    //send some data

    if(read(socket_descriptor, messaRX, sizeof(messaRX)) <0 )
    {
        puts("recv failed");
    }
    puts("servidor dice: ");
    puts(messaRX);

    puts("cliente dice: ");
    fgets(messaRX,sizeof(messaRX),stdin);
    write(socket_descriptor,messaRX,sizeof(messaRX));

    close(socket_descriptor);




    return 0;
}
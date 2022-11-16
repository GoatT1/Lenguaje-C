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

int main(int arg, char * argv[])
{
    int socket_descriptor, connection_descriptor ;
    unsigned int len;
    struct sockaddr_in servaddr, client;

    int len_rx, len_tx;
    char buff_tx[200] = "Hola cliente soy el servidor";
    char buff_rx[200];
    char * mensaje = 0;

    

    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_descriptor == -1)
    {
        printf("Could not create socket");
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);

    if((bind(socket_descriptor, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        puts("bind failed");
        return -1;
    }
    puts("bind done");

    listen(socket_descriptor, 5);

    len = sizeof(client);

    puts("Waiting connections...");

    
    
    connection_descriptor = accept(socket_descriptor, (struct sockaddr *)&client,&len);
    if(connection_descriptor < 0)
    {
        puts("failed to accept connection");
        return -1;
    }
    puts("Connection accepted");

    puts("servidor dice: ");
    fgets(buff_tx,200,stdin);
    write(connection_descriptor, buff_tx, strlen(buff_tx));

    if(read(connection_descriptor, buff_rx, sizeof(buff_rx)) < 0)
    {
        puts("recv failed");

    }
    puts("cliente dice: ");
    puts(buff_rx);

    close(connection_descriptor);
    close(socket_descriptor);

    return 0;
        
    
}
    







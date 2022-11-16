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
#include <stdio_ext.h>

#define tam 100

int main(int argc, char * argv[])
{
    int socket_descriptor;
    struct sockaddr_in server;

    char messaRX[tam];
    char messaTX[tam];

    int comuN = 5;
    int byterx = 0;

    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if(connect(socket_descriptor,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
        puts("Error al conectar");
        return 1;
    }
    puts("Conectado");

    while(comuN)
    {
        byterx = recv(socket_descriptor,messaRX,tam-1,0);
        if(byterx < 0)
        {
            puts("recv fallo");
        }
        *(messaRX+byterx)='\0';

        printf("El servidor dice: %s\n",messaRX);

        if(!strcmp(messaRX,"chau\n"))
        {
            puts("Chau recibido");
            comuN = 1;

        }
        else
        {
            printf("El cliente dice: ");
            __fpurge(stdin);
            fgets(messaTX,tam-1,stdin);
            write(socket_descriptor, messaTX, strlen(messaTX));

            if(!strcmp(messaTX,"chau\n"))
            {
                puts("Chau transmitido");
                comuN = 1;
            }
        }
        comuN--;
    }

    close(socket_descriptor);

    return 0;



}
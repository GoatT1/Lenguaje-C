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
    int socket_descriptor, connection_descriptor, c;
    struct sockaddr_in server, cliente;

    char messaTX[tam];
    char messaRX[tam];

    int comuN = 5;
    int byterx = 0;

    socket_descriptor = socket(AF_INET, SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if(bind(socket_descriptor,(struct sockaddr *)&server,sizeof(server)) != 0)
    {
        puts("Bind fallo");
        return 1;
    }
    puts("Bind aceptado");

    listen(socket_descriptor, 5);

    puts("Esperando que un cliente se conecte");

    c = sizeof(struct sockaddr_in);

    connection_descriptor = accept(socket_descriptor,(struct sockaddr*)&cliente, (socklen_t*)&c);

    if(connection_descriptor < 0)
    {
        puts("Conexion fallida");
    }
    
    puts("Cliente conectado");

    while(comuN)
    {
        printf("Servidor dice: ");
        __fpurge(stdin);
        fgets(messaTX,tam-1,stdin);

        write(connection_descriptor,messaTX,strlen(messaTX));

        if(!strcmp(messaTX,"chau\n"))
        {
            printf("Chau transmitido\n");
            comuN = 1;
        }
        else
        {
            byterx = recv(connection_descriptor, messaRX,tam-1,0);
            *(messaRX+byterx) = '\0';

            printf("Cliente dice: %s\n",messaRX);

            if(!strcmp(messaRX,"chau\n"))
            {
                printf("Chau recibido\n");
                comuN = 1;
            }

        }
        comuN--;

    }

    close(connection_descriptor);
    close(socket_descriptor);

    return 0;



    
}
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

struct persona
{
    char nombre[30];
    int edad;
};

union vinculo
{
    char buffer[sizeof(struct persona)];
    struct persona dato; 
};

int main(int argc, char * argv[])
{
    int socket_descriptor;
    struct sockaddr_in server;

    union vinculo convertir;

    int comuN=5;
    int byterx=0;

    socket_descriptor = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if(connect(socket_descriptor,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
        puts("Fallo la conexion");
        return 1;
    }
    puts("Conectado");

    while(comuN)
    {
        printf("Cargar nombre: ");
        __fpurge(stdin);
        scanf("%s",convertir.dato.nombre);
        
        printf("\nCargar edad: ");
        __fpurge(stdin);
        scanf("%d",&(convertir.dato.edad));
        printf("\n");

        write(socket_descriptor,convertir.buffer,sizeof(struct persona));

        comuN--;

    }

    close(socket_descriptor);




    return 0;
}

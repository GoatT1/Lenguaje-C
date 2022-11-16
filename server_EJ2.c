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
    int socket_descriptor,connection_descriptor,c;
    struct sockaddr_in server,cliente;

    int comuN=5;
    int byterx=0;

    union vinculo convertir;

    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family= AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if(bind(socket_descriptor,(struct sockaddr *)&server,sizeof(server)) !=0 )
    {
        puts("Bind fallo");
        return 1;
    }
    puts("Bind aceptado");

    listen(socket_descriptor,5);
    puts("Esperando que se conecte un cliente");

    c = sizeof(struct sockaddr_in);

    connection_descriptor = accept(socket_descriptor, (struct sockaddr *)&cliente,(socklen_t*)&c);

    if(connection_descriptor < 0)
    {
        puts("Conexion fallo");
    }
    puts("Cliente conectado");

    while(comuN)
    {
        byterx = recv(connection_descriptor,convertir.buffer,sizeof(struct persona),0);

        if(byterx == sizeof(struct persona))
        {
            //puts("Estructura recibida");

            printf("Cliente dice:\n %s\n %d\n",convertir.dato.nombre,convertir.dato.edad);
        }
        
    }

    close(connection_descriptor);
    close(socket_descriptor);




    return 0;
}

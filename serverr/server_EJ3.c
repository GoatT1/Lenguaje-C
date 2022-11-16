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

#define bmaxArch 2048

struct archivo
{
    char nombre[256];
    unsigned long int tam;
    char bytesarch[bmaxArch];
};

union vinculo
{
    char buffer[sizeof(struct archivo)];
    struct archivo dato;
};

int main(int argc, char *argv[])
{
    int socket_descriptor, connection_descriptor, c;
    struct sockaddr_in server,cliente;

    union vinculo convertir;

    int fd=-1;

    int byterx=0;

    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if(bind(socket_descriptor,(struct sockaddr*)&server,sizeof(server)) != 0)
    {
        puts("Bind fallo");
        return 1;
    }
    puts("Bind aceptado");

    listen(socket_descriptor,3);
    
    c=sizeof(struct sockaddr_in);

    connection_descriptor = accept(socket_descriptor,(struct sockaddr*)&cliente,(socklen_t*)&c);

    if(connection_descriptor < 0)
    {
        puts("Fallo la conexion");
        return 1;
    }

    puts("Cliente conectado");

    byterx = recv(connection_descriptor, convertir.buffer,sizeof(struct archivo),0);

    fd = open(convertir.dato.nombre,O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    if(fd==-1)
    {
        puts("Error al abrir archivo");
    }
    else
    {
        write(fd,(convertir.buffer+256+sizeof(unsigned long int)),convertir.dato.tam);

    }

    

    close(fd);
    close(connection_descriptor);
    close(socket_descriptor);










    return 0;
}
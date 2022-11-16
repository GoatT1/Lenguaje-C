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

    struct sockaddr_in server;

    int socket_descriptor;
    int fd=0;
    int byterx=0;
    long int tama=0;
    int leido=0;
    
    struct archivo dato;
    union vinculo convertir;


    fd=open(argv[1],O_RDONLY);
    if(fd == -1)
    {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }
    else
    {
        tama=lseek(fd,0,SEEK_END);
        printf("El tamaño del archivo es: %ld\n",tama);
        lseek(fd,0,SEEK_SET);
    }
    if(tama >= 0 && tama <= bmaxArch)
    {
        leido = read(fd,convertir.dato.bytesarch,tama);
        convertir.dato.tam = tama;
        strcpy(convertir.dato.nombre,argv[1]);

    }

    socket_descriptor = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if(connect(socket_descriptor,(struct sockaddr*)&server,sizeof(server)) <0 )
    {
        puts("Fallo en conectar");
        return 1;
    }
    //puts("Conectado");

    write(socket_descriptor,convertir.buffer,sizeof(struct archivo));

    close(fd);

    close(socket_descriptor);





    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
#include <stdlib.h>

char* barras(char * s1);

int main(int argc, char ** argv[])
{
    char *datos[3];
    

    for(int i=0;i<3;i++)
    {
        __fpurge(stdin);
        datos[i] = (char*)malloc(30*sizeof(char*));
        fgets(datos[i],30,stdin);
        __fpurge(stdin);

    }

    for(int i=0;i<3;i++)
    {
        barras(datos[i]);
    }
    for(int i=0;i<3;i++)
    {
        printf("%s",datos[i]);
    }




    return 0;
}

char* barras(char * s1)
{
    
    char * inicio = s1;

    while(*inicio != '\0')
    {
        inicio++;
    }
    

    *inicio = '\r';
    *(inicio+1) = '\n';
    *(inicio+2) = '\0';
    return s1;
}
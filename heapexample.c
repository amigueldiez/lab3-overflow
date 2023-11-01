#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

struct s_data {
    char buffer[64];
};

struct s_fp{
    int(*fp)();
};

void f_entrar()
{
    printf("Pasando\n");
}

void f_espero_fuera()
{
    printf("Esperando fuera\n");
}

int main (int argc, char **argv)
{
    struct s_data *s_midat;
    struct  s_fp *f;

    s_midat = malloc(sizeof(struct s_data));
    f = malloc(sizeof(struct s_fp));
    f->fp = f_espero_fuera;

    printf("data: esta en [%p], el puntero fp esta en [%p]\n",s_midat,f);

    strcpy(s_midat->buffer,argv[1]);

    f->fp();

}
#include <stdio.h>
#include "AFK.h"


int main()
{
    FILE *file;
    char buffer[256];

    file = fopen("code.txt", "r");
    if (file == NULL)
    {
        perror("Erro ao abrir o Arquivo!");
    }

    char entrada[TAM];

    int linha = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Linha %d ", linha);
        AFD(buffer);
        linha++;
    }

    return 0;
}

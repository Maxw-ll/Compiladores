#include <stdio.h>
#include <ctype.h>
#include "AFK.h"


void AFD(char *entrada)
{
    int estado = 0, idx_entrada = 0, idx_token = 0;
    char token[TAM];
    
  
    while (estado != 5)
    {
        char caractere = entrada[idx_entrada];

        //printf("Estado Atual: %d\n", estado);
        //printf("Caractere Atual: %c\n", entrada[idx_entrada]);

        switch (estado)
        {
            case 0:
            {
                if (caractere == '-')
                {
                    token[idx_token] = caractere;
                    idx_token++;
                    estado++;
                }
                else if (isdigit(caractere))
                {
                    token[idx_token] = caractere;
                    idx_token++;
                    estado += 2;
                }
            } break;

            case 1:
            {
                if (isdigit(caractere))
                {
                    token[idx_token] = caractere;
                    idx_token++;
                    estado++;
                }
            } break;

            case 2:
            {
                if(isdigit(caractere))
                {
                    token[idx_token] = caractere;
                    idx_token++;
                    estado = 2;   
                }
                else if (caractere == ',')
                {
                    token[idx_token] = caractere;
                    idx_token++;
                    estado++;
                }
                else
                {
                    estado = 5;
                }
            } break;

            case 3:
            {
                if(isdigit(caractere))
                {
                    token[idx_token] = caractere;
                    idx_token++;
                    estado++;
                }
            } break;

            case 4:
            {
                if (isdigit(caractere))
                {       
                    token[idx_token] = caractere;
                    idx_token++;
                    estado = 4;
                }
                else
                {
                    estado = 5;
                }
            } break;
        }

        if (caractere == '\0')
        {
            break;
        }

        idx_entrada++; 
    }

    token[idx_token] = '\0';

    if (estado == 5)
    {
        printf("Aceito! Token Encontrado: %s\n", token);
    }
    else
    {
        printf("Rejeitado! Nenhum Token foi encontrado\n");
    }
    
}
/*
int main()
{
    char entrada[TAM];

    printf("Digite a entrada a ser analisada pelo AFD: \n");
    scanf("%s", entrada);

    AFD(entrada);

    return 0;
}
*/

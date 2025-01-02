#include "Analisador.h"
#include <stdio.h>
#include <stdlib.h>

#define TEXT_TAM 50

int main()
{   

    printf("Digite algo: ");
    char* text = (char*)malloc(sizeof(char*)*TEXT_TAM);
    fgets(text, TEXT_TAM, stdin);
    printf("%s", text);
    Lexer* l = create_lexer(text);

    info_lexer(l);

}

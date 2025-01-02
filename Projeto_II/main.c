#include "Analisador.h"
#include <stdio.h>
#include <stdlib.h>



int main()
{   

    printf("Digite algo: ");
    char* text = (char*)malloc(sizeof(char*)*TEXT_TAM);
    fgets(text, TEXT_TAM, stdin);
    Lexer* l = create_lexer(text);
    int i= 0;
    Token *t = (Token*)malloc(sizeof(Token));
    
    while(l->pointer < l->tam)
    {
        t = get_next_token(l);
        info_token(t);
    }

}

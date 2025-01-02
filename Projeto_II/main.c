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
  
    Sintaxer *s = create_sintaxer(l);
    TreeNode *t = expression(s);

    show_tree(t, 0);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Analisador.h"

#define TAM_OPER 3
char *operators = "+-*";

#define TAM_PAREN 2
char *parenteses = "()";



int isoperator(char c)
{
    for(int i = 0; i < TAM_OPER; i++)
    {
        if(c == operators[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

int isparentheses(char c)
{
    for(int i=0; i<TAM_PAREN; i++)
    {
        if(c == parenteses[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

int isatribb(char c)
{
    if(c == ':')
    {
        return TRUE;
    }
    return FALSE;
}

Lexer *create_lexer(char *text)
{
    Lexer *l = (Lexer *)malloc(sizeof(Lexer));
    if (l != NULL)
    {
        text[strlen(text) - 1] = '\0';
        l->text = text;
        l->pointer = 0;
        l->current_char = l->text[l->pointer];
        l->tam = strlen(text);
    }

    return l;
}

void info_lexer(Lexer *l)
{

    if (l != NULL)
    {
        printf("----- INFO ANALISADOR LEXICO -----\n");
        printf("TEXTO: %s\n", l->text);
        printf("PONTEIRO: %d\n", l->pointer);
        printf("CURRENT_CHAR: %c\n", l->current_char);
        printf("TAMANHO: %d\n", l->tam);
        printf("----------------------------------\n");
    }

    else
    {
        printf("ERRO: Analisador Null");
    }
}

void advance(Lexer *l)
{
    l->pointer++;
    l->current_char = l->text[l->pointer];
}

void skip_whhitespace(Lexer *l)
{
    while (l->current_char == ' ' && l->pointer < l->tam)
    {
        advance(l);
    }
}

void info_token(Token *t)
{   
    if( t != NULL )
    {
        printf("----- INFO TOKEN -----\n");
        printf("Token Type: %s\n", t->type);
        printf("Token Value: %s\n", t->value);
        printf("----------------------\n");
    }

}

Token *number(Lexer *l)
{
    Token *t = (Token *)malloc(sizeof(Token));
    char *result = (char*)malloc(sizeof(char)*TEXT_TAM);
    int indx = 0;
    while (isdigit(l->current_char) && l->pointer < l->tam)
    {
        result[indx] = l->current_char;
        advance(l);
        indx++;
    }
    result[indx] = '\0';

    t->type = "NUMBER";
    t->value = result;

    return t;
}

Token *identificador(Lexer *l)
{   
    Token *t = (Token*)malloc(sizeof(Token));
    char *result = (char*)malloc(sizeof(char)*TEXT_TAM);
    int indx = 0;
    while(isalpha(l->current_char) && l->pointer < l->tam)
    {   
        result[indx] =  l->current_char;
        advance(l);
        indx++;
    }
    result[indx] = '\0';

    t->type = "IND";
    t->value = result;
    

    return t;
}

Token* operator(Lexer *l)
{   
    char *result = (char*)malloc(sizeof(char)*TEXT_TAM);
    Token *t = (Token*)malloc(sizeof(Token));

    result[0] = l->current_char;
    result[1] = '\0';

    t->type = "OPER";
    t->value = result;
    advance(l);
    return t;

}

Token *parentese(Lexer *l)
{   
    char *result = (char*)malloc(sizeof(char)*TEXT_TAM);
    Token *t = (Token*)malloc(sizeof(Token));

    result[0] = l->current_char;
    result[1] = '\0';

    t->type = "PAREN";
    t->value = result;
    advance(l);
    return t;

}

Token *atribuicao(Lexer *l)
{
    char *result = (char*)malloc(sizeof(char)*TEXT_TAM);
    Token *t = (Token*)malloc(sizeof(Token));
    result[0] = l->current_char;

    advance(l);

    if(l->current_char == '=')
    {
        result[1] = l->current_char;
        result[2] = '\0';

        t->type = "ATRIB";
        t->value = result;
        advance(l);
        return t;
    }

    printf("Erro Lexico: Caractere Inesperado -> %c Apos :\n", l->current_char);
   
   
    return NULL;

}

Token* get_next_token(Lexer *l)
{   
    if(l->current_char != '\0')
    {
        if(l->current_char == ' ')
        {
            skip_whhitespace(l);
        }
        if(isdigit(l->current_char))
        {
            return number(l);
        }
        if(isalpha(l->current_char))
        {
            return identificador(l);
        }
        if (isoperator(l->current_char))
        {
            return operator(l);
        }
        if(isparentheses(l->current_char))
        {
            return parentese(l);
        }
        if(isatribb(l->current_char))
        {
            return atribuicao(l);
        }
        else
        {
            printf("Erro Lexico: Caractere Inesperado -> %c\n", l->current_char);
            advance(l);
            return NULL;
        }

    }

    Token *t = (Token*)malloc(sizeof(Token));
    t->type = "EOF";
    t->value = "";
    return t;
}


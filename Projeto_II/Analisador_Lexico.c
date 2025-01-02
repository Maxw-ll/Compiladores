#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Analisador.h"

#define TRUE 1
#define FALSE 0

#define TAM_OPER 3
char *operators = {'+', '-', '*'};

#define TAM_PAREN 2
char *parenteses = {'(',')'};



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
        printf("TAMANHO: %d", l->tam);
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
    while (l->current_char == " " && l->pointer < l->tam)
    {
        advance(l);
    }
}

Token *number(Lexer *l)
{
    Token *t = (Token *)malloc(sizeof(Token));
    char *result = "";
    int indx = 0;
    while (isdigit(l->current_char))
    {
        result[indx] = l->current_char;
        advance(l);
        indx++;
    }
    t->type = "NUMBER";
    t->value = result;

    return t;
}

Token *identificador(Lexer *l)
{   
    Token *t = (Token*)malloc(sizeof(Token));
    char* result = "";
    int indx = 0;
    while(isalpha(l->current_char))
    {   
        result[indx] =  l->current_char;
        advance(l);
        indx++;
    }

    t->type = "IND";
    t->value = result;

    return t;
}

Token* operator(Lexer *l)
{
    Token *t = (Token*)malloc(sizeof(Token));
    t->type = "OPERATOR";
    t->value = l->current_char;
    return t;

}

Token *parentese(Lexer *l)
{
    Token *t = (Token*)malloc(sizeof(Token));
    t->type = "PARENTESES";
    t->value = l->current_char;
    return t;

}

Token *get_next_token(Lexer *l)
{   
    while(l->current_char != '\0')
    {
        if(l->current_char == " ")
        {
            skip_whhitespace(l);
            continue;
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

    }
}


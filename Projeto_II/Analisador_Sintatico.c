#include "Analisador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Sintaxer* create_sintaxer(Lexer *l)
{
    Sintaxer *s = (Sintaxer *)malloc(sizeof(Sintaxer));
    s->l = l;
    s->current_token = get_next_token(s->l);
    s->last_token = NULL;
    

    return s;
}
void consume(Sintaxer *s, Token *t)
{
    if (strcmp(s->current_token->type, t->type) == 0)
    {
        printf("Token Consumido!\n");
        //info_token(t);
        s->last_token = s->current_token;
        s->current_token = get_next_token(s->l);
       
    }
    // else
    // {
    //     error(s, t);
    //     while (strcmp(s->current_token->type, "EOF") != 0 && strcmp(s->current_token->type, t->type) != 0) //&& strcmp(s->current_token->type, "OPER") != 0 && strcmp(s->current_token->type, "PAREN") != 0) 
    //     {
    //         s->current_token = get_next_token(s->l);
    //     }
    // }
}


TreeNode* erro_fator(Sintaxer *s, Token *t)
{
    error(s, t);
    while (strcmp(s->current_token->type, "EOF") != 0 && strcmp(s->current_token->type, "IND") != 0 && strcmp(s->current_token->type, "NUMBER") != 0 && strcmp(s->current_token->value, "(") != 0)
    {
        s->current_token = get_next_token(s->l);
    }
    if(strcmp(s->current_token->type, "IND") == 0 || strcmp(s->current_token->type, "NUMBER") == 0 || strcmp(s->current_token->value, "(") == 0)
    {
        return fator(s);
    }
    return NULL;
}


TreeNode* error(Sintaxer *s, Token *t)
{   
    // if (strcmp(s->current_token->type, "EOF") == 0)
    // {

    // }
    if(strcmp(t->value, ")") == 0)
    {
        printf("Token Inesperado! Erro Sintatico. Esperado ) \n", s->current_token->value);
    }
    else if(s->last_token == NULL)
    {
        printf("Token Inesperado! Erro em: %s. Esperado IND, NUMBER ou (\n", s->current_token->value);
    } 
    else if (strcmp(s->last_token->type, "IND") == 0)
    { 
       printf("Token Inesperado! Erro em: '%s'. Esperado um OPERADOR: +, - ou * \n", s->current_token->value);
    }
    else if((strcmp(s->last_token->type, "NUMBER") == 0))
    {
        printf("Token Inesperado! Erro em: '%s'. Esperado um OPERADOR: +, - ou * \n", s->current_token->value);
    }
    else if(strcmp(s->last_token->type, "OPER") == 0)
    {
        printf("Token Inesperado! Erro em: %s. Esperado IND, NUMBER ou (\n", s->current_token->value);
    }

    //s->last_token = s->current_token;
    //s->current_token = get_next_token(s->l);
    //return expression(s);
    return NULL;

 
}

TreeNode *fator(Sintaxer *s)
{   
   
    Token *t = s->current_token;

    TreeNode *current_node = (TreeNode *)malloc(sizeof(TreeNode));

    if (strcmp(t->type, "NUMBER") == 0)
    {   
        consume(s, t);
        current_node->type = "UNI";
        current_node->value = t->value;
        current_node->left = NULL;
        current_node->right = NULL;
    }
    else if (strcmp(t->type, "IND") == 0)
    {
        consume(s, t);
        current_node->type = "UNI";
        current_node->value = t->value;
        current_node->left = NULL;
        current_node->right = NULL;

    }
    else if (strcmp(t->value, "(") == 0)
    {
        Token *para_fecha = (Token*)malloc(sizeof(Token));
        para_fecha->type = "PAREN";
        para_fecha->value = ")";
        consume(s, t);
        current_node = expression(s);
        if (strcmp(s->current_token->value, ")") != 0)
        {
            error(s, para_fecha);
        }
        
    }
    else
    {
       return erro_fator(s,t);
    }

    return current_node;
}

TreeNode *term(Sintaxer *s)
{   

    TreeNode *current_node;
    current_node = fator(s);

    if(strcmp(s->current_token->type, "EOF") != 0 && strcmp(s->current_token->type, "OPER") != 0 && strcmp(s->current_token->value, ")") != 0)
    {   
        Token *tz = (Token*)malloc(sizeof(Token));
        tz->type = "OPER";
        tz->value = "";
        consume(s, tz);
    }


    while (strcmp(s->current_token->type, "OPER") == 0 && strcmp(s->current_token->value, "*") == 0)
    {
        Token *t = s->current_token;
        consume(s, t);
        TreeNode *newnode = (TreeNode *)malloc(sizeof(TreeNode));
        newnode->type = "BIN";
        newnode->value = t->value;
        newnode->left = current_node;
        newnode->right = fator(s);
        current_node = newnode;
    }

    return current_node;
}

TreeNode *expression(Sintaxer *s)
{   
    

    TreeNode *current_node;
    current_node = term(s);

    if(strcmp(s->current_token->type, "EOF") != 0 && strcmp(s->current_token->type, "OPER") != 0 && strcmp(s->current_token->value, ")") != 0)
    {   
        Token *tz = (Token*)malloc(sizeof(Token));
        tz->type = "OPER";
        tz->value = "";
        consume(s, tz);
    }


    while (strcmp(s->current_token->type, "OPER") == 0 && (strcmp(s->current_token->value, "+") == 0  || strcmp(s->current_token->value, "-") == 0))
    {
        Token *t = s->current_token;
        consume(s, t);
        TreeNode *newnode = (TreeNode *)malloc(sizeof(TreeNode));
        newnode->type = "BIN";
        newnode->value = t->value;
        newnode->left = current_node;
        //info_node(newnode);
        newnode->right = term(s);
        current_node = newnode;
    }

    return current_node;
}



void spaces(int space)
{
    for(int i=0; i<space; i++)
        {
            printf("\t");
        }
}

void info_node(TreeNode *node)
{   
    if(node != NULL)
    {   
        printf("----------- INFO NODE ---------\n");
        printf("Node Type: %s\n", node->type);
        printf("Node Value: %s\n", node->value);
        printf("-------------------------------\n");
    }
    else
    {
        printf("Node NULL");
    }

}
void show_tree(TreeNode *node, int space)
{ 
    
    if(space == 0)
    {
        printf("-------------- INFO TREENODE --------------\n");

    }
    
    if(node != NULL){
        
        spaces(space);
        printf("Node Type: %s\n", node->type);
        spaces(space);
        printf("Node Value: %s\n", node->value);
        spaces(space);
        printf("Filho Esquerdo: \n");
        show_tree(node->left, space+1);
        spaces(space);
        printf("Filho Direito: \n");
        show_tree(node->right, space+1);
    } 
    else
    {   
        spaces(space);
        printf(" NULL NODE\n");
    }
}




TreeNode* analisador_sintatico(Sintaxer *s)
{
    //s->current_token = get_next_token(s->l);
    int i = 0;
    while(strcmp(s->current_token->type, "EOF") != 0)
    {
        if(strcmp(s->current_token->type, "NUMBER") == 0)
        {
            return expression(s);
        }
        else if(strcmp(s->current_token->type, "IND") == 0)
        {
            return expression(s);
        }
        else if(strcmp(s->current_token->value, "(") == 0)
        {
            return expression(s);
        }
        else
        {
            if(i == 0)
            {
                printf("Token Inesperado! Erro em: %s. Esperado IND, NUMBER ou (\n", s->current_token->value);
            }
            s->last_token = s->current_token;
            s->current_token = get_next_token(s->l);
        }

        i++;


    }

}
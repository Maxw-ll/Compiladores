#include "Analisador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Sintaxer* create_sintaxer(Lexer *l)
{
    Sintaxer *s = (Sintaxer *)malloc(sizeof(Sintaxer));
    s->l = l;
    s->current_token = get_next_token(s->l);
    

    return s;
}
void consume(Sintaxer *s, Token *t)
{
    if (strcmp(s->current_token->type, t->type) == 0)
    {
        printf("Token Consumido!\n");
        info_token(t);
        s->current_token = get_next_token(s->l);
       
    }
    else
    {
        printf("Erro: Token Inesperado!");
    }
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
        consume(s, t);
        current_node = expression(s);
        consume(s,t);
        
    }
    else{
        printf("Token Inesperado -> Erro Sintatico em: %s\n", t->value);
        return NULL;
    }

    return current_node;
}

TreeNode *term(Sintaxer *s)
{   
    

    TreeNode *current_node;
    current_node = fator(s);
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
    if(strcmp(s->current_token->type, "EOF") == 0)
    return NULL;
    

    TreeNode *current_node;
    current_node = term(s);


    while (strcmp(s->current_token->type, "OPER") == 0 && (strcmp(s->current_token->value, "+") == 0  || strcmp(s->current_token->value, "-") == 0))
    {
        Token *t = s->current_token;
        consume(s, t);
        TreeNode *newnode = (TreeNode *)malloc(sizeof(TreeNode));
        newnode->type = "BIN";
        newnode->value = t->value;
        newnode->left = current_node;
        info_node(newnode);
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
#ifndef ANALISADOR_LEX_SIN
#define ANALISADOR_LEX_SIN


#define TRUE 1
#define FALSE 0
#define TEXT_TAM 50
//Token
typedef struct token
{
    char* type;
    char* value;
}Token;


//Analisador Léxico
typedef struct lexer
{
    char* text;
    char current_char;

    int tam;
    int pointer;

} Lexer;

Lexer* create_lexer(char* text);
Token* get_next_token(Lexer *l);
Token *parentese(Lexer *l);
Token* operator(Lexer *l);
Token *identificador(Lexer *l);
Token *number(Lexer *l);

int isparentheses(char c);
int isoperator(char c);

void advance(Lexer *l);
void info_token(Token *t);
void info_lexer(Lexer *l);
void skip_whhitespace(Lexer *l);

//Analisador Sintático

typedef struct sintaxer
{   
    Lexer *l;
    Token *current_token;
    Token *last_token;
} Sintaxer;

typedef struct treenode
{
    char* type;
    char* value;
    struct treenode *left;
    struct treenode *right;
} TreeNode;

void spaces(int space);
void consume(Sintaxer *s, Token *t);
void show_tree(TreeNode *node, int space);
void info_node(TreeNode *t);

Sintaxer *create_sintaxer(Lexer *l);


TreeNode* error(Sintaxer *s, Token *t);
TreeNode *expression(Sintaxer *s);
TreeNode *term(Sintaxer *s);
TreeNode *fator(Sintaxer *s);
TreeNode* analisador_sintatico(Sintaxer *s);
#endif
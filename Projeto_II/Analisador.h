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









#endif
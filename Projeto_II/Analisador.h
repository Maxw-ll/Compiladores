#ifndef ANALISADOR_LEX_SIN
#define ANALISADOR_LEX_SIN

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
void info_lexer(Lexer *l);








#endif
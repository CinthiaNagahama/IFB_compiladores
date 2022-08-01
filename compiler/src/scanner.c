#include <ctype.h>
#include <string.h>
#include "../headers/input.h"
#include "../headers/errors.h"
#include "../headers/scanner.h"
#include "../headers/symbolsTable.h"

/* Verifica se caractere combina com o esperado */
void Match(char c)
{
    if (Look != c)
        Expected("'%c'", c);
    NextChar();
}

/* Recebe o nome de um identificador ou palavra-chave */
void GetName()
{
    int i;

    SkipWhite();
    if (!isalpha(Look))
        Expected("Identifier or Keyword");
    for (i = 0; isalnum(Look) && i < MAXTOKEN; i++)
    {
        TokenText[i] = toupper(Look);
        NextChar();
    }
    TokenText[i] = '\0';
    Token = 'x';
}

/* Recebe um número inteiro */
void GetNum()
{
    int i;

    SkipWhite();
    if (!isdigit(Look))
        Expected("Integer");
    for (i = 0; isdigit(Look) && i < MAXTOKEN; i++)
    {
        TokenText[i] = Look;
        NextChar();
    }
    TokenText[i] = '\0';
    Token = '#';
}

/* Analisa e traduz um operador */
void GetOp()
{
    SkipWhite();
    Token = Look;
    TokenText[0] = Look;
    TokenText[1] = '\0';
    NextChar();
}

/* Pega o próximo Token de entrada */
void NextToken()
{
    SkipWhite();
    if (isalpha(Look))
        GetName();
    else if (isdigit(Look))
        GetNum();
    else
        GetOp();
}

/* Analisador léxico */
void Scan()
{
    int kw;

    if (Token == 'x')
    {
        kw = Lookup(TokenText, KeywordList, KEYWORDLIST_SIZE);
        if (kw >= 0)
            Token = KeywordCode[kw];
    }
}

/* Verifica se a string combina com o esperado */
void MatchString(char *s)
{
    if (strcmp(TokenText, s) != 0)
        Expected(s);
    NextToken();
}

/* Reconhece operador aditivo */
int IsAddOp(char c)
{
    return (c == '+' || c == '-');
}

/* Reconhece operador multiplicativo */
int IsMulOp(char c)
{
    return (c == '*' || c == '/');
}

/* Reconhece um operador OU */
int IsOrOp(char c)
{
    return (c == '|' || c == '~');
}

/* Reconhece operadores relacionais */
int IsRelOp(char c)
{
    return (c == '=' || c == '#' || c == '<' || c == '>');
}

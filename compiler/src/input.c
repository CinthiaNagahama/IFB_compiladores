#include <stdio.h>
#include <ctype.h>
#include "../headers/input.h"
#include "../headers/scanner.h"
#include "../headers/symbolsTable.h"

char Look; /* O caractere lido "antecipadamente" (lookahead) */

/* Lê próximo caractere da entrada */
void NextChar()
{
    Look = getchar();
}

/* Inicialização do compilador */
void Init()
{
    SymbolCount = 0;

    NextChar();
    NextToken();
}

/* Pula um campo de comentário */
void SkipComment()
{
    while (Look != '}')
    {
        NextChar();
        if (Look == '{') /* Trata comentários aninhados */
            SkipComment();
    }
    NextChar();
}

/* Pula caracteres em branco */
void SkipWhite()
{
    while (isspace(Look) || Look == '{')
    {
        if (Look == '{')
            SkipComment();
        else
            NextChar();
    }
}

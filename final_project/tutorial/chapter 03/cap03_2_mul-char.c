/*
Capítulo 03 - Mais expressões, espaços e identificadores com múltiplos caracteres
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#define MAXNAME 30
#define MAXNUM 5

char Look; /* O caractere lido "antecipadamente" (lookahead) */

/* Protótipos */
void Init();
void NextChar();
void Error(char *fmt, ...);
void Abort(char *fmt, ...);
void Expected(char *fmt, ...);
void Match(char c);
void GetName(char *name);
void GetNum(char *num);
void EmitLn(char *fmt, ...);

void Expression();
void Term();
void Factor();
int IsAddOp(char c);
void Add();
void Subtract();
void Multiply();
void Divide();

void SkipWhiteSpace();
void Identifier();
void Assignment();

/* Programa principal */
int main()
{
    Init();
    Assignment();
    // Expression();
    if (Look != '\n')
        Expected("NewLine");

    return 0;
}

/* ---------------------------------------- CAP 01 ---------------------------------------- */

/* Inicialização do compilador */
void Init()
{
    NextChar();
    SkipWhiteSpace();
}

/* Lê próximo caractere da entrada */
void NextChar()
{
    Look = getchar();
}

/* Exibe uma mensagem de erro formatada */
void Error(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
}

/* Exibe uma mensagem de erro formatada e sai */
void Abort(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);

    exit(1);
}

/* Alerta sobre alguma entrada esperada */
void Expected(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputs(" expected!\n", stderr);

    exit(1);
}

/* Verifica se entrada combina com o esperado */
void Match(char c)
{
    if (Look != c)
        Expected("'%c'", c);
    NextChar();
    SkipWhiteSpace();
}

/* Recebe o nome de um identificador */
void GetName(char *name)
{
    int i;
    if (!isalpha(Look))
        Expected("Name");

    for (i = 0; isalnum(Look); i++)
    {
        if (i >= MAXNAME)
            Abort("Identifier is too long!");
        name[i] = toupper(Look);
        NextChar();
    }
    name[i] = '\0';
    SkipWhiteSpace();
}

/* Recebe um número inteiro */
void GetNum(char *num)
{
    int i;
    if (!isdigit(Look))
        Expected("Integer");
    for (i = 0; isdigit(Look); i++)
    {
        if (i >= MAXNUM)
            Abort("Integer too long!");
        num[i] = Look;
        NextChar();
    }
    num[i] = '\0';
    SkipWhiteSpace();
}

/* Emite uma instrução seguida por uma nova linha */
void EmitLn(char *fmt, ...)
{
    va_list args;

    putchar('\t');

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    putchar('\n');
}

/* Analisa e traduz um fator matemático */
void Factor()
{
    char num[MAXNUM + 1];
    if (Look == '(')
    {
        Match('(');
        Expression();
        Match(')');
    }
    else if (isalpha(Look))
    {
        Identifier();
    }
    else
    {
        GetNum(num);
        EmitLn("MOV AX, %s", num);
    }
}

/* Analisa e traduz um termo */
void Term()
{
    Factor();
    while (Look == '*' || Look == '/')
    {
        EmitLn("PUSH AX");
        switch (Look)
        {
        case '*':
            Multiply();
            break;
        case '/':
            Divide();
            break;
        default:
            break;
        }
    }
}

int IsAddOp(char c)
{
    return (c == '+' || c == '-');
}

/* Reconhece e traduz uma expressão */
void Expression()
{
    if (IsAddOp(Look))
        EmitLn("XOR AX, AX");
    else
        Term();
    while (IsAddOp(Look))
    {
        EmitLn("PUSH AX");
        switch (Look)
        {
        case '+':
            Add();
            break;
        case '-':
            Subtract();
            break;
        default:
            break;
        }
    }
}

/* Reconhece e traduz uma adição */
void Add()
{
    Match('+');
    Term();
    EmitLn("POP BX");
    EmitLn("ADD AX, BX");
}

/* Reconhece e traduz uma subtração */
void Subtract()
{
    Match('-');
    Term();
    EmitLn("POP BX");
    EmitLn("SUB AX, BX");
    EmitLn("NEG AX");
}

/* Reconhece e traduz uma multiplicação */
void Multiply()
{
    Match('*');
    Factor();
    EmitLn("POP BX");
    EmitLn("IMUL BX");
};

/* Reconhece e traduz uma divisão */
void Divide()
{
    Match('/');
    Factor();
    EmitLn("POP BX");
    EmitLn("XCHG AX, BX");
    EmitLn("CWD");
    EmitLn("IDIV BX");
};

/* Pula caracteres de espaço */
void SkipWhiteSpace()
{
    while (Look == ' ' || Look == '\t')
        NextChar();
}

/* Analisa e traduz um identificador */
void Identifier()
{
    char name[MAXNAME + 1];
    GetName(name);
    if (Look == '(')
    {
        Match('(');
        Match(')');
        EmitLn("CALL %s", name);
    }
    else
        EmitLn("MOV AX, [%s]", name);
}

/* Analisa e traduz um comando de atribuição */
void Assignment()
{
    char name[MAXNAME + 1];
    GetName(name);
    Match('=');
    Expression();
    EmitLn("MOV [%s], AX", name);
}
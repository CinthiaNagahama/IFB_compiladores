/*
Capítulo 03 - Mais expressões
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

char Look; /* O caractere lido "antecipadamente" (lookahead) */

/* Protótipos */
void Init();
void NextChar();
void Error(char *fmt, ...);
void Abort(char *fmt, ...);
void Expected(char *fmt, ...);
void Match(char c);
char GetName();
char GetNum();
void EmitLn(char *fmt, ...);

void Expression();
void Term();
void Factor();
int IsAddOp(char c);
void Add();
void Subtract();
void Multiply();
void Divide();

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
}

/* Recebe o nome de um identificador */
char GetName()
{
    char name;

    if (!isalpha(Look))
        Expected("Name");
    name = toupper(Look);
    NextChar();

    return name;
}

/* Recebe um número inteiro */
char GetNum()
{
    char num;

    if (!isdigit(Look))
        Expected("Integer");
    num = Look;
    NextChar();

    return num;
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
        EmitLn("MOV AX, %c", GetNum());
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

/* Analisa e traduz um identificador */
void Identifier()
{
    char name;
    name = GetName();
    if (Look == '(')
    {
        Match('(');
        Match(')');
        EmitLn("CALL %c", name);
    }
    else
        EmitLn("MOV AX, [%c]", name);
}

/* Analisa e traduz um comando de atribuição */
void Assignment()
{
    char name = GetName();
    Match('=');
    Expression();
    EmitLn("MOV [%c], AX", name);
}
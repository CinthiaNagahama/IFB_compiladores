#include <ctype.h>
#include <string.h>
#include "../headers/input.h"
#include "../headers/scanner.h"
#include "../headers/codegen.h"
#include "../headers/errors.h"
#include "../headers/parser.h"
#include "../headers/symbolsTable.h"

/* Analisa uma lista de declaração de variáveis */
void Declaration()
{
    NextToken();
    CheckIdent();
    CheckDuplicate(TokenText);
    AddEntry(TokenText, 'v');
    AllocVar(TokenText, 0);
    NextToken();
}

/* Reconhece um ponto-e-vírgula opcional */
void Semicolon()
{
    if (Token == ';')
        MatchString(";");
}

/* Analisa e traduz declarações globais */
void TopDeclarations()
{
    Scan();
    while (Token == 'v')
    {
        do
        {
            Declaration();
        } while (Token == ',');
        Semicolon();
        Scan();
    }
}

void BoolExpression(); /* Declaração adianta */

/* Analisa e traduz um fator matemático */
void Factor()
{
    if (Token == '(')
    {
        NextToken();
        BoolExpression();
        MatchString(")");
    }
    else
    {
        if (Token == 'x')
        {
            CheckTable(TokenText);
            AsmLoadVar(TokenText);
        }
        else if (Token == '#')
            AsmLoadConst(TokenText);
        else
            Expected("Math Factor");
        NextToken();
    }
}

/* Reconhece e traduz uma multiplicação */
void Multiply()
{
    NextToken();
    Factor();
    AsmPopMul();
}

/* Reconhece e traduz uma divisão */
void Divide()
{
    NextToken();
    Factor();
    AsmPopDiv();
}

/* Analisa e traduz um termo matemático */
void Term()
{
    Factor();
    while (IsMulOp(Token))
    {
        AsmPush();
        switch (Token)
        {
        case '*':
            Multiply();
            break;
        case '/':
            Divide();
            break;
        }
    }
}

/* Reconhece e traduz uma adição */
void Add()
{
    NextToken();
    Term();
    AsmPopAdd();
}

/* Reconhece e traduz uma subtração*/
void Subtract()
{
    NextToken();
    Term();
    AsmPopSub();
}

/* Analisa e traduz uma expressão matemática */
void Expression()
{
    if (IsAddOp(Token))
        AsmClear();
    else
        Term();
    while (IsAddOp(Token))
    {
        AsmPush();
        switch (Token)
        {
        case '+':
            Add();
            break;
        case '-':
            Subtract();
            break;
        }
    }
}

/* Analisa e traduz uma relação */
void Relation()
{
    char op;

    Expression();
    if (IsRelOp(Token))
    {
        op = Token;
        NextToken(); /* Só para remover o operador do caminho */
        if (op == '<')
        {
            if (Token == '>')
            { /* Trata operador <> */
                NextToken();
                op = '#';
            }
            else if (Token == '=')
            { /* Trata operador <= */
                NextToken();
                op = 'L';
            }
        }
        else if (op == '>' && Token == '=')
        { /* Trata operador >= */
            NextToken();
            op = 'G';
        }
        AsmPush();
        Expression();
        AsmPopCompare();
        AsmRelOp(op);
    }
}

/* Analisa e traduz um fator booleano com NOT inicial */
void NotFactor()
{
    if (Token == '!')
    {
        NextToken();
        Relation();
        AsmNot();
    }
    else
        Relation();
}

/* Analisa e traduz um termo booleano */
void BoolTerm()
{
    NotFactor();
    while (Token == '&')
    {
        NextToken();
        AsmPush();
        NotFactor();
        AsmPopAnd();
    }
}

/* Reconhece e traduz um operador OR */
void BoolOr()
{
    NextToken();
    BoolTerm();
    AsmPopOr();
}

/* Reconhece e traduz um operador XOR */
void BoolXor()
{
    NextToken();
    BoolTerm();
    AsmPopXor();
}

/* Analisa e traduz uma expressão booleana */
void BoolExpression()
{
    BoolTerm();
    while (IsOrOp(Token))
    {
        AsmPush();
        switch (Token)
        {
        case '|':
            BoolOr();
            break;
        case '~':
            BoolXor();
            break;
        }
    }
}

/* Analisa e traduz um comando de atribuição */
void Assignment()
{
    char name[MAXTOKEN + 1];

    strcpy(name, TokenText);
    CheckTable(name);
    NextToken();
    MatchString("=");
    BoolExpression();
    AsmStore(name);
}

void Block();

/* Analisa e traduz um comando IF */
void DoIf()
{
    int l1, l2;

    NextToken();
    BoolExpression();
    l1 = NewLabel();
    l2 = l1;
    AsmBranchFalse(l1);
    Block();
    if (Token == 'l')
    {
        NextToken();
        l2 = NewLabel();
        AsmBranch(l2);
        PostLabel(l1);
        Block();
    }
    PostLabel(l2);
    MatchString("ENDIF");
}

/* Analisa e traduz um comando WHILE */
void DoWhile()
{
    int l1, l2;

    NextToken();
    l1 = NewLabel();
    l2 = NewLabel();
    PostLabel(l1);
    BoolExpression();
    AsmBranchFalse(l2);
    Block();
    MatchString("ENDWHILE");
    AsmBranch(l1);
    PostLabel(l2);
}

/* Processa um comando READ */
void DoRead()
{
    NextToken();
    MatchString("(");
    for (;;)
    {
        CheckIdent();
        CheckTable(TokenText);
        AsmRead();
        AsmStore(TokenText);
        NextToken();
        if (Token != ',')
            break;
        NextToken();
    }
    MatchString(")");
}

/* Processa um comando WRITE */
void DoWrite()
{
    NextToken();
    MatchString("(");
    for (;;)
    {
        Expression();
        AsmWrite();
        if (Token != ',')
            break;
        NextToken();
    }
    MatchString(")");
}

/* Analisa e traduz um bloco de comandos estilo "C/Ada" */
void Block()
{
    int follow = 0;

    do
    {
        Scan();
        switch (Token)
        {
        case 'i':
            DoIf();
            break;
        case 'w':
            DoWhile();
            break;
        case 'R':
            DoRead();
            break;
        case 'W':
            DoWrite();
            break;
        case 'x':
            Assignment();
            break;
        case 'e':
        case 'l':
            follow = 1;
            break;
        }
        if (!follow)
            Semicolon();
    } while (!follow);
}

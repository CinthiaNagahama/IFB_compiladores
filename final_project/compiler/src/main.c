#include "../headers/input.h"
#include "../headers/scanner.h"
#include "../headers/parser.h"
#include "../headers/codegen.h"

/* Programa principal */
int main()
{
    Init();

    MatchString("PROGRAM");
    Semicolon();
    AsmHeader();
    TopDeclarations();
    MatchString("BEGIN");
    AsmProlog();
    Block();
    MatchString("END");
    AsmEpilog();

    return 0;
}
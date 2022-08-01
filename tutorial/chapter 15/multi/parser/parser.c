#include <ctype.h>
#include "../multi/utils/input.h"
#include "../multi/utils/errors.h"
#include "../multi/lexer/scanner.h"
#include "../multi/codegen/codegen.h"
#include "parser.h"

/* Analisa e traduz um fator matemático */
void Factor()
{
    char name[MAXNAME + 1], num[MAXNUM + 1];

    if (isdigit(Look))
    {
        GetNum(num);
        AsmLoadConst(num);
    }
    else if (isalpha(Look))
    {
        GetName(name);
        AsmLoadVar(name);
    }
    else
        Error("Unrecognized character: '%c'", Look);
}
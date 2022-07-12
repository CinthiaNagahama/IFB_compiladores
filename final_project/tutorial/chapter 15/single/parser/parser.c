#include <ctype.h>
#include "../single/utils/input.h"
#include "../single/utils/errors.h"
#include "../single/lexer/scanner.h"
#include "../single/codegen/codegen.h"
#include "parser.h"

/* Analisa e traduz um fator matemático */
void Factor()
{
    if (isdigit(Look))
        AsmLoadConst(GetNum());
    else if (isalpha(Look))
        AsmLoadVar(GetName());
    else
        Error("Unrecognized character: '%c'", Look);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/symbolsTable.h"
#include "../headers/errors.h"

char *SymbolTable[SYMBOLTABLE_SIZE]; /* Tabela de símbolos */
char SymbolType[SYMBOLTABLE_SIZE];   /* Tabela de tipos de símbolos */
int SymbolCount;                     /* Número de entradas na tabela de símbolos */

int LabelCount; /* Contador usado pelo gerador de rótulos */
/* Lista de palavras-chave */
char *KeywordList[KEYWORDLIST_SIZE] = {"IF", "ELSE", "ENDIF", "WHILE", "ENDWHILE",
                                       "READ", "WRITE", "VAR", "END"};
/* Códigos de palavras-chave: a ordem deve obedecer a lista de palavras-chave */
char *KeywordCode = "ileweRWve";

char TokenText[MAXTOKEN + 1]; /* Texto do token atual */
char Token;                   /* Código do token atual */

/* Verifica se símbolo está na tabela */
int InTable(char *name)
{
  return (Lookup(name, SymbolTable, SymbolCount) >= 0);
}

/* Se a string de entrada estiver na tabela, devolve a posição ou -1 se não estiver */
int Lookup(char *s, char *list[], int size)
{
  int i;

  for (i = 0; i < size; i++)
  {
    if (strcmp(list[i], s) == 0)
      return i;
  }

  return -1;
}

/* Retorna o endereço do identificador na tabela de símbolos */
int Locate(char *name)
{
  return Lookup(name, SymbolTable, SymbolCount);
}

/* Reporta um erro se identificador NÃO constar na tabela de símbolos */
void CheckTable(char *name)
{
  if (!InTable(name))
    Undefined(name);
}

/* Reporta um erro se identificador JÁ constar na tabela de símbolos */
void CheckDuplicate(char *name)
{
  if (InTable(name))
    Duplicate(name);
}

/* Adiciona uma nova entrada à tabela de símbolos */
void AddEntry(char *name, char type)
{
  char *newSymbol;

  CheckDuplicate(name);

  if (SymbolCount >= SYMBOLTABLE_SIZE)
  {
    Abort("Symbol table full!");
  }

  newSymbol = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  if (newSymbol == NULL)
    Abort("Out of memory!");

  strcpy(newSymbol, name);

  SymbolTable[SymbolCount] = newSymbol;
  SymbolType[SymbolCount] = type;
  SymbolCount++;
}

/* Gera um novo rótulo único */
int NewLabel()
{
  return LabelCount++;
}

/* Emite um rótulo */
void PostLabel(int lbl)
{
  printf("L%d:\n", lbl);
}
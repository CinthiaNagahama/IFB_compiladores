#ifndef _SYMBOLSTABLE_H
#define _SYMBOLSTABLE_H

#define SYMBOLTABLE_SIZE 1000
extern char *SymbolTable[SYMBOLTABLE_SIZE];
extern char SymbolType[SYMBOLTABLE_SIZE];
extern int SymbolCount;

extern int LabelCount;

#define KEYWORDLIST_SIZE 9
/* Lista de palavras-chave */
extern char *KeywordList[KEYWORDLIST_SIZE];
/* Códigos de palavras-chave: a ordem deve obedecer a lista de palavras-chave */
extern char *KeywordCode;

#define MAXTOKEN 16
extern char TokenText[MAXTOKEN + 1];
extern char Token;

int InTable(char *name);
int Lookup(char *s, char *list[], int size);
int Locate(char *name);
void CheckTable(char *name);
void CheckDuplicate(char *name);
void AddEntry(char *name, char type);
int NewLabel();
void PostLabel(int lbl);

#endif
#ifndef _SCANNER1_H
#define _SCANNER1_H

#define MAXNAME 30
#define MAXNUM 5

void Match(char c);
void GetName();
void GetNum();
void GetOp();

void NextToken();
void Scan();
void MatchString(char *s);

int IsAddOp(char c);
int IsMulOp(char c);
int IsOrOp(char c);
int IsRelOp(char c);

#endif
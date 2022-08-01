#ifndef _PARSER_H
#define _PARSER_H

void Declaration();
void Semicolon();
void TopDeclarations();

void BoolExpression();
void Factor();
void Multiply();
void Divide();
void Term();
void Add();
void Subtract();
void Expression();

void Relation();
void NotFactor();
void BoolTerm();
void BoolOr();
void BoolXor();
void BoolExpression();

void Assignment();
void Block();

void DoIf();
void DoWhile();
void DoRead();
void DoWrite();

#endif
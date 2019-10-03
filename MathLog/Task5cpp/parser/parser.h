#ifndef CPP_SOLUTION_PARSER_H
#define CPP_SOLUTION_PARSER_H

#include "expression.h"

using std::string;
using std::cout;
using std::cin;

expr_t parse(string expr);
expr_t var (string expr);
expr_t otricala (string  expr);
expr_t conjunct (string  expr);
expr_t disjunct(string  expr);
expr_t parse(string expr);
expr_t unary(string expr);
expr_t pred(string expr);
expr_t funct(string expr);
expr_t ter(string expr);

#include "parser.cpp"

#endif

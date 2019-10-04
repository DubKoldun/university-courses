#pragma once
#include "../parser/parser.h"
#include <vector>

string destroySpaces2(string const& some1);
expr_t makeNeg(expr_t expr);
expr_t makeAxiom1(expr_t a, expr_t b);
expr_t makeAxiom2(expr_t a, expr_t b, expr_t c);
expr_t makeAxiom9(expr_t a, expr_t b);
std::pair<std::vector<expr_t>, int> alphaImpl(expr_t expression, int);
std::pair<std::vector<expr_t>, int> contrposition(expr_t first, expr_t second, int currentIndex);

#include "addFunctions.cpp"

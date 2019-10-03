#pragma once
#include <vector>

string destroySpaces2(string const& some1);
expr_t makeNeg(expr_t expr);
expr_t makeAxiom1(expr_t a, expr_t b);
expr_t makeAxiom2(expr_t a, expr_t b, expr_t c);
expr_t makeAxiom9(expr_t a, expr_t b);
std::vector<expr_t> alphaImpl(expr_t expression);



#include "addFunctions.cpp"

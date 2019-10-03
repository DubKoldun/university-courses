#ifndef EXPRESSION_UTILS_HPP
#define EXPRESSION_UTILS_HPP

#include <algorithm>
#include <iterator>
#include <optional>

#include "expression.hpp"


std::vector<expr_t> propositionalAxiomSchemes;
std::vector<expr_t> formalArithmeticAxioms;

std::string propositionalAxiomSchemesStrings[] = {
    "(a = a) -> ((b = b) -> (a = a))",
    "((a = a) -> (b = b)) -> ((a = a) -> (b = b) -> (g = g)) -> ((a = a) -> (g = g))",
    "(a = a) -> (b = b) -> (a = a) & (b = b)",
    "(a = a) & (b = b) -> (a = a)",
    "(a = a) & (b = b) -> (b = b)",
    "(a = a) -> (a = a) | (b = b)",
    "(b = b) -> (a = a) | (b = b)",
    "((a = a) -> (g = g)) -> ((b = b) -> (g = g)) -> ((a = a) | (b = b) -> (g = g))",
    "((a = a) -> (b = b)) -> ((a = a) -> !(b = b)) -> !(a = a)",
    "!!(a = a) -> (a = a)"
};

std::string formalArithmeticAxiomsStrings[] = {
    "a = b -> a' = b'",
    "a = b -> a = c -> b = c",
    "a' = b' -> a = b",
    "!a' = 0",
    "a + b' = (a + b)'",
    "a + 0 = a",
    "a * 0 = 0",
    "a * b' = a * b + a"
};

void initialize() {
    std::transform(propositionalAxiomSchemesStrings, propositionalAxiomSchemesStrings + 10, std::back_inserter(propositionalAxiomSchemes), &parse);
    std::transform(formalArithmeticAxiomsStrings, formalArithmeticAxiomsStrings + 8, std::back_inserter(formalArithmeticAxioms), &parse);
}


bool isPropositionalAxiom(expr_t expr) {
    // TODO
}

std::optional<expr_t> whatSubstitues(onst std::string& var, expr_t norm, expr_t modified) {
    // TODO
}

bool isSubstitution(const std::string& var, expr_t norm, expr_t modified) {
    return whatSubstitues(var, norm, modified);
}

bool isPredicateAxiomExists(expr_t expr) {
    if (expr->getType() != "->" || expr->getLeft()->getType() != "@") {
        return false;
    }
    return isSubstitution(expr->getLeft()->getLeft()->prefix_form(), expr->getLeft()->getRight(), expr->getRight());
}

bool isPredicateAxiomForall(expr_t expr) {
    if (expr->getType() != "->" || expr->getRight()->getType() != "?") {
        return false;
    }
    return isSubstitution(expr->getRight()->getLeft()->prefix_form(), expr->getRight()->getRight(), expr->getLeft());
}

bool isPredicateAxiom(expr_t expr) {
    return isPredicateAxiomExists(expr) || isPredicateAxiomForall(expr);
}

bool isFormalArithmeticAxiomScheme(expr_t expr) {
    if (!(expr->getType() == "->" && expr->getLeft()->getType() == "&" && expr->getLeft()->getRight()->getType() == "@" && expr->getLeft()->getRight()->getRight()->getType() == "->")) {
        return false;
    }

    if (!equals(expr->getLeft()->getRight()->getRight()->getLeft(), expr->getRight()) {
        return false;
    }


    auto var = expr->getLeft()->getRight()->getLeft()->prefix_form();
    auto left = expr->getLeft()->getRight()->getRight()->getLeft();
    auto s1 = whatSubstitues(var, left, expr->getLeft()->getRight()->getRight()->getRight());
    if (!s1 || !equals(*s1, colon(var))) { // TODO not sure about "colon(var)"
        return false;
    }

    auto s2 = whatSubstitues(var, left, expr->getLeft()->getLeft());
    return s2 && equals(*s2, zero()); // TODO not sure about "zero()"
}

bool isFormalArithmeticAxiom(expr_t expr) {
    if (isFormalArithmeticAxiomScheme(expr)) {
        return true;
    }

    // TODO
}

bool isAxiom(expr_t expr) {
    return isPropositionalAxiom(expr) || isPredicateAxiom(expr) || isFormalArithmeticAxiom(expr);
}

bool isClosed(const std::string& variable, expr_t expr) {
    // TODO
}

#endif /* end of include guard: EXPRESSION_UTILS_HPP */

#include <string>
#include "proof.hpp"
#include "parser/expression.hpp"
#include "expression-utils.hpp"

void proof::add(expr_t expr) {
    obtained |= equals(expr, conclusion);
    indices.emplace(expr, ++size);

    if (expr->getType() == "->") {
        modusPonens[expr->getRight()].emplace_back(expr->getLeft(), size);
    }
}

bool proof::isHypothesis(expr_t expr) const {
    return hypotheses.find(expr) != hypotheses.end();
}

bool proof::isModusPonens(expr_t expr) const {
    auto iter = modusPonens.find(expr);
    if (iter == modusPonens.end()) {
        return false;
    }

    for (auto [ex, index] : *iter) {
        if (indices.find(ex) != indices.end()) {
            return true;
        }
    }
    return false;
}

bool proof::checkQuantifierDerived(const std::string& variable, expr_t check, expr_t left, expr_t right) const {
    return isClosed(variable, check) && indices.find(implication(left, right)) != indices.end();
}

bool proof::isDerivedExists(expr_t expr) const {
    if (expr->getType() != "->" || expr->getLeft()->getType() != "?") {
        return false;
    }
    return checkQuantifierDerived(expr->getLeft()->getLeft()->prefix_form(), expr->getRight(), expr->getLeft()->getRight(), expr->getRight());
}

bool proof::isDerivedForall(expr_t expr) const {
    if (expr->getType() != "->" || expr->getRight()->getType() != "@") {
        return false;
    }
    return checkQuantifierDerived(expr->getLeft()->getLeft()->prefix_form(), expr->getLeft(), expr->getLeft(), expr->getRight()->getRight());
}

void proof::append(expr_t expr) {
    if (isHypothesis(expr) || isModusPonens(expr) || isDerivedExists(exr) || isDerivedForall(expr) || isAxiom(expr)) {
        add(expr);
        return;
    }

    throw proof_exception("Line #" + std::to_string(size + 1) + " can't be obtained");
}

bool proof::correct() const {
    return obtained;
}

#ifndef PROOF_HPP
#define PROOF_HPP

#include <unordered_set>
#include <unordered_map>
#include <list>
#include <exception>

#include "../parser/expression.h"
#include "utils.hpp"

class proof_exception : public std::exception {

};

class proof {
public:
    proof(std::vector<expr_t> hypotheses, expr_t result) :
        hypotheses(hypotheses.cbegin(), hypotheses.cend()),
        conclusion(result) {}

    void append(expr_t expr);
    bool correct() const;


private:
    void add(expr_t expr);
    bool isHypothesis(expr_t expr) const;
    bool isModusPonens(expr_t expr) const;
    bool isDerivedExists(expr_t expr) const;
    bool isDerivedForall(expr_t expr) const;
    bool checkQuantifierDerived(const std::string& variable, expr_t check, expr_t left, expr_t right) const;

    const std::unordered_set<expr_t, StringHasher, EqualChecker> hypotheses;
    const expr_t conclusion;
    bool obtained = false;
    std::unordered_map<expr_t, size_t, StringHasher, EqualChecker> indices;
    std::unordered_map<expr_t, std::list<std::pair<expr_t, size_t>>, StringHasher, EqualChecker> modusPonens;
    size_t size = 0;
};

#endif /* end of include guard: PROOF_HPP */

#ifndef PROOF_HPP
#define PROOF_HPP

#include <set>
#include <map>
#include <list>
#include <exception>

#include "expression.hpp"

class proof_exception : public std::exception {

};

class proof {
public:
    proof(/* wtf ? */ hypotheses, expr_t result) : // TODO
        hypotheses(hypotheses.cbegin(), hypotheses.cend()),
        conclusion(result) {}

    void append(expr_t expr);
    bool correct() const;


private:
    void add(expr_t expr);
    bool isHypothesis(expr_t expr) const;
    bool isModusPonens(exprt_t expr) const;
    bool isDerivedExists(expr_t expr) const;
    bool isDerivedForall(expr_t expr) const;
    bool checkQuantifierDerived(const std::string& variable, expr_t check, expr_t left, expr_t right) const;

    const std::set<expr_t> hypotheses; // or whatever container u use (hashset or ...)
    const expr_t conclusion;
    bool obtained = false;
    std::map<expt_t, size_t> indices; // or whatever container u use (hashmap or ...)
    std::map<expr_t, std::list<std::pair<expr_t, size_t>>> modusPonens; // or whatever container u use (hashmap or ...)
    size_t size = 0;
};

#endif /* end of include guard: PROOF_HPP */

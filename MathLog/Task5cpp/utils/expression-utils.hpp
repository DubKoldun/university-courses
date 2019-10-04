#ifndef EXPRESSION_UTILS_HPP
#define EXPRESSION_UTILS_HPP

#include <algorithm>
#include <iterator>
#include <optional>
#include <unordered_set>
#include <unordered_map>

#include "../parser/expression.h"
#include "../parser/parser.h"
#include "utils.hpp"

using semap = std::unordered_map<std::string, expr_t, StringHasher, EqualChecker>;

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
    std::transform(propositionalAxiomSchemesStrings, propositionalAxiomSchemesStrings + 10,
        std::back_inserter(propositionalAxiomSchemes), &parse);
    std::transform(formalArithmeticAxiomsStrings, formalArithmeticAxiomsStrings + 8,
        std::back_inserter(formalArithmeticAxioms), &parse);
}

std::optional<semap> isPropositionalAxiomExact(expr_t ex, expr_t ax) {
    if (ax->getType() == "=") {
        semap m;
        m[ax->getLeft()->getStr()] = ex;
        return std::make_optional(m);
    }

    if (ex->getType() != ax->getType()) {
        return std::nullopt;
    }

    switch (ex->getType()[0]) {
        case '-':
        case '&':
        case '|':
        case '=':
        case '+':
        case '*': {
            auto left = isPropositionalAxiomExact(ex->getLeft(), ax->getLeft());
            if (!left) {
                return std::nullopt;
            }
            auto right = isPropositionalAxiomExact(ex->getRight(), ax->getRight());
            if (!right) {
                return std::nullopt;
            }
            for (auto [key, value] : left.value()) {
                if (right.value().find(key) != right.value().end() && right.value()[key] != value) {
                    return std::nullopt;
                }
            }
            return left->merge(right.value());
        }
        case '!':
            return isPropositionalAxiomExact(ex->getLeft(), ax->getLeft());
        case '@':
        case '?':
        case '0':
        case 'f':
        case 'p':
        case 'v':
        case '\'':
            return std::nullopt;
    }
}

bool isPropositionalAxiom(expr_t expr) {
    return std::any_of(propositionalAxiomSchemes.cbegin(), propositionalAxiomSchemes.cend(),
        [expr] (expr_t ax) { return isPropositionalAxiomExact(expr, ax); });
}

std::unordered_set<std::string> getOpened(expr_t e, std::unordered_set<std::string> s) {
    switch (e->getType()[0]) {
        case '+':
        case '*':
            return getOpened(e->getLeft(), s).merge(getOpened(e->getRight(), s));
        case '\'':
            return getOpened(e->getRight(), s);
        case 'f': {
            std::unordered_set<string> result;
            for (auto t : terms[e->getIndex()]) {
                result.merge(getOpened(t, s));
            }
            return result;
        }
        case '0':
            return std::unordered_set<std::string>();
        case 'v': {
            if (s.find(e->getStr()) != s.end()) {
                return std::unordered_set<std::string>();
            }
            std::unordered_set<std::string> s;
            s.insert(e->getStr());
            return s;
        }
    }
}

bool checkFreeSubstitution(const std::unordered_set<std::string>& s, expr_t ch) {
    std::vector<std::string> diff;
    auto opened = getOpened(ch, std::unordered_set<std::string>());
    std::set_difference(s.cbegin(), s.cend(), opened.begin(), opened.end(),
                        std::inserter(diff, diff.begin()));
    return diff.size() == 0;
}

std::optional<semap> whatSubstituesHelp(const std::string& var, expr_t norm, expr_t modified, std::unordered_set<std::string> s = std::unordered_set<std::string>()) {
    if (norm->getType() == "variable" && norm->getStr() == var && checkFreeSubstitution(s, modified)) {

        semap m;
        m.emplace(var, modified);
        return std::make_optional(m);
    }

    if (norm->getType() != modified->getType()) {
        return std::nullopt;
    }

    switch (norm->getType()[0]) {
        case '+':
        case '=':
        case '*': {

            auto m1 = whatSubstituesHelp(var, norm->getLeft(), modified->getLeft(), s);
            if (!m1) {
                return std::nullopt;
            }
            auto m2 = whatSubstituesHelp(var, norm->getRight(), modified->getRight(), s);
            if (!m2) {
                return std::nullopt;
            }
            return m1->merge(m2.value());
        }
        case '@':
        case '?': {

            if (norm->getLeft()->getStr() == var) {
                return std::make_optional(semap());
            }
            auto s1 = s;
            s1.insert(norm->getLeft()->getStr());
            return whatSubstituesHelp(var, norm->getRight(), modified->getRight(), s1);
        }
        case '0':
        case 'v':
            return std::make_optional(semap());

        case 'p':
        case 'f':
        {

            if (norm->getRight()->getStr() != modified->getRight()->getStr()) {
                return std::nullopt;
            }
            if (terms[norm->getIndex()].size() != terms[modified->getIndex()].size()) {
                return std::nullopt;
            }
            std::vector<expr_t> res;
            auto v1 = terms[norm->getIndex()];
            auto v2 = terms[modified->getIndex()];


            for (size_t i = 0; i < v1.size(); ++i) {
                if (v1[i]->getType() == "variable" && v1[i]->getStr() == var && checkFreeSubstitution(s, v2[i])) {
                    res.push_back(v2[i]);
                    continue;
                }
                if (v1[i]->getType() == "variable" && v1[i]->getStr() == var) {
                    return std::nullopt;
                }
            }
            if (res.empty()) {
                return std::make_optional(semap());
            }
            expr_t eee = res[0];
            for (size_t i = 1; i < res.size(); ++i) {
                if (res[i] != eee) {
                    return std::nullopt;
                }
            }
            semap m;
            m.emplace(var, eee);
            return make_optional(m);
        }

        case '\'':
            return whatSubstituesHelp(var, norm->getRight(), modified->getRight(), s);



        case '-':
        case '&':
        case '|': {

            auto lef = whatSubstituesHelp(var, norm->getLeft(), modified->getLeft(), s);
            auto rig = whatSubstituesHelp(var, norm->getRight(), modified->getRight(), s);
            if (!lef || !rig) {
                return std::nullopt;
            }
            for (auto [k, v] : lef.value()) {
                if (rig.value().find(k) != rig.value().end() && rig.value()[k] != v) {
                    return std::nullopt;
                }
            }
            return lef->merge(rig.value());
        }

        case '!':
            return whatSubstituesHelp(var, norm->getLeft(), modified->getLeft(), s);

    }
}
std::optional<expr_t> whatSubstitues(const std::string& var, expr_t norm, expr_t modified) {
    auto m = whatSubstitues(var, norm, modified);
    if (!m || m->size() != 1) {
        return std::nullopt;
    }

    return std::make_optional(m.value().begin()->second);
}

bool isSubstitution(const std::string& var, expr_t norm, expr_t modified) {
    return whatSubstitues(var, norm, modified);
}

bool isPredicateAxiomExists(expr_t expr) {
    if (expr->getType() != "->" || expr->getLeft()->getType() != "@") {
        return false;
    }
    return isSubstitution(expr->getLeft()->getLeft()->getStr(), expr->getLeft()->getRight(), expr->getRight());
}

bool isPredicateAxiomForall(expr_t expr) {
    if (expr->getType() != "->" || expr->getRight()->getType() != "?") {
        return false;
    }
    return isSubstitution(expr->getRight()->getLeft()->getStr(), expr->getRight()->getRight(), expr->getLeft());
}

bool isPredicateAxiom(expr_t expr) {
    return isPredicateAxiomExists(expr) || isPredicateAxiomForall(expr);
}

bool isFormalArithmeticAxiomScheme(expr_t expr) {
    if (!(expr->getType() == "->" && expr->getLeft()->getType() == "&" &&
            expr->getLeft()->getRight()->getType() == "@" && expr->getLeft()->getRight()->getRight()->getType() == "->")) {
        return false;
    }

    if (!equals(expr->getLeft()->getRight()->getRight()->getLeft(), expr->getRight()) {
        return false;
    }


    auto var = expr->getLeft()->getRight()->getLeft()->getStr();
    auto left = expr->getLeft()->getRight()->getRight()->getLeft();
    auto s1 = whatSubstitues(var, left, expr->getLeft()->getRight()->getRight()->getRight());
    if (!s1 || !equals(*s1, std::make_shared<multiply>(std::make_shared<variable>(var), "1"))) {
        return false;
    }

    auto s2 = whatSubstitues(var, left, expr->getLeft()->getLeft());
    return s2 && equals(*s2,  std::make_shared<multiply>(nullptr, nullptr, "0"));
}

std::optional<semap> isFormalArithmeticAxiomExact(expr_t ex, expr_t ax) {
    if (ex->getType() != ax->getType()) {
        return std::nullopt;
    }

    switch (expr->getType()[0]) {
        case '-':
        case '&':
        case '|':
        case '=':
        case '+':
        case '*': {

            auto left = isFormalArithmeticAxiomExact(ex->getLeft(), ax->getLeft());
            if (!left) {
                return std::nullopt;
            }
            auto right = isFormalArithmeticAxiomExact(ex->getRight(), ax->getRight());
            if (!right) {
                return std::nullopt;
            }
            for (auto [key, value] : left.value()) {
                if (right.value().find(key) != right.value().end() && right.value()[key] != value) {
                    return std::nullopt;
                }
            }
            return left->merge(right.value());
        }
        case '!':
            return isFormalArithmeticAxiomExact(ex->getLeft(), ax->getLeft());
        case '@':
        case '?':
        case '0':
            return std::make_optional(semap());
        case 'f':
        case 'p':
        case 'v': {

            semap m;
            m.emplace(ax->getStr(), ex);
            return std::make_optional(m);
        }
        case '\'':
            return isFormalArithmeticAxiomExact(ex->getRight(), ax->getRight());
    }
}

bool isFormalArithmeticAxiom(expr_t expr) {
    if (isFormalArithmeticAxiomScheme(expr)) {
        return true;
    }

    return std::any_of(formalArithmeticAxioms.cbegin(), formalArithmeticAxioms.cend(),
        [] (expr_t ax) { return isFormalArithmeticAxiomExact(expr, ax); });
}

bool isAxiom(expr_t expr) {
    return isPropositionalAxiom(expr) || isPredicateAxiom(expr) || isFormalArithmeticAxiom(expr);
}

bool isClosed(const std::string& variable, expr_t expr) {
    switch (expr->getType()[0]) {
        case '-':
        case '&':
        case '|':
        case '=':
        case '+':
        case '*':
            return isClosed(variable, expr->getRight()) && isClosed(variable, expr->getLeft());
        case '@':
        case '?':
            return expr->getLeft()->getStr() == variable || isClosed(variable, expr->getRight());
        case '0':
            return true;
        case '\'':
            return isClosed(variable, expr->getRight());
        case 'f':
        case 'p': {

            const auto v = terms[expr->getIndex()];
            return std::all_of(v.cbegin(), v.cend(),
            [variable] (term t) { return isClosed(variable, t->getLeft()) && isClosed(variable, t->getRght()); });
        }
        case 'v':
            return expr->getStr() != variable;
        case '!':
            return isClosed(variable, expr->getLeft());
    }
}

#endif /* end of include guard: EXPRESSION_UTILS_HPP */

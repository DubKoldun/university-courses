#include <unordered_map>
#include <memory>
#include "../expression.h"

using std::unordered_map;

struct StringHasher {
    size_t operator()(expr_t expr) const {
          return std::hash<std::string>()(expr.get()->prefix_form());
    }
};

struct EqualChecker {
    bool operator()(expr_t expr1, expr_t expr2) const {
        return equals(expr1, expr2);
    }
};

unordered_map <expr_t, int, StringHasher, EqualChecker> hypothesises;

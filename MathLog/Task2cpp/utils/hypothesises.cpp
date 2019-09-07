#include <unordered_map>
#include "../expression.h"

using std::unordered_map;

struct StringHasher {
    size_t operator()(expression * expr) const {
          return std::hash<std::string>()(expr->prefix_form());
    }
};

struct EqualChecker {
    bool operator()(expression * expr1, expression * expr2) const {
        return *expr1 == expr2;
    }
};

unordered_map <expression* , size_t, StringHasher, EqualChecker> hypothesises;

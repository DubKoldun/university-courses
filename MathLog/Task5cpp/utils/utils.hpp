#ifndef UTILS_HPP
#define UTILS_HPP

struct StringHasher {
    size_t operator()(expr_t expr) const {
          return std::hash<std::string>()(expr.get()->getStr());
    }
};

struct EqualChecker {
    bool operator()(expr_t expr1, expr_t expr2) const {
        return equals(expr1, expr2);
    }
};

#endif /* end of include guard: UTILS_HPP */

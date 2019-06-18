//
// #include <unordered_map>
// #include "../expression.h"
//
// using std::unordered_map;
//
// struct StringHasher {
//     size_t operator()(std::shared_ptr<expression> expr) const {
//           return std::hash<std::string>()(expr->prefix_form());
//     }
// };
//
// struct EqualChecker {
//     bool operator()(std::shared_ptr<expression> expr1, std::shared_ptr<expression> expr2) const {
//         return *(expr1.get()) == expr2.get();
//     }
// };
//
// unordered_map <std::shared_ptr<expression>, size_t, StringHasher, EqualChecker> hypothesises;

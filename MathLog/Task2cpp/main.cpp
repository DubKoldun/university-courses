#include <iostream>
#include "expression.h"
#include "utils/features.cpp"
#include "utils/axiom.cpp"


int main() {
    unordered_map <expression*, size_t, StringHasher, EqualChecker> proofs;

    readFirstLine();
    size_t i = 1;

    for (string str; readLine(str); ++i) {
        expression* expr = makeExpression(str);
        // auto expr = std::make_shared<expression>(makeExpression(str));

//        cout << expr->prefix_form() << "\n";

        int buff = axiomNumber(expr);

        if(buff) {
            expr->val = {buff, -1, "Ax. sch. "};
            proofs.emplace(expr, i);
            continue;
        }

        auto it = hypothesises.find(expr);
        buff = (it != hypothesises.end()) ? it->second : 0;

        if(buff) {
            expr->val = {buff, 0, "Hypothesis "};
            proofs.emplace(expr, i);
            continue;
        }


    }

    return 0;
}

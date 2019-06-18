#include <iostream>
#include "expression.h"
#include <memory>
#include "utils/features.cpp"
#include "utils/axiom.cpp"

#include "parser/expression.tab.h"
#include "parser/expression.lexer.h"

extern expression* result;

void yyerror(const char *error) {
    std::cerr << error;
}

int yywrap() {
    return 1;
}


int main() {
    // unordered_map <std::shared_ptr<expression>, size_t, StringHasher, EqualChecker> proofs;

    // readFirstLine();
    size_t i = 1;
    // const char* express = "A->A";
    yy_scan_string("A->A");
    yyparse(); // huinya
    // std::cout << result-> prefix_form() << "\n";
    delete result;

    // for (std::string str; readLine(str); ++i) {

        // std::shared_ptr<expression> expr(makeExpression(str));

        // cout << expr->prefix_form() << "\n";
        //
        // int buff = axiomNumber(expr.get());
        //
        // if(buff) {
        //     expr->val = {buff, -1, "Ax. sch. "};
        //     proofs.emplace(expr, i);
        //     continue;
        // }
        //
        // auto it = hypothesises.find(expr);
        // buff = (it != hypothesises.end()) ? it->second : 0;
        //
        // if(buff) {
        //     expr->val = {buff, 0, "Hypothesis "};
        //     proofs.emplace(expr, i);
        //     continue;
        // }


    // }

    return 0;
}

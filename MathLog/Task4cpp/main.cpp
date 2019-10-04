#include <algorithm>
#include <iostream>
#include <sstream>
#include <list>
#include "parser/parser.h"
#include "hypothesisesAndAxiom/axiom.h"
#include "utils/addFunctions.h"
#include "utils/features.cpp"
#include "deduction/deductor.cpp"

using std::list;


int main() {
    
    return 0;
}


// A|-B->A check deduction
// A->B->A
// A
// B->A

// int main() {
//     std::vector<expr_t> checker;
//     expr_t a = parse("A");
//     expr_t ba = parse("B->A");
//     expr_t aba = parse("A->B->A");
//     aba->val = {1,-1,"Ax"};
//     checker.push_back(aba);
//     expr_t a_ = parse("A");
//     a_->val = {1,0,"Ax"};
//     checker.push_back(a);
//     expr_t ba_ = parse("B->A");
//     ba_->val = {1,0,"MP"};
//     checker.push_back(ba_);
//     std::vector<expr_t> v(deduction(checker, a, ba));
//     for (auto i : v) {
//         std::cout << i->prefix_form() << "\n";
//     }
//     return 0;
// }

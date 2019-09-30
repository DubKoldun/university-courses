#include <algorithm>
#include <iostream>
#include <sstream>
#include <list>
#include "parser/parser.h"
#include "hypothesisesAndAxiom/axiom.h"
#include "utils/addFunctions.cpp"
#include "utils/features.cpp"
#include "utils/hardcode.cpp"

using std::list;

int main() {
    string currentLine;
    int i = 1;

    unordered_map <expr_t, int, StringHasher, EqualChecker> provesMap;
    unordered_map <expr_t, list <std::pair<expr_t, int>>, StringHasher, EqualChecker> modusMap;

    readFirstLine();
    string s = hypotForAns.substr(0, hypotForAns.size()-2);
    if (!hypothesises.empty()) s += " ";
    cout << s << "|- !!" << parse(statement)->prefix_form() << "\n";

    while (readLine(currentLine)) {
        expr_t currentExpression(parse(currentLine));

        if (currentExpression->getType() == "->") {
            expr_t right = currentExpression->getRight();
            auto currentMP = modusMap.find(right);
            if (currentMP != modusMap.end()) {
                currentMP->second.emplace_back(currentExpression, i);
            } else {
                modusMap.emplace(right, list<std::pair<expr_t, int>>{{currentExpression, i}});
            }
        }

        int currentState = axiomNumber(currentExpression);
        if (currentState) {
            currentExpression->val = {currentState, -1, 1, "Ax. sch."};
            provesMap.insert({currentExpression, i++});
            if (currentState == 10) {
                ax10(currentExpression->getRight());
            } else {
                hypAndClassAx(currentExpression);
            }
            continue;
        }

        currentState = checkHypothesis(currentExpression);
        if (currentState) {
            currentExpression->val = {currentState, 0, 1, "Hypothesis"};
            provesMap.insert({currentExpression, i++});
            hypAndClassAx(currentExpression);
            continue;
        }


        auto buff = modusMap.find(currentExpression);
        if (buff != modusMap.end()) {
            int min = INF;
            for (auto j: buff->second) {
                auto full = provesMap.find(j.first);
                auto left = provesMap.find(full->first->getLeft());
                if (left != provesMap.end()) {
                    min = std::min(min, left->first->val.depth + full->first->val.depth + 1);
                    currentExpression->val = {j.second, left->second, min, "M.P."};
                }
            }
            unordered_map<int,expr_t> buff2 = reverseMap(provesMap);
            provesMap.insert({currentExpression, i++});
            modusPonens(buff2.find(currentExpression->val.b)->second, currentExpression);

            continue;
        }

        cout << "Proof is incorrect";
        return 0;
    }



    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include "utils/features.cpp"
#include "utils/axiom.cpp"

using std::vector;
using std::list;

int main() {
    readFirstLine();

    string currentLine;
    int i = 0;

    expr_t lastExpression;

    unordered_map <expr_t, int, StringHasher, EqualChecker> provesMap;
    unordered_map <expr_t, list <std::pair<expr_t, int>>, StringHasher, EqualChecker> modusMap;

    while (readLine(currentLine)) {
        expr_t currentExpression(parse(currentLine));
        lastExpression = currentExpression;
        provesMap.insert({currentExpression, ++i});

        if (currentExpression->getType() == "->") {
            expr_t right = currentExpression->getRight(), left = currentExpression->getLeft();
            auto currentMP = modusMap.find(right);
            if (currentMP != modusMap.end()) {
                currentMP->second.emplace_back(left, i);
            } else {
                modusMap.emplace(right, list<std::pair<expr_t, int>>{{left, i}});
            }
        }

        int currentState = axiomNumber(currentExpression);
        if (currentState) {
            currentExpression->val = {currentState, -1, "Ax. sch."};
            continue;
        }

        currentState = checkHypothesis(currentExpression);
        if (currentState) {
            currentExpression->val = {currentState, 0, "Hypothesis"};
            continue;
        }

        auto buff = modusMap.find(currentExpression);
        if (buff != modusMap.end()) {

            bool flag = false;
            for (auto i: buff->second) {
                auto left = provesMap.find(i.first);
                if (left != provesMap.end()) {
                    currentExpression->val = {i.second, left->second, "M.P."};
                    flag = true;
                    break;
                }
            }

            if (!flag) {
                cout << "Proof is incorrect";
                return 0;
            }
            continue;
        }

        cout << "Proof is incorrect";
        return 0;
    }

    expr_t exprStatement = parse(statement);

    if (!equals(lastExpression, exprStatement)) {
        cout << "Proof is incorrect";
        return 0;
    }

    vector<std::pair<expr_t,int>> answer;
    for (auto i: provesMap) {
        answer.emplace_back(std::pair<expr_t,int>({i.first,i.second}));
    }
    sort(answer.begin(), answer.end(), ComparePairs());

    for (auto i: answer) {
        cout << i.second;
    }



    return 0;
}

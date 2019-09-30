#include <algorithm>
#include <iostream>
#include <sstream>
#include <list>
#include "utils/task2Utils.cpp"
#include "utils/axiom.cpp"

using std::list;

int main() {
    readFirstLine();

    string currentLine;
    int i = 1;

    expr_t lastExpression;

    unordered_map <expr_t, int, StringHasher, EqualChecker> provesMap;
    unordered_map <expr_t, list <std::pair<expr_t, int>>, StringHasher, EqualChecker> modusMap;

    while (readLine(currentLine)) {
        expr_t currentExpression(parse(currentLine));
        // cout << i << "D : " << currentExpression->prefix_form() <<  "\n";
        lastExpression = currentExpression;
        if (provesMap.find(currentExpression) != provesMap.end()) {
            lastExpression = provesMap.find(currentExpression)->first;
            continue;
        }

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
            // cout << 1 << "ax\n";
            currentExpression->val = {currentState, -1, 1, "Ax. sch."};
            provesMap.insert({currentExpression, i++});
            continue;
        }

        currentState = checkHypothesis(currentExpression);
        if (currentState) {
            currentExpression->val = {currentState, 0, 1, "Hypothesis"};
            provesMap.insert({currentExpression, i++});
            continue;
        }

        // for (auto j: modusMap) {
        //     cout << j.first->prefix_form();
        // }

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

            if (min == INF) {
                cout << "Proof is incorrect";
                return 0;
            }
            provesMap.insert({currentExpression, i++});

            continue;
        }

        cout << "Proof is incorrect";
        return 0;
    }

    if (!equals(lastExpression, parse(statement))) {
        cout << "Proof is incorrect";
        return 0;
    }

    vector<std::pair<expr_t,int>> answer;

    recovery(reverseMap(provesMap), provesMap, lastExpression, answer);

    sort(answer.begin(), answer.end(), ComparePairs());

    std::vector<std::pair<expr_t, int>>::iterator it;
    it = std::unique (answer.begin(), answer.end(), [](std::pair<expr_t, int>  a, std::pair<expr_t, int>  b) { return equals(a.first, b.first);});
    answer.resize( std::distance(answer.begin(),it) );

    string s = hypotForAns.substr(0, hypotForAns.size()-2);
    if (!hypothesises.empty()) s += " ";
    cout << s << "|- " << parse(statement)->prefix_form() << "\n";


    unordered_map <int, int> connections;
    int currentIndex = 1, oldIndex = 0;
    for (auto i: answer) {
        oldIndex = i.second;
        expr_t expr = i.first;
        switch (expr->val.b) {
            case (-1): {
                connections.emplace(oldIndex, currentIndex);
                cout << "[" + std::to_string(currentIndex) + ". " + expr->val.value + " " + std::to_string(expr->val.a) + "] ";
                cout << expr->prefix_form() << "\n";
                ++currentIndex;
                break;
            }
            case (0): {
                connections.emplace(oldIndex, currentIndex);
                cout << "[" + std::to_string(currentIndex) + ". " + expr->val.value + " " + std::to_string(expr->val.a) + "] ";
                cout << expr->prefix_form() << "\n";
                ++currentIndex;
                break;
            }
            default: {
                int a = i.first->val.a, b = i.first->val.b;
                cout << "[" << currentIndex << ". " << expr->val.value << " " << (connections.find(a)->second) << ", " << (connections.find(b)->second) << "] ";
                cout << expr->prefix_form() << "\n";
                connections.emplace(oldIndex, currentIndex);
                ++currentIndex;
                break;
            }

        }
    }

    return 0;
}

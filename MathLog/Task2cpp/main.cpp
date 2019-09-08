#include <iostream>
#include <memory>
#include <algorithm>
#include "utils/features.cpp"
#include "utils/axiom.cpp"

//need algo

int main() {
    readFirstLine();
    string currentLine;
    size_t i = 0;

    unordered_map <expression*, size_t, StringHasher, EqualChecker> provesMap;
    unordered_map <expression*, std::set<mp, Compare>, StringHasher, EqualChecker> modusMap;

    while (readLine(currentLine)) {
        ++i;
        expression * currentExpression = parse(currentLine);

        int axiom = axiomNumber(currentExpression);
        if (axiom) {
            currentExpression->val = {-1, axiom, "Ax. sch. "};
            provesMap.emplace(currentExpression, i);

            if (currentExpression->getType() == "->") { //&& provesMap.find(currentExpression->getLeft()) != provesMap.end()) {
                expression* r = currentExpression->getRight();
                auto search = modusMap.find(r);

                if (search == modusMap.end()) {
                    modusMap.emplace(r, std::set<mp, Compare>{{currentExpression}});
                } else {
                    search->second.insert({currentExpression}); // after all need to check on a left part
                }
            }
            continue;
        }

        int hypothesis = hypothesises.find(currentExpression)->second;
        if (hypothesis) {
            currentExpression->val = {0, hypothesis, "Hypothesis "};
            provesMap.emplace(currentExpression, i);

            if (currentExpression->getType() == "->") { //&& provesMap.find(currentExpression->getLeft()) != provesMap.end()) {
                expression* r = currentExpression->getRight();
                auto search = modusMap.find(r);

                if (search == modusMap.end()) {
                    modusMap.emplace(r, std::set<mp, Compare>{{currentExpression}});
                } else {
                    search->second.insert({currentExpression}); // after all need to check on a left part
                }
            }
            continue;
        }
        
        auto search = modusMap.find(currentExpression);
        if (search != modusMap.end()) {
            int minValue = INF;
            for (auto ss: search->second) {
                auto left = ss.general->getLeft();

                if(provesMap.find(left) != provesMap.end()) {
                    switch (left->val.b) {
                        case (-1): {
                            minValue = std::min(1,minValue);
                            break;
                        }
                        case (0): {
                            minValue = std::min(1,minValue);
                            break;
                        }
                        default: {
                            auto search2 = modusMap.find(left);
                            minValue = std::min(search2->second.begin()->size + 1, minValue);
                        }
                    }
                    ss.size = minValue;
                }
            }

            auto var = search->second.begin();

            if(var->size != INF) {
                search->first->val = {provesMap.find(var->general)->second, provesMap.find(var->general->getLeft())->second, "M. P. "};
            }
            break;
        }
        delete currentExpression;

        cout << "Proof is incorrect\n";
        return 0;

    }

    // for (auto i : provesMap) cout << "Debug: " << i.first->val.a << " " << i.first->val.b << " " << i.second;

    return 0;
}

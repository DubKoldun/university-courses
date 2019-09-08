#include <iostream>
#include <memory>
#include "utils/features.cpp"
#include "utils/axiom.cpp"

//need algo

struct mp {
    expression* general;
    size_t size = INF;


};

int main() {
    readFirstLine();
    string currentLine;
    size_t i = 0;

    unordered_map <expression*, size_t, StringHasher, EqualChecker> provesMap;
    unordered_map <expression*, std::vector<mp>, StringHasher, EqualChecker> modusMap;

    while (readLine(currentLine)) {
        ++i;
        expression * currentExpression = parse(currentLine);

        int axiom = axiomNumber(currentExpression);
        if (axiom) {
            currentExpression->val = {-1, axiom, "Ax. sch. "};
            provesMap.emplace(currentExpression, i);
            if (currentExpression.getType() == "->") { //&& provesMap.find(currentExpression->getLeft()) != provesMap.end()) {
                expression* r = currentExpression->getRight();
                auto * search = modusMap.find(r);
                if (search == modusMap.end()) {
                    modusMap.emplace(r, std::set<mp, Compare>({currentExpression}));
                } else {
                    search->second.emplace({currentExpression}); // after all need to check on a left part
                }
            }
            continue;
        }

        int hypothesis = hypothesises.find(currentExpression)->second;
        if (hypothesis) {
            currentExpression->val = {0, hypothesis, "Hypothesis "};
            provesMap.emplace(currentExpression, i);
            if (currentExpression.getType() == "->") { //&& provesMap.find(currentExpression->getLeft()) != provesMap.end()) {
                expression* r = currentExpression->getRight();
                auto search = modusMap.find(r);
                if (search == modusMap.end()) {
                    modusMap.emplace(r, std::set<mp, Compare>({currentExpression}));
                } else {
                    search->second.emplace({currentExpression}); // after all need to check on a left part
                }
            }
            continue;
        }

        auto search = modusMap.find(currentExpression);
        if (search != modusMap.end()) {
            size_t minValue = INF;
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
                            minValue = std::min(modusMap.find(left).begin()->second.size + 1, minValue);
                        }
                    }
                    ss.size = minValue;
                }
            }

            auto var = search.begin()->second;

            if(var.size != INF) {
                search->first.val = {provesMap.find(var.general).second, provesMap.find(var.general->getLeft()).second, "M. P. "};
            }
        } 

        cout << "Proof is incorrect\n";
        return 0;

    }

    for (auto i : provesMap) cout << "Debug: " << i.first->val.a << " " << i.first->val.b << " " << i.second;

    return 0;
}

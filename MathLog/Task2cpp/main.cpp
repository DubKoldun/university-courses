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
    expression* lastLine;


    unordered_map <expression*, size_t, StringHasher, EqualChecker> provesMap;
    unordered_map <expression*, std::set<mp, Compare>, StringHasher, EqualChecker> modusMap;

    while (readLine(currentLine)) {
        ++i;
        expression * currentExpression = parse(currentLine);
        lastLine = currentExpression;

        int axiom = axiomNumber(currentExpression);
        if (axiom) {
            currentExpression->val = {axiom, -1, "Ax. sch. "};
            provesMap.emplace(currentExpression, i);

            if (currentExpression->getType() == "->") { //&& provesMap.find(currentExpression->getLeft()) != provesMap.end()) {
                expression* r = currentExpression->getRight();
                auto search = modusMap.find(r);

                if (search == modusMap.end()) {
                    modusMap.emplace(r, std::set<mp, Compare>{{currentExpression}});
                } else {
                    search->second.insert({currentExpression}); // after all need to check on a left part
                }
                // delete r;
            }


                // for (auto i: provesMap){
                //      cout << "Debug PM: " << i.first->prefix_form() << " " << i.first->val.a << " " << i.first->val.b << " " << i.second << "\n";
                //      // delete i.first;
                // }
                // for (auto i: modusMap) {
                //     cout << "Debug MP: " << i.first->prefix_form() << " " << i.first->val.a << " " << i.first->val.b << "\n modusMap[i].second contains: \n";
                //     // delete i.first;
                //     for (auto ss: i.second) {
                //         cout << ss.general->prefix_form() << " ";
                //     } cout << "\n";
                // }

            continue;
        }
        auto buff = hypothesises.find(currentExpression);
        int hypothesis = 0;
        if (buff != hypothesises.end()) {
            hypothesis = hypothesises.find(currentExpression)->second;
        }

        if (hypothesis) {
            currentExpression->val = {hypothesis, 0, "Hypothesis "};
            provesMap.emplace(currentExpression, i);

            if (currentExpression->getType() == "->") { //&& provesMap.find(currentExpression->getLeft()) != provesMap.end()) {
                expression* r = currentExpression->getRight();
                auto search = modusMap.find(r);

                if (search == modusMap.end()) {
                    modusMap.emplace(r, std::set<mp, Compare>{{currentExpression}});
                } else {
                    search->second.insert({currentExpression}); // after all need to check on a left part
                }
                // delete r;
            }


                // for (auto i: provesMap){
                //      cout << "Debug PM: " << i.first->prefix_form() << " " << i.first->val.a << " " << i.first->val.b << " " << i.second << "\n";
                //      // delete i.first;
                // }
                // for (auto i: modusMap) {
                //     cout << "Debug MP: " << i.first->prefix_form() << " " << i.first->val.a << " " << i.first->val.b << "\n";
                //     for (auto ss: i.second) {
                //         cout << ss.general->prefix_form();
                //     }
                //     // delete i.first;
                // }
            // delete currentExpression;
            continue;
        }

        auto search = modusMap.find(currentExpression);

        // for (auto ss:search->second) {
        //     cout << ss.general->prefix_form();
        // }

        if (search != modusMap.end()) {
            int minValue = INF;
            for (auto ss: search->second) {
                auto left = ss.general->getLeft();
                // cout << left->prefix_form();
                if(provesMap.find(left) != provesMap.end()) {
                    // cout << "lul";

                    auto s = provesMap.find(left);
                    switch (s->first->val.b) {
                        case (-1): {
                            minValue = std::min(1,INF);
                            break;
                        }
                        case (0): {
                            minValue = std::min(INF,1);
                            break;
                        }
                        default: {
                            auto search2 = modusMap.find(left);
                            minValue = std::min(search2->second.begin()->size + 1, INF);
                        }
                    }
                    auto ext = search->second.extract(ss).value();
                    ext.size = minValue;
                    search->second.insert(ext);
                }
                // delete left;
            }

            auto var = search->second.begin();

            if(var->size != INF) {
                search->first->val = {provesMap.find(var->general)->second, provesMap.find(var->general->getLeft())->second, "M. P. "};
                provesMap.emplace(currentExpression, i);

                if (currentExpression->getType() == "->") { //&& provesMap.find(currentExpression->getLeft()) != provesMap.end()) {
                    expression* r = currentExpression->getRight();
                    auto sss = modusMap.find(r);

                    if (sss == modusMap.end()) {
                        modusMap.emplace(r, std::set<mp, Compare>{{currentExpression}});
                    } else {
                        cout << "contains search before insert: \n";
                        for (auto z: sss->second) cout << z.general->prefix_form() << " ";
                        sss->second.insert({currentExpression}); // after all need to check on a left part
                        cout << "contains search after insert: \n";
                        for (auto z: sss->second) cout << z.general->prefix_form() << " ";
                    }
                    // delete r;
                }
                for (auto z: provesMap){
                     cout << "Debug PM: " << z.first->prefix_form() << " " << z.first->val.a << " " << z.first->val.b << " " << z.second << "\n";
                     // delete i.first;
                }
                for (auto z: modusMap) {
                    cout << "Debug MP: " << z.first->prefix_form() << " " << z.first->val.a << " " << z.first->val.b << "\n modusMap[z].second contains: \n";
                    // delete i.first;
                    for (auto ss1: z.second) {
                        cout << ss1.general->prefix_form() << " ";
                    } cout << "\n";
                }

            } else {
                cout << "lulProof is incorrect\n";
                return 0;
            }


            continue;
        }

        delete currentExpression;
        cout << "Proof is incorrect\n";
        return 0;
    }


    if (lastLine != parse(statement)) {
        cout << "Proof is incorrect\n";
        return 0;
    }

    //proves recovery



    for (auto i: provesMap){
         cout << "Debug PM: " << i.first->prefix_form() << " " << i.first->val.a << " " << i.first->val.b << " " << i.second << "\n";
         // delete i.first;
    }
    for (auto i: modusMap) {
        cout << "Debug MP: " << i.first->prefix_form() << " " << i.first->val.a << " " << i.first->val.b << "\n";
        // delete i.first;
    }
    // delete [] modusMap;
    // delete [] provesMap;
    delete lastLine;

    return 0;
}

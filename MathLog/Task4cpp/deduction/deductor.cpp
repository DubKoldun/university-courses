#include <algorithm>
#include <iterator>

#include "../parser/parser.h"
#include "../utils/addFunctions.h"


std::vector<expr_t> deduction(std::vector<expr_t> const& proves,  expr_t left, expr_t right) {
        std::vector<expr_t> answer;
        std::vector<int> oldToNew;
        int currentIndex = 0;
        for (auto i: proves) {
            if (equals(left,i)) {
                std::vector<expr_t> v2;
                std::pair<std::vector<expr_t>,int> p = alphaImpl(left, currentIndex);
                v2 = p.first; currentIndex = p.second;
                std::copy(v2.cbegin(), v2.cend(), std::back_inserter(answer));
                oldToNew.push_back(currentIndex-1);

                // std::cout << "After iteration == " << currentIndex << " <= cur\n" ;
                // for (auto j : answer) {
                //     std::cout << j->prefix_form() << "\n";
                // }std::cout << "\n";
                continue;
            }
            expr_t buff;
            switch (i->val.b) {
                case (-1) : {
                    i->val = {0, -2, "Hyp"};
                    answer.push_back(i);

                    buff = makeAxiom1(i, left);
                    buff->val = {1, -1, "Ax"};
                    answer.push_back(buff);

                    buff = std::make_shared<implication>(left, i);
                    buff->val = {currentIndex, currentIndex + 1, "MP"};
                    answer.push_back(buff);

                    currentIndex += 3;
                    oldToNew.push_back(currentIndex-1);

                    // std::cout << "After iteration " << currentIndex << " <= cur-1\n" ;
                    // for (auto j : answer) {
                    //     std::cout << j->prefix_form() << "\n";
                    // }std::cout << "\n";
                    break;
                }
                case (-2) : {
                    i->val = {0, -2, "Hyp"};
                    answer.push_back(i);

                    buff = makeAxiom1(i, left);
                    buff->val = {1, -1, "Ax"};
                    answer.push_back(buff);

                    buff = std::make_shared<implication>(left, right);
                    buff->val = {currentIndex, currentIndex + 1, "MP"};
                    answer.push_back(buff);

                    currentIndex += 3;
                    oldToNew.push_back(currentIndex-1);

                    // std::cout << "After iteration " << currentIndex << "<= cur-2\n" ;
                    // for (auto j : answer) {
                    //     std::cout << j->prefix_form() << "\n";
                    // }std::cout << "\n";
                    break;
                }
                default : {
                    // cout << i->val.a << " -> " << oldToNew[i->val.a] << "\n";
                    // cout << i->val.b << " -> " << oldToNew[i->val.b] << "\n";
                    expr_t a = answer[oldToNew[i->val.a]];
                    expr_t b = answer[oldToNew[i->val.b]];
                    expr_t c = b->getRight();
                    buff = makeAxiom2(left, a->getRight(), c->getRight());
                    buff->val = {2, -1, "Ax"};
                    answer.push_back(buff);

                    buff = std::make_shared<implication>(b, c);
                    buff->val = {oldToNew[i->val.a], currentIndex, "MP"};
                    answer.push_back(buff);

                    buff = answer[oldToNew[i->val.b]]->getRight();
                    buff->val = {oldToNew[i->val.b], currentIndex + 1, "MP"};
                    answer.push_back(buff);

                    currentIndex += 3;
                    oldToNew.push_back(currentIndex-1);

                    // std::cout << "After iteration " << currentIndex << "<=cur mp\n" ;
                    // for (auto j : answer) {
                    //     std::cout << j->prefix_form() << "\n";
                    // }std::cout << "\n";
                }
            }

        }
        return answer;

}

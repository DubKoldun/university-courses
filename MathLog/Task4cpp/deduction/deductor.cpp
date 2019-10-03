#include "../parser/parser.h"
#include "../utils/addFunctions.h"


std::vector<expr_t> deduction(std::vector<expr_t> const& proves, std::vector<int> oldToNew,  expr_t left, expr_t right) {
        std::vector<expr_t> answer;
        int currentIndex = 0;
        for (auto i: proves) {
            if (equals(left,i)) {
                answer.push_back(alphaImpl(left, currentIndex));
                oldToNew.push_back(currentIndex-1);
                continue;
            }
            expr_t buff;
            switch (i->val.b) {
                case (-1) : {
                    i->val = {0, 0, "Hyp"};
                    answer.push_back(i);
                    oldToNew.push_back(currentIndex);

                    buff = makeAxiom1(i, left);
                    buff->val = {1, -1, "Ax"};
                    answer.push_back(buff);

                    buff = std::make_shared<implication>(left,right);
                    buff->val = {currentIndex, currentIndex + 1, "MP"};
                    answer.push_back(buff);

                    currentIndex += 3;
                    oldToNew.push_back(currentIndex-1);

                    break;
                }
                case (0) : {
                    i->val = {0, 0, "Hyp"};
                    answer.push_back(i);

                    buff = makeAxiom1(i, left);
                    buff->val = {1, -1, "Ax"};
                    answer.push_back(buff);

                    buff = std::make_shared<implication>(left,right);
                    buff->val = {currentIndex, currentIndex + 1, "MP"};
                    answer.push_back(buff);

                    currentIndex += 3;
                    oldToNew.push_back(currentIndex-1);

                    break;
                }
                default : {
                    expr_t a = std::make_shared<implication>(left, answer[oldToNew[i->val.a]]);
                    expr_t b = std::make_shared<implication>(left, answer[oldToNew[i->val.b]]);
                    expr_t c = std::make_shared<implication>(left, answer[oldToNew[i->val.b]]->getRight());
                    buff = makeAxiom2(a, b, c);
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
                }
            }
        }

}

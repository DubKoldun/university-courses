//
// Created by vitaliy on 20.04.19.
//
// So painful
//

#include "../expression.h"

int axiomNumber(expr_t expr) {

    if (expr->getType() == "->") { // 1,2,3,4,5,6,7,8,9,10
        expr_t left = expr->getLeft(), right = expr->getRight();

        if (right->getType() == "->") { // 1,2,3,8,9

            if (equals(left, right->getRight())) return  1; // 1

            if (right->getRight()->getType() == "&") { // 3
                if (equals(right->getRight()->getLeft(), left) && equals(right->getLeft(),right->getRight()->getRight())) {
                    return 3;
                }
            }

        } else { //,6,7
            
            if (right->getType() == "|") { //6,7
                if (equals(left, right->getLeft())) return 6;
                if (equals(left, right->getRight())) return 7;
            }
        }



        if (left->getType() == "&") { //4,5
            if (equals(left->getLeft(), right)) return 4;
            if (equals(left->getRight(), right)) return 5;
        }

        if (left->getType() == "!") { //10
            if (left->getLeft()->getType() == "!") {
                if (equals(right, left->getLeft()->getLeft())) {
                    return 10;
                }
            }
        }

        switch (left->getType().back()) { // 2,8,9
            case '>': {
                if (right->getType() != "->")
                    break;
                if (right->getLeft()->getType() != "->")
                    break;
                expr_t fi = left->getLeft();
                expr_t ksi = left->getRight();
                expr_t leftR = right->getLeft();
                expr_t rightR = right->getRight();

                switch (rightR->getType().back()) {
                    case '>': // 2, 8
                        if (leftR->getRight()->getType() == "->" &&
                            equals(fi, leftR->getLeft()) &&
                            equals(fi, rightR->getLeft()) &&
                            equals(ksi, leftR->getRight()->getLeft()) &&
                            equals(leftR->getRight()->getRight(), rightR->getRight())) {
                            return 2;
                        }
                        if (rightR->getLeft()->getType() == "|" &&
                            equals(fi, rightR->getLeft()->getLeft()) &&
                            equals(ksi, leftR->getRight()) &&
                            equals(ksi, rightR->getRight()) &&
                            equals(leftR->getLeft(), rightR->getLeft()->getRight())) {
                            return 8;
                        }
                        break;
                    case '!': // 9
                        if (leftR->getRight()->getType() != "!")
                            break;
                        if (equals(fi, leftR->getLeft()) &&
                            equals(fi, rightR->getRight()) &&
                            equals(ksi, leftR->getRight()->getRight()))
                            return 9;
                        break;
                }
                break;
            }
        }


    }

    return 0;
}

// //
// // Created by vitaliy on 20.04.19.
// //
// // GOVNOCODE  v. 1.0
// // So painful
// //
//
//
// int axiomNumber(expression *expr) { //GOVNOCODE
//
//     if (expr->getType() == "->") { // 1,2,3,4,5,6,7,8,9,10
//         auto *impl = dynamic_cast<binaryOperation *>(expr);
//         expression *left = impl->getLeft(), *right = impl->getRight();
//
//         if (left->getType() == "!") { //10
//             if (left->getLeft()->getType() == "!") {
//                 if (*right == left->getLeft()->getLeft()) return 10;
//             }
//         }
//
//         if (right->getType() == "->") { // 1,2,3,8,9
//
//             if (*left == right->getRight()) return 1; // 1
//
//             if (right->getRight()->getType() == "&") { // 3
//                 if (*right->getRight()->getLeft() == left && *right->getLeft() == right->getRight()->getRight())
//                     return 3;
//             }
//
//             switch (left->getType().back()) { // 2,8,9
//                 case '>': {
//                     if (right->getType() != "->")
//                         break;
//                     if (right->getLeft()->getType() != "->")
//                         break;
//                     expression *fi = left->getLeft();
//                     expression *ksi = left->getRight();
//                     expression *leftR = right->getLeft();
//                     expression *rightR = right->getRight();
//
//                     switch (rightR->getType().back()) {
//                         case '>': // 2, 8
//                             if (leftR->getRight()->getType() == "->" &&
//                                 (*fi == leftR->getLeft()) &&
//                                 (*fi == rightR->getLeft()) &&
//                                 (*ksi == leftR->getRight()->getLeft()) &&
//                                 (*leftR->getRight()->getRight() == rightR->getRight()))
//                                 return 2;
//                             if (rightR->getLeft()->getType() == "|" &&
//                                 (*fi == rightR->getLeft()->getLeft()) &&
//                                 (*ksi == leftR->getRight()) &&
//                                 (*ksi == rightR->getRight()) &&
//                                 (*leftR->getLeft() == rightR->getLeft()->getRight()))
//                                 return 8;
//                             break;
//                         case '!': // 9
//                             if (leftR->getRight()->getType() != "!")
//                                 break;
//                             if ((*fi == leftR->getLeft()) &&
//                                 (*fi == rightR->getRight()) &&
//                                 (*ksi == leftR->getRight()->getRight()))
//                                 return 9;
//                             break;
//                     }
//                     break;
//                 }
//             }
//
//         } else { //4,5,6,7
//             if (left->getType() == "&") { //4,5
//                 if (*left->getLeft() == right) return 4;
//                 if (*left->getRight() == right) return 5;
//             }
//             if (right->getType() == "|") { //6,7
//                 if (*left == right->getLeft()) return 6;
//                 if (*left == right->getRight()) return 7;
//             }
//         }
//
//     } else { // 0
// //        std::cout << "wtf\n";
//         return 0;
//     }
//
//     return 0;
// }

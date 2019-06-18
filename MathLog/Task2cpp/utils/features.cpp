// //
// // Created by vitaliy on 20.04.19.
// //
//
// #include <iostream>
// #include <memory>
// #include "hypothesises.cpp"
// #include "../parser/expression.tab.h"
// #include "../parser/expression.lexer.h"
//
// using std::string;
// using std::cout;
// using std::cerr;
// using std::cin;
//
// extern expression* result;
// string statement = "";
//
// void yyerror(const char *error) {
//     cerr << error;
// }
//
// int yywrap() {
//     return 1;
// }
//
// void destroySpaces(std::string & some) {
//     for (size_t i = 0; i < some.size()-1; ++i) {
//         if (some[i] == ' ') {
//             some.erase(i--, 1);
//         }
//     }
// }
//
// bool readLine(string& expression) {
//     if (getline(cin,expression)) {
//         destroySpaces(expression);
//         return true;
//     } else {
//         return false;
//     }
// }
//
// expression* makeExpression(string const& express) {
//     // expression* expr1;
//     yy_scan_string(express.c_str());
//     yyparse(); // huinya
//     return result;
//     // expr1 = result;
//     // // delete result;
//     // return expr1;
// }
//
// void parseStatement(size_t i, string const& firstLine) {
//     i += 2;
//     for (; i < firstLine.size(); ++i) statement.push_back(firstLine[i]);
// }
//
// // void readFirstLine() {
// //     string firstLine, leftPart, rightPart;
// //     readLine(firstLine);
// //
// //     size_t i = 0;
// //     size_t number = 0;
// //     string buff = "";
// //
// //     for (; firstLine[i] != '|' || firstLine[i + 1] != '-'; ++i) {
// //         if (firstLine[i] == ',' || (firstLine[i + 1] == '|' && firstLine[i + 2] == '-')) {
// //             // if (firstLine[i + 1] == '|' && firstLine[i + 2] == '-') buff.push_back(firstLine[i]);
// //             // std::shared_ptr<expression> ssss(makeExpression(buff));
// //             auto t = makeExpression(buff);
// //             delete t;
// //             auto y = makeExpression(buff);
// //             delete y;
// //             // hypothesises.emplace(ssss, ++number);
// //             // buff.clear();
// //             continue;
// //         }
// //         // buff.push_back(firstLine[i]);
// //     }
// //     // parseStatement(i, firstLine);
// // }

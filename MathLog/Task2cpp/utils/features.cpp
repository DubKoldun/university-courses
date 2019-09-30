//
// Created by vitaliy on 20.04.19.
//
#include <iostream>
// #include <fstream>
#include <limits>
#include <vector>
#include "hypothesises.cpp"
#include "parser.cpp"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::cin;

// std::ifstream in("tests/proof1.txt");
// std::ofstream out("tests/out1.txr");
//

string statement, hypotForAns = "";

int checkHypothesis(expr_t expr) {
    auto buff = hypothesises.find(expr);
    if (buff != hypothesises.end()) {
        return buff->second;
    }
    return 0;

}

void destroySpaces(string & some) {
    for (size_t i = 0; i < some.size(); ++i) {
        if (some[i] == ' ' || some[i] == '\n' || some[i] == '\t') {
            some.erase(i--, 1);
        }
    }
}

bool readLine(string & expression) {
    if (getline(cin, expression)) {          //////////////////////
        // for (auto e: expression) cout << e << "\n";
        destroySpaces(expression);
        // for (auto e: expression) cout << e << "\n";
        return true;
    } else {
        return false;
    }
}

void parseStatement(size_t i, string const& firstLine) {
    i += 2;
    for (; i < firstLine.size(); ++i) statement.push_back(firstLine[i]);
}

void readFirstLine() {
    string firstLine;
    readLine(firstLine);

    size_t i = 0;
    int number = 0;
    string buff = "";

    for (; firstLine[i] != '|' || firstLine[i + 1] != '-'; ++i) {
        if (firstLine[i] == ',' || (firstLine[i + 1] == '|' && firstLine[i + 2] == '-')) {
            if (firstLine[i + 1] == '|' && firstLine[i + 2] == '-') buff.push_back(firstLine[i]);
            hypotForAns += (parse(buff)->prefix_form() + ", ");
            hypothesises.emplace(parse(buff), ++number);
            buff.clear();
            continue;
        }
        buff.push_back(firstLine[i]);
    }
    parseStatement(i, firstLine);
}

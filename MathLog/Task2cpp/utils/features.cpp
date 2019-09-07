//
// Created by vitaliy on 20.04.19.
//

#include <iostream>
#include <memory>
#include "hypothesises.cpp"
#include "parser.cpp"

using std::string;
using std::cout;
using std::cerr;
using std::cin;

string statement;

void destroySpaces(std::string & some) {
    for (size_t i = 0; i < some.size()-1; ++i) {
        if (some[i] == ' ') {
            some.erase(i--, 1);
        }
    }
}

bool readLine(string& expression) {
    if (getline(cin,expression)) {
        destroySpaces(expression);
        return true;
    } else {
        return false;
    }
}

expression* makeExpression(string & express) {
    expression* result = parse(express);
    return result;
}

void parseStatement(size_t i, string const& firstLine) {
    i += 2;
    for (; i < firstLine.size(); ++i) statement.push_back(firstLine[i]);
}

void readFirstLine() {
    string firstLine, leftPart, rightPart;
    readLine(firstLine);

    size_t i = 0;
    size_t number = 0;
    string buff = "";

    for (; firstLine[i] != '|' || firstLine[i + 1] != '-'; ++i) {
        if (firstLine[i] == ',' || (firstLine[i + 1] == '|' && firstLine[i + 2] == '-')) {
            if (firstLine[i + 1] == '|' && firstLine[i + 2] == '-') buff.push_back(firstLine[i]);
            expression * ssss = makeExpression(buff);
            hypothesises.emplace(ssss, ++number);
            buff.clear();
            continue;
        }
        buff.push_back(firstLine[i]);
    }
    parseStatement(i, firstLine);
}

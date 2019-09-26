//
// Created by vitaliy on 20.04.19.
//
#include <iostream>
#include "hypothesises.cpp"
#include "parser.cpp"

using std::string;
using std::cout;
using std::cerr;
using std::cin;


string statement;

int checkHypothesis(expr_t expr) {
    auto buff = hypothesises.find(expr);
    if (buff != hypothesises.end()) {
        return buff->second;
    }
    return 0;

}

void destroySpaces(string & some) {
    for (size_t i = 0; i < some.size()-1; ++i) {
        if (some[i] == ' ') {
            some.erase(i--, 1);
        }
    }
}

bool readLine(string & expression) {
    if (getline(cin, expression)) {
        destroySpaces(expression);
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
            hypothesises.emplace(parse(buff), ++number);
            buff.clear();
            continue;
        }
        buff.push_back(firstLine[i]);
    }
    parseStatement(i, firstLine);
}



struct ComparePairs {
    bool operator()(std::pair<expr_t, int> const& pair1, std::pair<expr_t, int> const& pair2) const {
        return pair1.second < pair2.second;
    }
};

struct mp {
    int number, size;
    expr_t left;
};

struct CompareMP {
    bool operator()(mp first, mp second) {
        return first.size < second.size;
    }
};

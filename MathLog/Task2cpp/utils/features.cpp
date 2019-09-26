//
// Created by vitaliy on 20.04.19.
//
#include <iostream>
#include <limits>
#include <vector>
#include "hypothesises.cpp"
#include "parser.cpp"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::cin;


string statement, hypotForAns = "";

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
            hypotForAns += (parse(buff)->prefix_form() + ", ");
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

unordered_map <int, expr_t> reverseMap(unordered_map <expr_t, int, StringHasher, EqualChecker> const& provesMap) {
    unordered_map <int, expr_t> ans;
    for (auto i: provesMap) {
        ans.emplace(i.second, i.first);
    }
    return ans;
}

void recovery(unordered_map <int, expr_t> const& reverseProvesMap, unordered_map <expr_t, int, StringHasher, EqualChecker> const& provesMap, expr_t expr, vector<std::pair<expr_t, int>> & ans) {
    auto current = provesMap.find(expr);
    switch (expr->val.b) {
        case (-1) : {
            // cout << -1;
            ans.emplace_back(std::pair<expr_t, int>({expr, current->second}));
            break;
        }
        case (0) : {
            // cout << 0;
            ans.emplace_back(std::pair<expr_t, int>({expr, current->second}));
            break;
        }
        default: {
            // cout << 1;
            ans.emplace_back(std::pair<expr_t, int>({expr, current->second}));
            int a = expr->val.a, b = expr->val.b;
            auto buff1 = reverseProvesMap.find(a), buff2 = reverseProvesMap.find(b);
            recovery(reverseProvesMap, provesMap, buff1->second, ans);
            recovery(reverseProvesMap, provesMap, buff2->second, ans);

            // cout << 1
            // ans.emplace_back(std::pair<expr_t, int>({buff1->second, a}));
            // ans.emplace_back(std::pair<expr_t, int>({buff2->second, b}));
        }
    }
}

// struct mp {
//     int number, size;
//     expr_t left;
// };
//
// struct CompareMP {
//     bool operator()(mp first, mp second) {
//         return first.size < second.size;
//     }
// };

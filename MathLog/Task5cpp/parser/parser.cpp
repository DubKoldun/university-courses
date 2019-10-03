#include "parser.h"

// подумать о скобках. в терме могут быть скобки
// скипнешь ли ты их случайно или нет, что с этим
// можно сделать + ты у унара вызываешь парс, если встретил скобку.
// также у плюса и умножить - наименьший
// приоритет справа .


expr_t var (string expr) {
    return std::make_shared<variable>(expr);
}

expr_t otricala (string  expr) {
    size_t currentPosition = 0, size = expr.size();
    while (currentPosition != size) {
        switch (expr[currentPosition]) {
            case '!': {
                return std::make_shared<negation>(otricala(expr.substr(currentPosition+1,size)));
            }
        }
        ++currentPosition;
    }
    return unary(expr);
}

expr_t ter (string expr) {
    size_t size = expr.size();
    size_t currentPosition = expr.size()-1, //// tut
}

expr_t funct (string expr) {
    string name = "";
    size_t currentPosition = 0, size = expr.size();
    while (expr[currentPosition] != '(') name += expr[++currentPosition];

    size_t startTerm = currentPosition + 1;
    vector<expr_t> buff;

    while (expr[currentPosition] != ')') {
        while (expr[currentPosition] != ',' || expr[currentPosition] != ')') ++currentPosition;
        buff.push_back(ter(expr.substr(startTerm, currentPosition)));
        ++currentPosition;
    }
    terms.push_back(buff);
    return make_shared<function>(var(name), terms.size()-1);
}


expr_t pred (string expr) {
    size_t currentPosition = 0, size = expr.size();

    if (expr[currentPosition] <= 'Z' && expr[currentPosition] >= 'A') {
        return funct(expr);
    }

    while (expr[currentPosition] != '=') ++currentPosition;
    return std::make_shared<predicat>(ter(expr.substring(0,currentPosition)), ter(expr.substring(currentPosition+1, size)));
}


expr_t unary (string expr) {
    size_t size = expr.size(), count = 0;
    int currentPosition = 0;
    while (currentPosition != size) {
        switch (expr[currentPosition]) {
            case '!': {
                return std::make_shared<negation>(otricala(expr.substr(currentPosition+1,size)));
            }
            case '(': {
                return parse(expr.substr(1, size - 1));
            }
            case '@': {
                while (expr[currentPosition] != '.') ++currentPosition;
                return std::make_shared<unary>(var(expr.substr(1,currentPosition), parse(expr.substr(currentPosition+1, size)), "@"));
            }
            case '?': {
                while (expr[currentPosition] != '.') ++currentPosition;
                return std::make_shared<unary>(var(expr.substr(1,currentPosition), parse(expr.substr(currentPosition+1, size)), "?"));
            }
        }
    }
    return pred(expr);
}

expr_t conjunct (string  expr) {
    size_t size = expr.size(), count = 0;
    int currentPosition = size-1;
    while (currentPosition != -1) {
        switch (expr[currentPosition]) {
            case ')': {
                ++count;
                while (currentPosition != -1 && count != 0) {
                    --currentPosition;
                    if (expr[currentPosition] == ')') ++count;
                    if (expr[currentPosition] == '(') --count;
                }
                continue;
            }
            case '&': {
                return std::make_shared<conjunction>(conjunct(expr.substr(0,currentPosition)), unary(expr.substr(currentPosition+1,size)));
            }
        }
            --currentPosition;
    }
    return unary(expr);
}


expr_t disjunct(string  expr) {
    size_t size = expr.size(), count = 0;
    int currentPosition = size-1;
    while (currentPosition != -1) {
        switch (expr[currentPosition]) {
            case ')': {
                ++count;
                while (currentPosition != -1 && count != 0) {
                    --currentPosition;
                    if (expr[currentPosition] == ')') ++count;
                    if (expr[currentPosition] == '(') --count;
                }
                continue;
            }
            case '|': {
                return std::make_shared<disjunction>(disjunct(expr.substr(0,currentPosition)),conjunct(expr.substr(currentPosition+1,size)));
            }
        }
        --currentPosition;
    }
    return conjunct(expr);
}

expr_t parse(string expr) {
    size_t currentPosition = 0, size = expr.size(), count = 0;
    while (currentPosition != size) {
        switch (expr[currentPosition]) {
            case '(': {
                ++count;
                while (currentPosition != size && count != 0) {
                     ++currentPosition;
                     if (expr[currentPosition] == ')') --count;
                     if (expr[currentPosition] == '(') ++count;
                 }
                continue;
            }
            case '-': {
                return std::make_shared<implication>(disjunct(expr.substr(0,currentPosition)),parse(expr.substr(currentPosition+2,size)));
            }
        }
        ++currentPosition;
    }
    return disjunct(expr);
}

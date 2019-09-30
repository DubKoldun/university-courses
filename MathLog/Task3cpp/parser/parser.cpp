#include "parser.h"

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
            case '(': {
                return parse(expr.substr(1,size-2));
            }
        }
        ++currentPosition;
    }

    return var(expr);
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
                return std::make_shared<conjunction>(conjunct(expr.substr(0,currentPosition)),otricala(expr.substr(currentPosition+1,size)));
            }
        }
            --currentPosition;
    }
    return otricala(expr);
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

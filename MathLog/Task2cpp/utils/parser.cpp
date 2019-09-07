#include <iostream>
#include "../expression.h"

using std::string;
using std::cout;
using std::cin;

expression * parse(string  expr);

expression * var (string  expr) {
    expression * result = new variable(expr);
    return result;
}

expression * otricala (string  expr) {
    size_t currentPosition = 0, size = expr.size();
    while (currentPosition != size) {
        switch (expr[currentPosition]) {
            case '!': {
                expression * result = new negation(otricala(expr.substr(currentPosition+1,size)));
                return result;
            }
            case '(': {
                expression * result = parse(expr.substr(1,size-2));
                return result;
            }
        }
        ++currentPosition;
    }
    return var(expr);
}

expression * conjunct (string  expr) {
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
                expression * result = new conjunction(conjunct(expr.substr(0,currentPosition)),otricala(expr.substr(currentPosition+1,size)));
                return result;
            }
        }
            --currentPosition;
    }
    return otricala(expr);
}


expression * disjunct(string  expr) {
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
                expression * result = new disjunction(disjunct(expr.substr(0,currentPosition)),conjunct(expr.substr(currentPosition+1,size)));
                return result;
            }
        }
        --currentPosition;
    }
    return conjunct(expr);
}

expression* parse(string  expr) {
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
                expression * result = new implication(disjunct(expr.substr(0,currentPosition)),parse(expr.substr(currentPosition+2,size)));
                return result;
            }
        }
        ++currentPosition;
    }
    return disjunct(expr);
}

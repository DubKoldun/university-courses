#include <utility>

#ifndef CPP_SOLUTION_EXPRESSION_H
#define CPP_SOLUTION_EXPRESSION_H

#include <string>
#include <iostream>

class expression {
public:
    virtual std::string prefix_form() = 0;

    virtual bool operator==(expression *some) = 0;

    virtual std::string getType() = 0;

    virtual expression* getLeft() = 0;

    virtual expression* getRight() = 0;

    virtual ~expression() = default;

    struct meaning {
        int a, b = 0;
        std::string value;

        std::string name() {
            switch (b) {
                case (-1): {
                    return value + std::to_string(a);
                }
                case (0): {
                    return value + std::to_string(a);
                }
                default: {
                    return value + std::to_string(a) + std::to_string(b);
                }
            }
        }
    };

    meaning val;
};

class binaryOperation : public expression {
private:
    expression *_left;
    expression *_right;
    std::string _type;
public:
    binaryOperation(expression *left, expression *right, std::string type) :
            _left(left),
            _right(right), _type(std::move(type)) {
    }

    std::string getType() override {
        return _type;
    }

    expression *getLeft() override {
        return _left;
    }

    expression *getRight() override {
        return _right;
    }

    bool operator==(expression *some) override {
        if (getType() != some->getType()){
//            std::cout << "not" << getType() << some->getType() << std::endl;
            return false;
        }
        else {
//            std::cout << "yes" << getType() << some->getType() << std::endl;
            auto *some1 = dynamic_cast<binaryOperation *>(some);
            return (*some1->getLeft() == getLeft()) && (*some1->getRight() == getRight());
        }
    }

    std::string prefix_form() override {
        return "(" + _left->prefix_form() + _type + _right->prefix_form() + ")";
    }
};

class variable : public expression {
private:
    std::string _name;
    std::string _type = "variable";
public:
    explicit variable(std::string &name) : _name(name) {
    }

    std::string getType() override {
        return _type;
    }

    expression *getLeft() override {
        return nullptr;
    }

    expression *getRight() override {
        return nullptr;
    }

    bool operator==(expression *some) override {
//        std::cout << "variable operator: ";
//        std::cout << prefix_form() << " " << some->prefix_form() << "\n";
        return _type == some->getType() && prefix_form() == some->prefix_form();
    }

    std::string prefix_form() override {
        return _name;
    }

};

class implication : public binaryOperation {
public:
    implication(expression *left, expression *right) : binaryOperation(left, right, "->") {
    }

};

class disjunction : public binaryOperation {
public:
    disjunction(expression *left, expression *right) : binaryOperation(left, right, "|") {
    }
};

class conjunction : public binaryOperation {
public:
    conjunction(expression *left, expression *right) : binaryOperation(left, right, "&") {
    }

};

class negation : public expression {
private:
    expression *_expr;
    std::string _type = "!";
public:
    explicit negation(expression *expr) :
            _expr(expr) {
    }

    std::string getType() override {
        return _type;
    }

    expression * getExpr() {
        return _expr;
    }

    expression *getLeft() override {
        return _expr;
    }

    expression *getRight() override {
        return _expr;
    }

    bool operator==(expression* some) override {
//        std::cout << "neg operator ";
//        std::cout << _expr->prefix_form() << " " << some->prefix_form() << "\n";
//        std::cout << _expr->getType()     << " " << some->getType() << "\n";
        if (getType() != some->getType()) return false;
        else {
            auto *some1 = dynamic_cast<negation *>(some);
            return *some1->getExpr() == _expr;
        }
    }

    std::string prefix_form() override {
        return  _expr->prefix_form();
    }
};

#endif //CPP_SOLUTION_EXPRESSION_H

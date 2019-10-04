#ifndef CPP_SOLUTION_EXPRESSION_H
#define CPP_SOLUTION_EXPRESSION_H

#include <memory>
#include <string>
#include <iostream>

using std::shared_ptr;

const int INF = std::numeric_limits<int>::max();

class expression;

using expr_t = std::shared_ptr<expression>;

class expression {
public:

    virtual std::string prefix_form() = 0;

    virtual std::string getType() = 0;

    virtual expr_t getLeft() = 0;

    virtual expr_t getRight() = 0;

    virtual ~expression() = default;

    struct meaning {
        int a, b = 0;
        std::string value;

        std::string name() {
            switch (b) {
                case (-1): {
                    return value + std::to_string(a);
                }
                case (-2): {
                    return value + std::to_string(a);
                }
                default: {
                    return value + std::to_string(a) + std::to_string(b);
                }
            }
        }
    };

    friend bool equals(expr_t expr1, expr_t expr2);

    meaning val;
private:

    virtual bool equalsSharedPointer(expr_t expr) = 0;

};

class binaryOperation : public expression {
private:

    expr_t _left;
    expr_t _right;
    std::string _type;

    bool equalsSharedPointer(expr_t some) override {
        if (getType() != some->getType()) {
            return false;
        }
        std::shared_ptr<binaryOperation> some1 = std::dynamic_pointer_cast<binaryOperation>(some);
        return equals(_left,some1->getLeft())  && equals(_right,some1->getRight());
    }

public:

    binaryOperation(expr_t left, expr_t right, std::string type) :
            _left(left),
            _right(right), _type(std::move(type)) {
    }

    std::string getType() override {
        return _type;
    }

    expr_t getLeft() override {
        return _left;
    }

    expr_t getRight() override {
        return _right;
    }

    std::string prefix_form() override {
        return "("  +  _left->prefix_form() + " " + _type + " " + _right->prefix_form() + ")";
    }

};

class variable : public expression {
private:

    std::string _name;
    std::string _type = "variable";

    bool equalsSharedPointer (expr_t some) override {
        return (_type == some->getType()) && (_name == some->prefix_form());
    }

public:
    explicit variable(std::string &name) : _name(name) {
    }

    std::string getType() override {
        return _type;
    }

    expr_t getLeft() override {
        std::cout << "lol";
        return nullptr;
    }

    expr_t getRight() override {
        std::cout << "lol";
        return nullptr;
    }

    std::string prefix_form() override {
        return _name;
    }

};

class implication : public binaryOperation {
public:
    implication(expr_t left, expr_t right) : binaryOperation(left, right, "->") {
    }

};

class disjunction : public binaryOperation {
public:
    disjunction(expr_t left, expr_t right) : binaryOperation(left, right, "|") {
    }
};

class conjunction : public binaryOperation {
public:
    conjunction(expr_t left, expr_t right) : binaryOperation(left, right, "&") {
    }

};

class negation : public expression {
private:

    expr_t _expr;
    std::string _type = "!";

    bool equalsSharedPointer(expr_t some) override {
        if (getType() != some->getType()) {
            return false;
        }
        std::shared_ptr<negation> some1 = std::dynamic_pointer_cast<negation>(some);
        return equals(_expr, some1->getExpr());
    }

public:
    explicit negation(expr_t expr) :
            _expr(expr) {
    }

    std::string getType() override {
        return _type;
    }

    expr_t getExpr() {
        return _expr;
    }

    expr_t getLeft() override {
        return _expr;
    }

    expr_t getRight() override {
        return _expr;
    }

    std::string prefix_form() override {
        return  "!" + _expr->prefix_form();
    }

};

bool equals(expr_t expr1, expr_t expr2) {
    return expr1->equalsSharedPointer(expr2);
}

#endif //CPP_SOLUTION_EXPRESSION_H

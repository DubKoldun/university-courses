#ifndef CPP_SOLUTION_EXPRESSION_H
#define CPP_SOLUTION_EXPRESSION_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

using std::shared_ptr;

class expression;

using expr_t = std::shared_ptr<expression>;

class expression {
public:

    virtual std::string getStr() = 0;

    virtual std::string getType() = 0;

    virtual expr_t getLeft() = 0;

    virtual expr_t getRight() = 0;

    virtual int getIndex() = 0;

    virtual ~expression() = default;

    // struct meaning {
    //     int a, b = 0, depth = INF;
    //     std::string value;
    //
    //     std::string name() {
    //         switch (b) {
    //             case (-1): {
    //                 return value + std::to_string(a);
    //             }
    //             case (0): {
    //                 return value + std::to_string(a);
    //             }
    //             default: {
    //                 return value + std::to_string(a) + std::to_string(b);
    //             }
    //         }
    //     }
    // };

    friend bool equals(expr_t expr1, expr_t expr2);

    // meaning val;
private:

    virtual bool equalsSharedPointer(expr_t expr) = 0;

};

std::vector<std::vector<expr_t>> terms;

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
        return equals(_left,some1->getLeft()) && equals(_right,some1->getRight());
    }

public:

    binaryOperation(expr_t left, expr_t right, std::string type) :
            _left(left),
            _right(right), _type(std::move(type)) {
    }

    std::string getType() override {
        return _type;
    }

    int getIndex()  override{
        return -1;
    }

    expr_t getLeft() override {
        return _left;
    }

    expr_t getRight() override {
        return _right;
    }

    std::string getStr() override {
        return "("  +  _left->getStr() + " " + _type + " " + _right->getStr() + ")";
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


class unar : public binaryOperation {
public:

    std::string getStr() override {
        return "(" + getType() + getLeft()->getStr() + "." + getRight()->getStr() + ")";
    }

    unar (expr_t left, expr_t right, std::string _type) : binaryOperation(left, right, _type) {}

};

class function : public expression {
private:
    int _index;
    expr_t _right;
    std::string _type = "function";
public:

    int getIndex() override {
        return _index;
    }

    std::string getType() override {
        return _type;
    }

    expr_t getRight() override {
        return _right;
    }

    expr_t getLeft() override {
        return nullptr;
    }

    std::string getStr() override{
        std::string buff = "(" + _right->getStr() + "(";
        for (size_t i = 0; i < terms[_index].size(); ++i) {
            buff += terms[_index][i]->getStr();
            if (i < terms[_index].size() - 1) {
                buff += ", ";
            }
        }
        buff += "))";
        return buff;
    }

    function(expr_t right, int index) : _right(right), _index(index) {}

};

class predicat : public binaryOperation {
public:

    std::string getStr() override {
        return "(" +  getLeft()->getStr() + " = " + getRight()->getStr() + ")";
    }

    predicat(expr_t left, expr_t right) : binaryOperation(left, right, "predicat") {}

};

class plus : public binaryOperation {
public:

    std::string getStr() override{
        return "(" + getLeft()->getStr() + " * " + getRight()->getStr() + ")";
    }

    plus(expr_t left, expr_t right) : binaryOperation(left, right, "plus") {

    }
};

class multiply : public expression {
public:
    expr_t _right, _left;
    std::string _type = "multiply";
    int _index = -1;

    int getIndex() override {
        return _index;
    }

    std::string getType() override{
        return _type;
    }

    expr_t getRight() override{
        return _right;
    }

    expr_t getLeft() override{
        return _left;
    }

    std::string getStr() override{
        std::string buff;
        switch (_type[0]) {
            case '0' : {
                buff = "0";
                break;
            }
            case '1' : {
                buff = _right->getStr() + "\'";
                break;
            }
            case 'f' : {
                buff = "(" + _right->getStr() + "(";
                for (int i = 0; i < terms[_index].size(); ++i) {
                    buff += terms[_index][i]->getStr();
                    if (i < terms[_index].size() - 1) {
                        buff += ", ";
                    }
                }
                buff += "))";
                break;
            }
        }
        return buff;
    }

    multiply(expr_t left, expr_t right, std::string type) :
            _left(left),
            _right(right), _type(type) {
    }

    multiply(expr_t left, std::string type) :
            _right(left), _type(type) {
    }

    multiply(expr_t left, int index, std::string type) :
    _right(left),
    _index(index), _type(type) {

    }
};


class term : public binaryOperation {
public:

    std::string getStr() override{
        return "(" + getLeft()->getStr() + " + " + getRight()->getStr() + ")";
    }

    term(expr_t left, expr_t right) : binaryOperation(left, right, "term") {}

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

    int getIndex() override {
        return -1;
    }

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

    std::string getStr() override {
        return  "!" + _expr->getStr();
    }

};

class variable : public expression {
private:

    std::string buff;
    std::string _type = "variable";

    bool equalsSharedPointer (expr_t some) override {
        return (_type == some->getType()) && (buff == some->getStr());
    }

public:

    int getIndex() override {
        return -1;
    }

    explicit variable(std::string &name) : buff(name) {
    }

    std::string getType() override {
        return _type;
    }

    expr_t getLeft() override {
        return nullptr;
    }

    expr_t getRight() override {
        return nullptr;
    }

    std::string getStr() override {
        return buff;
    }

};


bool equals(expr_t expr1, expr_t expr2) {
    return expr1->equalsSharedPointer(expr2);
}

#endif //CPP_SOLUTION_EXPRESSION_H

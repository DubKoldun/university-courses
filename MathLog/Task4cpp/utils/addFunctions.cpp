#include "../parser/parser.h"
#include <vector>

string destroySpaces2(string const& some1) {
    string some = some1;
    for (size_t i = 0; i < some.size(); ++i) {
        if (some[i] == ' ' || some[i] == '\n' || some[i] == '\t') {
            some.erase(i--, 1);
        }
    }
    return some;
}

expr_t makeNeg(expr_t expr) {
    return parse(destroySpaces2("!" + expr->prefix_form()));
}

expr_t makeAxiom1(expr_t a, expr_t b) {
    return parse(destroySpaces2(a->prefix_form() + "->" + b->prefix_form() + "->" + a->prefix_form()));
}

expr_t makeAxiom2(expr_t a, expr_t b, expr_t c) {
    return parse(destroySpaces2("(" + a->prefix_form() + "->" + b->prefix_form() + ")->(" + a->prefix_form() + "->" + b->prefix_form() + "->" + c->prefix_form() + ")->(" + a->prefix_form() + "->" + c->prefix_form() + ")"));
}

expr_t makeAxiom9(expr_t a, expr_t b) {
    return parse(destroySpaces2(" ( " + a->prefix_form() + " -> " + b->prefix_form() + " ) -> ( " + a->prefix_form() + "-> !" + b->prefix_form() + ") -> !" + a->prefix_form()));
}

// (1) α → (α → α) Сх. акс. 1
// (2) (α → (α → α)) → (α → ((α → α) → α)) → (α → α) Сх. акс. 2
// (3) (α → ((α → α) → α)) → (α → α) M.P. 1,2
// (4) (α → ((α → α) → α)) Сх. акс. 1
// (5) α → α M.P. 4,3


std::pair<std::vector<expr_t>, int> alphaImpl(expr_t expression, int currentIndex) {
    string e = destroySpaces2(expression->prefix_form());
    expr_t ano = parse(destroySpaces2(e+"->"+e));
    std::vector<expr_t> ans;

    expr_t buff = makeAxiom1(expression, expression);
    buff->val = {1, -1, "Ax"};
    ans.push_back(buff);

    buff = makeAxiom2(expression, ano, expression);
    buff->val = {2, -1, "Ax"};
    ans.push_back(buff);

    buff = parse("(" + e + "->((" + e + "->" + e + ")->" + e + "))->(" + e + "->" + e + ")");
    buff->val = {currentIndex, currentIndex + 1, "MP"};
    ans.push_back(buff);

    buff = makeAxiom1(expression, ano);
    buff->val = {1, -1, "Ax"};
    ans.push_back(buff);

    ano->val = {currentIndex + 3, currentIndex + 2, "MP"};
    ans.push_back(ano);

    currentIndex += 5;
    return {ans, currentIndex};
}

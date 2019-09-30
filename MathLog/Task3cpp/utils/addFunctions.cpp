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


// A
// (A -> (!A -> A))
// (!A -> A)
// (!A -> (!A -> !A))
// ((!A -> (!A -> !A)) -> ((!A -> ((!A -> !A) -> !A)) -> (!A -> !A)))
// ((!A -> ((!A -> !A) -> !A)) -> (!A -> !A))
// (!A -> ((!A -> !A) -> !A))
// (!A -> !A)
// ((!A -> A) -> ((!A -> !A) -> !!A))
// ((!A -> !A) -> !!A)
// !!A

void hypAndClassAx(expr_t expression) {
    expr_t neg = makeNeg(expression);
    string e = destroySpaces2(expression->prefix_form()), n = destroySpaces2(neg->prefix_form());
    expr_t ano = parse(n+"->"+n);
    // vector<expr_t> ans;
    // ans.push_back(expression);
    // ans.push_back(makeAxiom1(expression,neg));
    // ans.push_back(parse(n+"->"+e));
    // ans.push_back(makeAxiom1(neg,neg));
    // ans.push_back(makeAxiom2(neg,ano,neg));
    // ans.push_back(parse("((" + n + "->((" + n + "->" + n + ")->" + n + "))->(" + n + "->" + n + "))"));
    // ans.push_back(makeAxiom1(neg,ano));
    // ans.push_back(ano);
    // ans.push_back(makeAxiom9(neg,expression));
    // ans.push_back(parse("((" + n + "->" + n + ")->!" + n + ")"));
    // ans.push_back(parse(!n));
    // return ans;

    cout << e << "\n";
    cout << makeAxiom1(expression, neg)->prefix_form() << "\n";
    cout << "(" << n << " -> " << e << ")\n";
    cout << makeAxiom1(neg, neg)->prefix_form() << "\n";
    cout << makeAxiom2(neg, ano, neg)->prefix_form() << "\n";
    cout << "((" << n << " -> ((" << n << " -> " << n << ") -> " << n << ")) -> (" << n << " -> " << n << "))\n";
    cout << makeAxiom1(neg, ano)->prefix_form() << "\n";
    cout << ano->prefix_form() << "\n";
    cout << makeAxiom9(neg, expression)->prefix_form() << "\n";
    cout << "((" << n << "->" << n << ") -> !" << n << ")\n";
    cout << "!" << n << "\n";
}



// (1) α → (α → α) Сх. акс. 1
// (2) (α → (α → α)) → (α → ((α → α) → α)) → (α → α) Сх. акс. 2
// (3) (α → ((α → α) → α)) → (α → α) M.P. 1,2
// (4) (α → ((α → α) → α)) Сх. акс. 1
// (5) α → α M.P. 4,3


void alphaImpl(expr_t expression) {
    string e = destroySpaces2(expression->prefix_form());
    expr_t ano = parse(destroySpaces2(e+"->"+e));
    // std::vector<expr_t> ans;
    // ans.push_back(makeAxiom1(expression,expression));
    // ans.push_back(expression,ano,expression);
    // ans.push_back(parse("(" + e + "->((" + e + "->" + e + ")->" + e + "))->(" + e + "->" + e + ")"));
    // ans.push_back(makeAxiom1(expression, ano));
    // ans.push_back(parse(e+"->"+e));
    // return ans;
    cout << makeAxiom1(expression, expression)->prefix_form() << "\n";
    cout << makeAxiom2(expression, ano, expression)->prefix_form() << "\n";
    cout << "(" << e << " -> ((" << e << " -> " << e << ") -> " << e << ")) -> (" << e << " -> " << e << ")\n";
    cout << makeAxiom1(expression, ano)->prefix_form() << "\n";
    cout << e << " -> " << e << "\n";
}

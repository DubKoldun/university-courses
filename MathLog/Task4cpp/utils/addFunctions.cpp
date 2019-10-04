

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


// contrposition "(A -> B) -> (A -> !B) -> !A",
//            "A -> B", +1
//            "(A -> !B) -> !A", +2
//            "!B -> (A -> !B)", +3
//            "!B", +4
//            "A -> !B",
//            "!A"


std::pair<std::vector<expr_t>, int> contrposition (expr_t first, expr_t second, int currentIndex) {
    std::vector<expr_t> ans;
    std::string a = first->prefix_form(), b = second->prefix_form();
    expr_t neb = parse(destroySpaces2("!" + b));

    expr_t buff = makeAxiom9(a,b);
    buff->val = {9, -1, "Ax"};
    ans.push_back(buff);

    buff = std::make_shared<implication>(a, b);
    buff->val = {1, -2, "Hyp"};
    ans.push_back(buff);

    buff = std::parse(destroySpaces2("(" + a + "->!" b + ")" + "->!" + a));
    buff->val = {currentIndex + 1, currentIndex, "MP"};
    ans.push_back(buff);

    buff = makeAxiom1(a,neb);
    buff->val = {1, -1, "Ax"};
    ans.push_back(buff);

    neb->val = {2, -2, "Hyp"};
    ans.push_back(val);

    buff = parse(destroySpaces2(a + "->!" + b));
    buff->val = {currentIndex + 4, currentIndex +3, "MP"};
    ans.push_back(buff);

    buff = parse(destroySpaces2("!" + a));
    buff->val = {currentIndex + 5, currentIndex +2, "MP"};
    ans.push_back(buff);

    currentIndex += 7;
    return {ans, currentIndex};
}

std::pair<std::vector<expr_t>,int> exMiddle()

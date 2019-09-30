#include "features.cpp"

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
            ans.emplace_back(std::pair<expr_t, int>({expr, current->second}));
            break;
        }
        case (0) : {
            ans.emplace_back(std::pair<expr_t, int>({expr, current->second}));
            break;
        }
        default: {
            ans.emplace_back(std::pair<expr_t, int>({expr, current->second}));
            int a = expr->val.a, b = expr->val.b;
            auto buff1 = reverseProvesMap.find(a), buff2 = reverseProvesMap.find(b);
            recovery(reverseProvesMap, provesMap, buff1->second, ans);
            recovery(reverseProvesMap, provesMap, buff2->second, ans);
        }
    }
}

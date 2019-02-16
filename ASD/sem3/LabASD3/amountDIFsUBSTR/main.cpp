#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;


int main() {
    std::string s;
    cin >> s;

    std::reverse(s.begin(),s.end());

    vector <size_t> pref_func(s.size());

    size_t max = 0, amount = 0;

    for (size_t i = 1; i < pref_func.size(); ++i) {
        size_t j = pref_func[i-1];
        while (j > 0 && s[i] != s[j]) {
            j = pref_func[j-1];
        }
        if (s[i] == s[j]) ++j;
        pref_func[i] = j;
        max = std::max(j,max);
        amount
    }

    return 0;
}
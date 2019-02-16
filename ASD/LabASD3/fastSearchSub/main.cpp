#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

int main() {
    std::string s1, s2;
    cin >> s1 >> s2;
    std::string s = s1 + '#' + s2;

    vector <size_t> z_func(s.size());
    vector <size_t> ans;
    for (size_t i = 1, left = 0, right = 0; i < z_func.size(); ++i) {
        if (i <= right) {
            z_func[i] = std::min(right - i +1, z_func[i-left]);
        }
        while (i+z_func[i] < z_func.size() && s[z_func[i]] == s[i + z_func[i]])
            ++z_func[i];
        if (i + z_func[i]-1 > right) {
            left = i;
            right = z_func[i] +i -1;
        }
        if (z_func[i] == s1.size())
            ans.push_back(i -s1.size());
    }

    cout << ans.size() << "\n";
    for (auto const& item: ans) {
        cout << item << " ";
    }
    return 0;
}
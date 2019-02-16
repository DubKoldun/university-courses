#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

int main() {
    std::string s;
    cin >> s;

    vector <size_t> z_func(s.size());
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
        cout << z_func[i] << " ";
    }
    return 0;
}
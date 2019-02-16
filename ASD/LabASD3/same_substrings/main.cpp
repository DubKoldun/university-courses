#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cin;

int main() {
    string s;
    size_t requestAmount;
    cin >> s >> requestAmount;

    vector <size_t> pows(s.size());
    vector <size_t> hash(s.size());

    pows[0] = 1;
    int hashNumb = 103;
    hash[0] = pows[0] * (s[0] - 'a' + 1);

    for (size_t i = 1; i != s.size(); ++i) {
        pows[i] = pows[i-1] * hashNumb;
        hash[i] = pows[i] * (s[i] - 'a' + 1);
        hash[i] += hash[i-1];
    }

    for (size_t i = 0; i < requestAmount; ++i) {
        size_t hash1, hash2, left1, right1, left2 ,right2;
        cin >> left1 >> right1 >> left2 >> right2;
        hash1 = hash[--right1];
        if (--left1) hash1 -= hash[left1-1];
        hash2 = hash[--right2];
        if (--left2) hash2 -= hash[left2-1];

        if((left1 <= left2 && hash1*pows[left2 - left1] == hash2) || (left1 > left2 && hash1 == hash2*pows[left1 - left2]))
            cout << "Yes\n";
        else cout << "No\n";

    }

    return 0;
}
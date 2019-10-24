#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

static const long long MOD = 1000000000 + 7;

int main() {
    long long k, m;
    cin >> k >> m;
    vector<bool> exist(m+1);

    for (size_t i = 0; i < k; ++i) {
        int buff;
        cin >> buff;
        exist[buff] = true;
    }

    vector <long long> answer(2001,0);
    vector <long long> sumWeightTree(2001,0);

    answer[0] = 1;
    sumWeightTree[0] = 1;

    for (size_t i = 1; i < m + 1; ++i) {
        long long buff = 0;
        for (size_t j = 1; j < i + 1; ++j) {
            if (!exist[j]) continue;
            buff += (sumWeightTree[i - j]) % MOD;
            buff %= MOD;
        }

        answer[i] = buff % MOD;

        cout << answer[i] << " ";

        for(size_t j = 0; j < i + 1; ++j) {
            sumWeightTree[i] += (answer[i - j] * answer[j]) % MOD;
            sumWeightTree[i] %= MOD;
        }
    }

    return 0;
}
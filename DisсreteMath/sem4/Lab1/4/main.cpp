#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cin;

long long C(long long n, long long k) {
    double res = 1;
    for (long long i = 1; i < k + 1; ++i)
        res = res * (n - k + i) / i;
    return (long long) (res + 0.01);
}

vector<long long> genfuncPair(vector<long long> const &variety1, vector<long long> const &variety2) {
    vector<long long> ans(7);
    for (size_t i = 0; i < ans.size(); ++i) {
        for (size_t j = 0; j < i + 1; ++j) {
            ans[i] += variety1[j] * variety2[i - j];
        }
    }
    return ans;
}

vector<long long> genfuncSeq(vector<long long> const &variety) {
    vector<long long> ans(7);
    ans[0] = 1;
    for (size_t i = 1; i < ans.size(); ++i) {
        for (size_t j = 1; j < i + 1; ++j) {
            ans[i] += variety[j] * ans[i - j];
        }
    }
    return ans;
}

vector<long long> genfuncMultiset(vector<long long> const &variety) {

    vector<long long> ans(7);
    ans[0] = 1;

    vector<vector<long long>> buff(7,vector<long long>(7));

    for (size_t i = 0; i < buff.size(); ++i) buff[0][i] = 1;

    for (size_t i = 1; i < buff.size(); ++i) {
        for (size_t j = 1; j < buff.size(); ++j) {
            for (size_t k = 0; k < i/j + 1; ++k) {
                buff[i][j] += C(variety[j] + k - 1, k) * buff[i - k * j][j - 1];
            }
        }
        ans[i] = buff[i][i];
    }
    return ans;
}

vector<long long> parsing(string func) {
    switch (func[0]) {
        case 'B': {
            vector<long long> variety(7);
            variety[0] = 0, variety[1] = 1;
            return variety;
        }
        case 'P': {
            func = func.substr(2, func.size() - 3);
            string first, second;
            size_t i = 0, flag = 0;
            while (func[i] != ',') {
                if (func[i] == 'P') ++flag;
                first.push_back(func[i]);
                ++i;
                if (func[i] == ',' && flag != 0) {
                    --flag;
                    first.push_back(func[i++]);
                }
            }
            ++i;
            while (i < func.size()) {
                second.push_back(func[i]);
                ++i;
            }
            return genfuncPair(parsing(first), parsing(second));
        }
        case 'S': {
            func = func.substr(2, func.size() - 3);
            return genfuncMultiset(parsing(func));
        }
        case 'L': {
            func = func.substr(2, func.size() - 3);
            return genfuncSeq(parsing(func));
        }
        default:
            cout << "Something wet wrong";
            return vector<long long>(0);
    }
};

int main() {
    string func;
    cin >> func;
    vector<long long> ans = parsing(func);
    for (auto i: ans) cout << i << " ";
    return 0;
}

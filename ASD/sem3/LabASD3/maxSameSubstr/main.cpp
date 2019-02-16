#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using std::vector;
using std::string;
using std::cout;
using std::cin;


string string1, string2;
std::pair<long long,long long> answer;

long long MAX = pow(2,60);

vector <long long> pows;

void calculationsHashs(vector<long long> & hash, string const& s) {
    int hashNumb = 37;
    hash[0] = s[0];

    for (long long i = 1; i != s.size(); ++i) {
        hash[i] += s[i];
        hash[i] %= MAX;
        if (hash[i] < 0) hash[i] += MAX;
        hash[i] += (hash[i-1] * hashNumb) % MAX;
        hash[i] %= MAX;
        if (hash[i] < 0) hash[i] += MAX;
    }
}


bool checkSubstr(vector<long long> const& hash1, vector<long long> const& hash2, int size) {
    std::set <long long> hash2Substr;

    for (int i = 0; i < hash2.size() - size; ++i) {
        long long hash = hash2[i + size];
        if (i){
            hash -= (hash2[i - 1] * pows[size + 1]) % MAX;
            hash %= MAX;
            if (hash < 0) hash += MAX;
        }
        hash2Substr.insert(hash);
    }

    for (long long i = 0; i < hash1.size() - size; ++i) {
        long long hash = hash1[i + size];
        if (i) {
            hash -= (hash1[i - 1] * pows[size + 1]) % MAX;
            hash %= MAX;
            if (hash < 0) hash += MAX;
        }
        if (hash2Substr.find(hash) != hash2Substr.end()) {
            //if (string1[i] == string2[i] && string1[i+size-1] == string1[i+size-1]) {
                answer = std::make_pair(i, i + size);
                return true;
            //}
        } else continue;
    }
    return false;
}

void binSearch(vector<long long> const& hash1, vector<long long> const& hash2) {
    int left = -1;
    int right = static_cast<int>(std::min(hash1.size(),hash2.size()));
    while (left < right - 1) {
        int middle = left- (left-right)/ 2;
        if (checkSubstr(hash1,hash2, middle)) left = middle;
        else right = middle;
    }
}

int main() {

    freopen("common.in","r",stdin);
    freopen("common.out","w",stdout);

    cin >> string1 >> string2;

    pows.resize(std::max(string2.size(),string1.size()));
    vector <long long> hashs1(string1.size());
    vector <long long> hashs2(string2.size());


    int hashNumb = 37;
    pows[0] = 1;
    for (long long i = 1; i != pows.size(); ++i) {
        pows[i] = (pows[i - 1] * hashNumb) % MAX;
        pows[i] %= MAX;
        if (pows[i] < 0) pows[i] += MAX;
    }

    calculationsHashs(hashs1,string1);
    calculationsHashs(hashs2,string2);

    binSearch(hashs1,hashs2);

    for (long long i = answer.first; i < answer.second + 1; ++i) {
        cout << string1[i];
    }


    return 0;
}





























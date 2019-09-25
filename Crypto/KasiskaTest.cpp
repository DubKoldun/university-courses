#include <algorithm>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;

double indexAlpha (string text, size_t period) {
    vector <double> currentAlpha(26);
    size_t currentSize = 0;
    for (size_t i = 0; i < text.size(); i += period) {
        ++currentAlpha[text[i]-'a'];
        ++currentSize;
    }

    double ans = 0;

    for (auto i : currentAlpha) {
        ans += pow(i/(double)currentSize,2);
    }

    return ans;
}

int main() {
    string text;
    cin >> text;
    size_t period = 0, maxPeriod = 0;
    double max = 0;

    while (period != text.size()) {
        value = indexAlpha(text, ++period)
        if (max < value) {
            max = value;
            maxPeriod = period;
        }
    }
}

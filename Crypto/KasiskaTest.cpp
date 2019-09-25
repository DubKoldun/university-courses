#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::cout;
using std::cin;

double indexAlpha(string text, size_t period)
{
    vector<double> currentAlpha(26);
    size_t currentSize = 0;
    for (size_t i = 0; i < text.size(); i += period)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            size_t shift = 'a';
            if (text[i] >= 'A' && text[i] <= 'Z') { shift = 'A'; }
            ++currentAlpha[text[i] - shift];
            ++currentSize;
        }
    }

    double ans = 0;

    for (auto i : currentAlpha)
    {
        ans += pow(i / (double) currentSize, 2);
    }

    return ans;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    string text = "";
    string token;
    while (cin >> token)
    {
        text += token;
    }
    size_t period = 0, maxPeriod = 0;
    double max = 0;

    while (period <= 17)
    {
        auto value = indexAlpha(text, ++period);
        cout << value << std::endl;
        if (value > max)
        {
            max = value;
            maxPeriod = period;
        }
    }
    cout << max;
    return 0;
}

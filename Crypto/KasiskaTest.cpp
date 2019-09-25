#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::cout;
using std::cin;

const size_t MAX_PERIOD = 17;
const size_t ALPHABET_LENGTH = 26;
vector<vector<char>> vigenereSquare(ALPHABET_LENGTH, vector<char>(ALPHABET_LENGTH));

void generateVigenereSquare()
{
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i)
    {
        for (size_t j = 0; j < ALPHABET_LENGTH; ++j)
        {
            vigenereSquare[i][j] = ('A' + j + i > 'Z' ? ('A' + j + i - ALPHABET_LENGTH) : ('A' + j + i));
        }
    }
}

void printVigenereSquare()
{
    for (size_t i = 0; i < vigenereSquare.size(); ++i)
    {
        for (char c : vigenereSquare[i])
        {
            cout << c << ' ';
        }
        cout << std::endl;
    }
}


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
    generateVigenereSquare();
    //printVigenereSquare();
    //cout << "Enter a key: "; we use file input so it is TODO to make interface more nice (to be possible to enter the key in console)
    string key;
    cin >> key;

    string text = "";
    string token;
    while (cin >> token)
    {
        text += token;
    }
    //delete all symbols except 'a'..'z' and 'A'..'Z' from the input text and then make all chars big xd (u know, like 'a' -> 'A" and 'b' -> 'B'...)
    for (size_t i = 0; i < text.size(); ++i)
    {
        if (!((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')))
        {
            text.erase(i, 1);
        }
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = text[i] - 'a' + 'A';
        }
    }
    cout << text << std::endl;
    //now encrypt the text
    string cipherText = "";
    for (size_t i = 0; i < text.size(); ++i)
    {
        //                                                                                                                                                      yourtextishereqwert
        cipherText += vigenereSquare[text[i] - 'A'][key[i % key.size()]- 'A']; //key[i % key.size()] means.. u know, when u write your key under your text like keykeykeykeykeykeyke , it returns the index of the key's char, that comes under the your current text char
    }
    cout << cipherText << std::endl;
    size_t period = 0;
    double maxValue = 0, maxPeriod;

    while (period <= MAX_PERIOD)
    {
        auto value = indexAlpha(text, ++period);
        //cout << value << ' ' << period << std::endl; //here we should try different ways to look for the period (the closest to 0.065 ...)
        if (value > maxValue)
        {
            maxValue = value;
            maxPeriod = period;
        }
    }
    cout << "We have found the period: " << maxPeriod << std::endl;
    return 0;
}

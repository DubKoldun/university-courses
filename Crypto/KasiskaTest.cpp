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
const double NASHE_CHISLO = 0.065;
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
    vector<double> currentAnswers;
    for (size_t p = 0; p < period; ++p)
    {
        size_t currentSize = 0;
        for (size_t i = p; i < text.size(); i += period)
        {
            ++currentAlpha[text[i] - 'A'];
            ++currentSize;
        }

        double ans = 0;

        for (double i : currentAlpha)
        {
            ans += pow(i / (double) currentSize, 2);
        }
        //return ans;
        currentAnswers.push_back(ans);
        currentAlpha = vector<double>(26);
    }
    double sum = 0;
    for (double cur : currentAnswers)
    {
        sum += cur;
    }

    return (sum / currentAnswers.size());
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
            --i;
        }
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = text[i] - 'a' + 'A';
        }
    }
    //cout << text << std::endl;
    //now encrypt the text
    string cipherText = "";
    for (size_t i = 0; i < text.size(); ++i)
    {
        //                                                                                                                                                      yourtextishereqwert
        cipherText += vigenereSquare[text[i] - 'A'][key[i % key.size()]- 'A']; //key[i % key.size()] means.. u know, when u write your key under your text like keykeykeykeykeykeyke , it returns the index of the key's char, that comes under the your current text char
    }
    //cout << cipherText << std::endl;
    size_t period = 0;
    double minDif = 1e9, truePeriod;

    while (period <= MAX_PERIOD)
    {
        double value = indexAlpha(text, ++period);
        //cout << value << ' ' << period << std::endl;
        double dif = value - NASHE_CHISLO;
        if (dif < 0)
        {
            dif *= -1;
        }
        if (dif < minDif)
        {
            minDif = dif;
            truePeriod = period;
        }
    }
    cout << "We have found the period: " << truePeriod << " (MAGIC PZDC)" << std::endl;
    return 0;
}

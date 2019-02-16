// C++ program for building suf array of a given text
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cin;


struct suf
{
    int index;
    int rang[2];
};


vector <int> buildSufArray(string s)
{
    vector <suf> suffixs;
    suf suffixes[s.size()];

    for (int i = 0; i < s.size(); i++)
    {
        suffixes[i].index = i;
        suffixes[i].rang[0] = s[i] - 'a';
        suffixes[i].rang[1] = ((i+1) < s.size())? (s[i + 1] - 'a'): -1;
    }

    std::sort(suffixes, suffixes+s.size(), [](auto a, auto b) { return (a.rang[0] == b.rang[0])? (a.rang[1] < b.rang[1] ?1: 0):
                                                                (a.rang[0] < b.rang[0] ?1: 0);});

    int ind[s.size()];

    for (int k = 4; k < 2*s.size(); k *= 2)
    {
        int rang = 0;
        int prev_rang = suffixes[0].rang[0];
        suffixes[0].rang[0] = rang;
        ind[suffixes[0].index] = 0;

        // Assigning rang to suffixes
        for (int i = 1; i < s.size(); i++)
        {
            // If first rang and next rangs are same as that of previous
            // suf in array, assign the same new rang to this suf
            if (suffixes[i].rang[0] == prev_rang &&
                suffixes[i].rang[1] == suffixes[i-1].rang[1])
            {
                prev_rang = suffixes[i].rang[0];
                suffixes[i].rang[0] = rang;
            }
            else // Otherwise increment rang and assign
            {
                prev_rang = suffixes[i].rang[0];
                suffixes[i].rang[0] = ++rang;
            }
            ind[suffixes[i].index] = i;
        }

        // Assign next rang to every suf
        for (int i = 0; i < s.size(); i++)
        {
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rang[1] = (nextindex < s.size())?
                                  suffixes[ind[nextindex]].rang[0]: -1;
        }

        // Sort the suffixes according to first k characters 
        std::sort(suffixes, suffixes+s.size(), [](auto a, auto b) { return (a.rang[0] == b.rang[0])? (a.rang[1] < b.rang[1] ?1: 0):
                                                               (a.rang[0] < b.rang[0] ?1: 0);});
    }

    vector<int> answer(s.size());
    for (int i = 0; i < s.size(); i++)
        answer[i] = suffixes[i].index;

    return std::move(answer);
}


int main() {
    string s;
    cin >> s;
    vector <int> sufArray(s.size());

    sufArray = buildSufArray(s);

    for (auto const& item: sufArray) {
        cout << item + 1 << " ";
    } cout << "\n";


    return 0;
} 
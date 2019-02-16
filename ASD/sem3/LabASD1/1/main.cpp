#include <iostream>
#include <vector>
#include <algorithm>

#define cout std::cout
#define cin std::cin

std::vector<std::vector<int>> graf;
std::vector<uint8_t> usedColors;
std::vector<int> answer;

bool cycleCheck(int);
void topSort(int);


int main() {
    int amountEdges, amountV;
    cin >> amountV >> amountEdges;
    graf.resize(amountV);
    usedColors.resize(amountV);
    int numberVOne, numberVTwo;
    while(amountEdges > 0){
        --amountEdges;
        cin >> numberVOne;
        cin >> numberVTwo;
        graf[numberVOne-1].push_back(numberVTwo-1);
    }

    bool flagCycle = false;
    for (int i = 0; i < amountV; ++i){
        if(usedColors[i] != 2) {
            if (cycleCheck(i)) {
                cout << -1;
                flagCycle = true;
                break;
            }
        }
    }

    if(!flagCycle) {
        for (unsigned char &usedColor : usedColors) usedColor = 0;

        for (int i = 0; i < amountV; ++i) {
            if (usedColors[i] != 2){
                topSort(i);
            }
        }

        std::reverse(answer.begin(), answer.end());
        for (int &i : answer) cout << ++i << " ";

    }

    return 0;
}

bool cycleCheck(int v) {
    usedColors[v] = 1;
    for (auto i: graf[v]){
        if(usedColors[i] == 0)
            cycleCheck(i);

        if(usedColors[i] == 1)
            return true;
    }
    usedColors[v] = 2;
    return false;
}

void topSort(int v) {
    usedColors[v] = 2;
    for (auto i: graf[v]){
        if(usedColors[i] != 2){
            topSort(i);
        }
    }
    answer.push_back(v);
}




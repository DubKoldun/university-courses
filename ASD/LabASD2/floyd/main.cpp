#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

vector <vector<int>> graf;


int main() {
    int amountV;
    cin >> amountV;

    graf.resize(amountV);
    for (auto &item: graf){
        item.resize(amountV);
    }

    for (auto &i: graf){
        for (auto &j: i){
            cin >> j;
        }
    }

    for (int i = 0; i < amountV; ++i){
        for (int j = 0; j < amountV; ++j){
            for (int k = 0; k < amountV; ++k){
                graf[j][k] = std::min(graf[j][k], graf[j][i] + graf[i][k]);
            }
        }
    }

    for (auto &i: graf){
        for (auto &j: i){
            cout << j << " ";
        } cout << "\n";
    }

    return 0;
}
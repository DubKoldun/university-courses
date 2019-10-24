#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <fstream>
#include <algorithm>

using std::cout;
using std::cin;

std::ifstream in("chvatal.in");
std::ofstream out("chvatal.out");

std::vector <std::vector<bool>> graf;
std::queue <int> buffQueue;
std::deque <int> currentDeque, buffDeque;

int main() {
    int amountV;
    std::string v1;
    in >> amountV;
    graf.resize(static_cast<unsigned long>(amountV));
    for (auto &i : graf) {
        i.resize(static_cast<unsigned long>(amountV));
    }

    for (int i = 1; i < amountV; ++i){
        in >> v1;
        for (int j = 0; j < v1.size(); ++j){
            graf[i][j] = v1[j] - '0';
            graf[j][i] = v1[j] - '0';
        }
    }

    for (int i = 0; i < amountV; ++i) currentDeque.push_back(i);

    for (int i = 0; i < amountV*(amountV-1); ++i){
        int vF = currentDeque.front();
        int vS = currentDeque[1];
        if (!graf[vF][vS]){
            size_t j;
            for (j = 2; (!graf[vF][currentDeque[j]] || !graf[vS][currentDeque[j + 1]]) &&
                j < amountV - 1; ++j) {}

            if (j == amountV - 1) {
                for (j = 2; !graf[vF][currentDeque[j]]; ++j) {}
            }
            std::reverse(currentDeque.begin() + 1, currentDeque.begin() + j + 1);
        }
        currentDeque.pop_front();
        currentDeque.push_back(vF);
    }


    for (; !currentDeque.empty();){
        out << currentDeque.front()+1 << " ";
        currentDeque.pop_front();
    }
    return 0;
}
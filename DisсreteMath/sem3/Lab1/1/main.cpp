#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <fstream>

using std::cout;
using std::cin;

std::ifstream in("fullham.in");
std::ofstream out("fullham.out");

std::vector <std::vector<bool>> graf;
std::queue <int> buffQueue;
std::deque <int> currentDeque;

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
        currentDeque.pop_front();
        int vS = currentDeque.front();
        if (!graf[vF][vS]){
            buffQueue.push(currentDeque.front());
            currentDeque.pop_front();
            while (!graf[vF][buffQueue.back()] || !graf[vS][currentDeque.front()]){
                buffQueue.push(currentDeque.front());
                currentDeque.pop_front();
            }
            while(!buffQueue.empty()){
                currentDeque.push_front(buffQueue.front());
                buffQueue.pop();
            }
        }
        currentDeque.push_back(vF);
    }


    for (; !currentDeque.empty();){
        out << currentDeque.front()+1 << " ";
        currentDeque.pop_front();
    }
    return 0;
}
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

std::ifstream in("matching.in");
std::ofstream out("matching.out");

using std::vector;

vector <bool> used;
vector <vector<int>> graf;
vector <int> answer;
vector <int> last;
vector <std::pair<int,int>> order;

bool TYANKA(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (auto const& to: graf[v]) {
        if (answer[to] == -1 || TYANKA(answer[to])) {
            answer[to] = v;
            last[v] = to;
            return true;
        }
    }
    return false;
}
int main() {
    int amountV;

    in >> amountV;


    for (int i = 0 ; i < amountV; ++i) {
        int w;
        in >> w;
        order.emplace_back(w,i);
    }

    std::sort(order.begin(), order.end(), [](auto p, auto q){ return p.first > q.first; });

    //for (auto item: order) std::cout << item.first << " " << item.second <<"\n";

    graf.resize(amountV);

    for (auto &item: graf) {
        int localAmountE;
        in >> localAmountE;
        for (int j = 0; j < localAmountE; ++j) {
            int v;
            in >> v;
            item.emplace_back(--v);
        }
    }

    used.resize(amountV);
    answer.resize(amountV, -1);
    last.resize (amountV, -1);

    for (auto item: order) {

        used[0] = true;

        for (auto &&item1 : used) {
            item1 = false;
        }

        TYANKA(item.second);
    }



    for (auto item : last) {
        out << item + 1 << " ";
    } out<<"\n";

    return 0;
}
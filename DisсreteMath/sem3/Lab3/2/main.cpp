#include <fstream>
#include <vector>
#include <set>

using std::vector;
using std::set;

std::ifstream in("destroy.in");
std::ofstream out("destroy.out");

static long long INF = 9000000000000000000;

#define Pair std::pair<long long,int>

vector <vector<Pair>> graf;
vector <bool> used;
set <Pair> answer;
set <int> lastAns;

int main() {
    int amountV, amountE, amount = 0;
    long long maxSum;
    in >> amountV >> amountE >> maxSum;


    graf.resize(amountV, vector<Pair>(amountV,std::make_pair(INF,-1)));
    vector <long long> minE(amountV, INF);
    used.resize(amountV);

    for (int i = 0; i < amountE; ++i){
        int v1,v2;
        long long w;
        in >> v1 >> v2 >> w;

            graf[--v1][--v2] = std::make_pair(-w, i);
            graf[v2][v1] = std::make_pair(-w, i);

        answer.insert(std::make_pair(w,i));
    }

    minE[0] = 0;

    for (int i = 0; i < amountV; ++i) {
        int v1 = -1;
        for (int j = 0; j < amountV; ++j) {
            if (!used[j] && (v1 == -1 || minE[j] < minE[v1]))
                v1 = j;
        }

        used[v1] = true;

        for (int v2 = 0; v2 < amountV; ++v2) {
            if (graf[v1][v2].first < minE[v2]) {
                minE[v2] = graf[v1][v2].first;
                answer.erase(std::make_pair(-graf[v1][v2].first,graf[v1][v2].second));
            }
        }

    }

    for (auto pos = answer.begin(); pos != answer.end() && maxSum >= 0; ++pos){
        maxSum -= pos->first;
        if (maxSum >= 0) {
            lastAns.insert(pos->second);
            ++amount;
        }
    }

    out << amount << "\n";

    for (auto const& item: lastAns) {
        out << item+1 << " ";
    }
    return 0;
}
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::set;

std::ifstream in("destroy.in");
std::ofstream out("destroy.out");


#define Pair std::pair<long long,long long>
#define make std::make_pair
#define weight first.first
#define index first.second
#define V1 second.first
#define V2 second.second

vector <std::pair<Pair,Pair>> graf;
vector<int> p;
set <Pair> used;

int get (int v) {
    return (v == p[v]) ? v : (p[v] = get (p[v]));
}

void unite (int a, int b) {
    a = get (a);
    b = get (b);
    if (a != b)
        p[a] = b;
}

int main() {
    int amountV, amountE, amount = 0;
    long long maxSum;
    in >> amountV >> amountE >> maxSum;

    p.resize(amountV);

    for (int i = 0; i < amountE; ++i) {
        int v1, v2;
        long long w;
        in >> v1 >> v2 >> w;
        graf.emplace_back(make(make(-w, i), make(--v1, --v2)));
        used.insert(make(w, i));
    }

    std::sort(graf.begin(), graf.end(), [](auto p, auto q) { return p.weight < q.weight; });

    for (int i = 0; i < p.size(); ++i) {
        p[i] = i;
    }

    for (int i = 0; i < amountE; ++i) {
        if (get(graf[i].V1) != get(graf[i].V2)) {
            used.erase(used.find(make(-graf[i].weight, graf[i].index)));
            unite(graf[i].V1, graf[i].V2);
        }
    }

    set<int> last;

    for (auto pos = used.begin(); pos != used.end() && maxSum >= 0; ++pos) {
        maxSum -= pos->first;
        if (maxSum >= 0) {
            last.insert(pos->second);
            ++amount;
        }
    }


    out << amount << "\n";

    for (auto const &item: last) {
        out << item + 1 << " ";
    }
    return 0;
}
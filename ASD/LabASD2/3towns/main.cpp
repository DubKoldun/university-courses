#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::cout;
using std::cin;
using std::pair;
using std::set;
using std::min;

typedef pair<long long,long long> Pair;


long long amountV, amountE;

vector <bool> used;
vector <long long>  distanceA, distanceB, distanceC;
vector <vector<Pair>> graf;

const long long INF = 1000000000000000001;

set<Pair> dei;


#define weight item.second
#define SECOND item.first

void deikstra(long long v, vector<long long>& distance){

    for (auto k: used) k = false;

    dei.clear();
    dei.insert(Pair(0,v));

    distance[v] = 0;

    while (!dei.empty()){
        auto buff = dei.begin();
        while (used[buff->second] && !dei.empty()){
            dei.erase(dei.begin());
            if(dei.empty())
                return;
            buff = dei.begin();
        }

        long long v1 = buff->second;
        used[v1] = true;

        for (const auto &item: graf[v1]){
            if (distance[v1] + weight < distance[SECOND]) {
                distance[SECOND] = distance[v1] + weight;
                dei.insert(Pair(distance[SECOND],SECOND));
            }
        }

    }

}


int main() {
    long long a, b, c;
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> amountV >> amountE;
    distanceA.resize(amountV,INF);
    distanceB.resize(amountV,INF);
    distanceC.resize(amountV,INF);
    used.resize(amountV);
    graf.resize(amountV);

    for (long long i = 0; i < amountE; ++i){
        long long v1, v2, w;
        cin >> v1 >> v2 >> w;
        --v1, --v2;
        graf[v1].push_back(Pair(v2,w));
        graf[v2].push_back(Pair(v1,w));
    }
    cin >> a >> b >> c;
    --a, --b, --c;
    deikstra(a, distanceA);
    deikstra(b, distanceB);
    deikstra(c, distanceC);


    long long ans1 = min(distanceA[b] + distanceB[c],
                   distanceA[c] + distanceC[b]);

    long long ans2 = min(distanceB[a] + distanceA[c],
                   distanceB[c] + distanceC[a]);

    long long ans3 = min(distanceC[a] + distanceA[b],
                   distanceC[b] + distanceB[a]);

    long long ans = min(min(ans1,ans2),ans3);



    if (ans >= INF) cout << -1; else cout << ans;
    return 0;
}
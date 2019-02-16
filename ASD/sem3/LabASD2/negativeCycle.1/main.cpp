#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;

int mINF = -100000000;
int INF = 100000;

class e{
public:
    int v1, v2, w;
    e (int v11,int v22,int w1);
};

e::e(int v11, int v22, int w1): v1(v11), v2(v22), w(w1) {

}

typedef e* edge;

vector<int> distance;
vector<int> parents;
vector<edge> edges;



int main() {
    int amountV;
    cin >> amountV;
    parents.resize(amountV,-1);
    distance.resize(amountV);


    for (int i = 0; i < amountV; ++i){
        for (int j = 0; j < amountV; ++j){
            int w;
            cin >> w;
            if (w != INF) {
                auto k = new e(i, j, w);
                edges.push_back(k);
            }
        }
    }

    int v = -1;

    for (int i = 0; i < amountV; ++i){
        v = -1;
        for (auto &item: edges){
            if(distance[item->v2] > distance[item->v1] + item->w){
                distance[item->v2] = std::max(mINF,distance[item->v1] + item->w);
                parents[item->v2] = item->v1;
                v = item->v2;
            }
        }
    }

    if (v == -1) cout << "NO"; else {
        int next = v;
        for (int i = 0; i < parents.size(); ++i){
            next = parents[next];
        }

        vector<int> ans;
        int current = next;
        while (current != next || ans.empty()){
            ans.push_back(current+1);
            current = parents[current];
        }

        std::reverse(ans.begin(), ans.end());

        cout << "YES\n";
        cout << ans.size() << "\n";
        for (auto item: ans) cout << item << " ";

    }






    return 0;
}
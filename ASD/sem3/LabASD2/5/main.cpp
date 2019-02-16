#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

const long long INF = 8000000000000000000;

class e{
public:
    int v1 = 0;
    int v2 = 0;
    long long weight = INF;
    e (int v12, int v22, long long w);
};

e::e(int v12, int v22, long long w): v1(v12), v2(v22), weight(w){}

typedef e* edge;

vector <edge> edges;
vector <vector <int>> graf;
vector <bool> used1, used2;

vector <long long> path, checkPATH;

void dfs(int v, vector<bool> &used){
    used[v] = true;
    for (auto item: graf[v]) {
        if(!used[item]) dfs (item, used);
    }
}


int main(){
    int amountV, amountE, start;
    cin >> amountV >> amountE >> start;
    --start;

    graf.resize(amountV);
    path.resize(amountV, INF + 1000000000000000000);
    checkPATH.resize(amountV);
    used1.resize(amountV);
    used2.resize(amountV);


    path[start] = 0;


    for(int i = 0; i < amountE; ++i){
        int v1, v2;
        long long w;
        cin >> v1 >> v2 >> w;
        --v1, --v2;

        edge buff = new e(v1,v2,w);
        edges.push_back(buff);

        graf[v1].push_back(v2);
    }


    dfs(start, used1);

    for(int j = 0; j < amountV - 1; ++j){
        for(auto item: edges){
            if (used1[item->v2] && (path[item->v1] < INF) && (path[item->v2] > path[item->v1] + item->weight)) {
                path[item->v2] = std::max(-INF, path[item->v1] + item->weight);
            }
        }
    }

    checkPATH = path;

    for(auto item: edges){
        if (used1[item->v2] && (checkPATH[item->v1] < INF) && (checkPATH[item->v2] > checkPATH[item->v1] + item->weight)) {
            checkPATH[item->v2] = std::max(-INF, checkPATH[item->v1] + item->weight);
        }
    }


    for (int i = 0; i < amountV; ++i) {
        if (used1[i] && checkPATH[i] != path[i]) {
            dfs(i, used2);
        }
    }

    for(int i = 0; i < amountV; ++i){

        if(path[i] >= INF){
            cout << "*\n";
            continue;
        }

        if(used2[i]){
            cout << "-\n";
            continue;
        }
        cout << path[i] << "\n";
    }

    return 0;
}
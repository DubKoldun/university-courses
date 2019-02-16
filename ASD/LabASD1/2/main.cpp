#include <iostream>
#include <vector>
#include <algorithm>

#define cout std::cout
#define cin std::cin
#define vector std::vector

vector<vector<std::pair<int,int>>> graf;
vector<int> timesIn;
vector<int> answer;
vector<bool> used;
vector<int> up;
int amountE, amountV, currentTime = 0;

void dfs(int v, int p){
    used[v] = true;
    ++currentTime;
    timesIn[v] = currentTime;
    up[v] = currentTime;
    for (auto i: graf[v]){
        if(i.first == p) continue;
        if(used[i.first]){
            up[v] = std::min(up[v], timesIn[i.first]);
        } else {
            dfs(i.first,v);
            up[v] = std::min(up[v],up[i.first]);
            if(up[i.first] > timesIn[v])
                answer.emplace_back(i.second);
        }

    }

}

void searchBridge(){
    for (int i = 0; i < amountV; ++i){
        if(!used[i]){
            dfs(i,-1);
        }
    }
}


int main() {
    int v1, v2;
    cin >> amountV >> amountE;
    used.resize(amountV);
    graf.resize(amountV);
    timesIn.resize(amountV);
    up.resize(amountV);
    int buff = amountE;
    while (amountE > 0){
        --amountE;
        cin >> v1 >> v2;
        --v1, --v2;
        graf[v1].push_back(std::pair<int,int>(v2,buff-amountE));
        graf[v2].push_back(std::pair<int,int>(v1,buff-amountE));
    }

    searchBridge();

    cout << answer.size() << "\n";


    std::sort(answer.begin(),answer.end());
    for (auto i: answer) cout << i << "\n";
    return 0;
}

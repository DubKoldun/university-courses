#include <iostream>
#include <vector>
#include <algorithm>

#define cout std::cout
#define cin std::cin
#define vector std::vector

vector<vector<int>> graf;
vector<int> timesIn;
vector<int> answer;
vector<bool> used;
vector<bool> usedDot;
vector<int> up;
int amountE, amountV, currentTime = 0;

void dfs(int v, int p){
    used[v] = true;
    ++currentTime;
    timesIn[v] = currentTime;
    up[v] = currentTime;
    int child = 0;
    for (auto i: graf[v]){
        if(i == p) continue;
        if(used[i]){
            up[v] = std::min(up[v], timesIn[i]);
        } else {
            dfs(i,v);
            up[v] = std::min(up[v],up[i]);
            if((up[i] >= timesIn[v] && p != -1) && !usedDot[v])
                answer.emplace_back(v), usedDot[v] = true;
            ++child;
        }
    }
    if ((p == -1 && child > 1)&&!usedDot[v]) usedDot[v] = true, answer.emplace_back(v);

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
    usedDot.resize(amountV);
    while (amountE > 0){
        --amountE;
        cin >> v1 >> v2;
        --v1, --v2;
        graf[v1].push_back(v2);
        graf[v2].push_back(v1);
    }

    searchBridge();

    cout << answer.size() << "\n";

    std::sort(answer.begin(),answer.end());
    for (auto i: answer) cout << i+1 << " ";
    return 0;
}

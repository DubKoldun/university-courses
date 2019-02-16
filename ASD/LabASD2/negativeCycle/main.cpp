#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using std::vector;
using std::cin;
using std::cout;

vector <vector<int>> graf;
std::unordered_set <int> ans;
vector <bool> used;

int INF = 100000;
int mInf = -1000000;

void dfs(int v){
    used[v] = true;
    for (int i = 0; i < graf[v].size(); ++i){
        //if (graf[v][i] < INF){
            ans.insert(i+1);
            if (!used[i]) dfs(i);
    }
}

int main() {
    int amountV;
    cin >> amountV;

    graf.resize(amountV, vector<int>(amountV));

    for (auto &i: graf){
        for (auto &j: i){
            cin >> j;
        }
    }

    for (int i = 0; i < amountV; ++i){
        for (int j = 0; j < amountV; ++j){
            for (int k = 0; k < amountV; ++k){
                graf[j][k] = std::max(mInf,std::min(graf[j][k], graf[i][j] + graf[j][i]));
            }
        }
    }

    for (int i = 0; i < amountV; ++i){
        for (int j = 0; j < amountV; ++j){
            for (int k = 0; k < amountV; ++k){
                if (graf[j][i] < INF && graf[i][k] < INF && graf[i][i] < 0)
                    graf[j][k] = mInf;
            }
        }
    }



    used.resize(amountV);

    for (int i = 0; i < amountV; ++i){
        if (graf[i][i] < 0){
            dfs(i);
            break;
        }
    }

    if (ans.empty()) cout << "NO"; else {
        cout << "YES\n";
        cout << ans.size() << "\n";
        //std::reverse(ans.begin(), ans.end());
        for (auto i: ans) cout << i << " ";
    }

    return 0;
}
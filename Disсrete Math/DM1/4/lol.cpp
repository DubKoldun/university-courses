#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
vector <int> queue, ans;
vector <vector <int>> graph;

ifstream fin("guyaury.in");
ofstream fout("guyaury.out");
int n, index;


void blinchik(int l, int r, int i){
    if(l == r){
        queue.insert(queue.begin() + l, i);
    }
    else if(graph[i][queue[(l + r >> 1) % queue.size()]]){
        blinchik(l, (l + r >> 1) % queue.size(), i);
    }
    else{
        blinchik((l + r >> 1) + 1, r, i);
    }
}


void solution_2(){
    graph.resize(n);
    for(int i = 0; i < n; i++){
        graph[i].resize(n);
    }
    string s;
    graph[0][0] = 0;
    queue.push_back(0);
    for(int i = 1; i < n; i++){
        fin >> s;
        graph[i][i] = 0;
        for(int j = 0; j < i; j++){
            if(s[j] == '1'){
                graph[j][i] = 0;
                graph[i][j] = 1;
            }
            else{
                graph[j][i] = 1;
                graph[i][j] = 0;
            }
        }
    }
    if(n > 1){
        if(graph[0][1] == 1){
            queue.push_back(1);
        }else{
            queue.insert(queue.begin(), 1);
        }
        while(queue.size() < n){
            int siz  = queue.size();
            blinchik(0, siz, siz);
        }
    }
    index = n - 1;
    while(index > 0){
        if(graph[queue[index]][queue[0]]){
            break;
        }
        index--;
    }
    ans.insert(ans.begin(), queue.begin(), queue.begin() + index + 1);
    queue.erase(queue.begin(), queue.begin() + index + 1);
    for (auto i = queue.begin(); i != queue.end();) {
        auto t = ans.begin();
        while (t != ans.end() && graph[*t][*i]) {
            ++t;
        }
        if (t != ans.end()) {
            ans.insert(t, queue.begin(), i + 1);
            queue.erase(queue.begin(), i + 1);
            i = queue.begin();
        } else {
            i++;
        }
    }
    for(int i = 0; i < n; i++){
        fout << ans[i] + 1 << " ";
    }
}

int main(){
    fin >> n;
    solution_2();
    return 0;
}
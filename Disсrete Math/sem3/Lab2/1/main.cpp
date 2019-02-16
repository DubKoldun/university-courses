#include <iostream>
#include <vector>
#include <fstream>

using std::cin;
using std::cout;
using std::vector;

//std::ifstream govno("in.in");

struct e{
    int start, end, index;
    char orientation;
    e(): start(0), end(0), orientation(true), index(0){}
    e(int s, int e, int i, char o = -1): start(s), end(e), orientation(o), index(i){}
}; typedef e* edge;

vector <edge> edges;

vector <int> hamilCycleOnOX;
vector <bool> usedEdges;

char isIntersect(const edge &a, const edge &b) {
    char ifClause = (hamilCycleOnOX[b->start] > hamilCycleOnOX[a->start] && hamilCycleOnOX[a->end] < hamilCycleOnOX[b->end] && hamilCycleOnOX[a->end] > hamilCycleOnOX[b->start]);
    char anyWayIfClause = (hamilCycleOnOX[b->end] < hamilCycleOnOX[a->end] && hamilCycleOnOX[b->start] < hamilCycleOnOX[a->start]) && hamilCycleOnOX[b->end] > hamilCycleOnOX[a->start] ;
    return  ifClause || anyWayIfClause;

}


char splitEdges(edge edge1, char currentOrientation) {

    if (usedEdges[edge1->index])
        return edge1->orientation == currentOrientation;

    usedEdges[edge1->index] = true;
    edge1->orientation = currentOrientation;

    for (auto &item: edges){
        if(!isIntersect(edge1,item) || !isIntersect(item,edge1)) continue;

        if(!splitEdges(item,!currentOrientation))
            return false;
    }

    return true;
}


int main() {
    int amountV, amountE;
    cin >> amountV >> amountE;

    hamilCycleOnOX.resize(amountV);
    usedEdges.resize(amountE, false);

    for (int i = 0; i < amountE; ++i) {
        int v1, v2;
        cin >> v1 >> v2;
        edge newE = new e(v1-1, v2-1, i);
        edges.push_back(newE);
    }


    for (int i = 0; i < amountV; ++i) {
        int v1;
        cin >> v1;
        hamilCycleOnOX[v1 - 1] = i;
    }

    char flag = false;

    for (auto &item: edges){
        if(hamilCycleOnOX[item->start] > hamilCycleOnOX[item->end])
            std::swap(item->start,item->end);
    }

    for (auto &item: edges){
        if (!usedEdges[item->index]) {
            if (splitEdges(item,true)) {

            } else {
                cout << "NO\n";
                flag = true;
                return 0;
                break;
            }
        }
    }


    cout << "YES\n";
    for (auto& item: hamilCycleOnOX) {
        cout << item << " 0 ";
    }
    cout << "\n";
    for (auto& item: edges) {
        //cout << item ->start;

        double medium = static_cast<double>(hamilCycleOnOX[item->start]) / 2 +
                        static_cast<double>(hamilCycleOnOX[item->end]) / 2;
        cout << medium << " ";

        if (!item->orientation) cout << static_cast<double>(hamilCycleOnOX[item->end]) - medium << "\n";
        else cout << -(static_cast<double>(hamilCycleOnOX[item->end]) - medium) << "\n";
    }

    return 0;
}





















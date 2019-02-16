#include <iostream>
#include <vector>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::vector;

vector<int> buffer, cycle;
vector<vector<bool>> graf;

ifstream in("guyaury.in");
ofstream out("guyaury.out");


void search(int left, int right, int i) {
    if (left == right) {
        buffer.insert(buffer.begin() + left, i);
        return;
    }

    int middle = (left + right) / 2;

    if (graf[i][buffer[middle]]) {
        search(left, middle, i);
    } else {
        search(middle + 1, right, i);
    }
}

void findCycle(int amountV) {
    if (amountV > 1) {
        if (graf[0][1]) {
            buffer.push_back(1);
        } else {
            buffer.insert(buffer.begin(), 1);
        }
    }

    while (buffer.size() < amountV) {
        int size = buffer.size();
        search(0, size, size);
    }

    int v = amountV - 1;
    while (v > 0) {
        if (graf[buffer[v]][buffer[0]]) {
            break;
        }
        --v;
    }

    cycle.insert(cycle.begin(), buffer.begin(), buffer.begin() + v + 1);
    buffer.erase(buffer.begin(), buffer.begin() + v + 1);

    for (auto i = buffer.begin(); i != buffer.end();) {
        auto t = cycle.begin();

        while ((t != cycle.end()) && (graf[*t][*i])) ++t;

        if (t != cycle.end()) {
            cycle.insert(t, buffer.begin(), i + 1);
            buffer.erase(buffer.begin(), i + 1);
            i = buffer.begin();
        } else ++i;
    }
}

int main() {
    int amountV;
    std::string v1;

    in >> amountV;
    graf.resize(amountV);

    for (auto& i: graf) i.resize(amountV);
    buffer.push_back(0);

    for (int i = 1; i < amountV; ++i) {
        in >> v1;
        for (int j = 0; j < i; ++j) {
            if (v1[j] - '0') {
                graf[j][i] = false;
                graf[i][j] = true;
            } else {
                graf[j][i] = true;
                graf[i][j] = false;
            }
        }
    }

    findCycle(amountV);

    for (auto i: cycle) out << i + 1 << " ";

    return 0;
}
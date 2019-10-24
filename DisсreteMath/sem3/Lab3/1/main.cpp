//#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
//#include <iostream>

using std::vector;
using std::pair;

std::ifstream in ("schedule.in");
std::ofstream out("schedule.out");

vector <pair<long long,long long>> tasks;
std::multiset <long long> used;

int main() {
    int amountT, i = -1;
    long long answer = 0;
    in >> amountT;
    while (++i != amountT) {
        long long t1, t2;
        in >> t1 >> t2;
        tasks.emplace_back(t1,t2);
        answer += t2;
    }

    std::sort (tasks.begin(), tasks.end(), [](auto p, auto q){ return p.first < q.first ;});

    int current = 1;

    for (auto const& item: tasks) {
        if (item.first == 0) continue;
        if (item.first >= current) used.insert(item.second), ++current, answer -= item.second;
        else {
            long long min = *used.begin();
            if (min < item.second) {
                answer += min;
                answer -= item.second;
                used.erase(used.begin());
                used.insert(item.second);
            }
        }
    }


    out << answer;

    return 0;
}
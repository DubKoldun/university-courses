#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;

vector<int> lamps;

int main() {
    int amountLamps;
    std::string s;
    cin >> amountLamps;
    lamps.push_back(1);
    cout.flush();


    while (lamps.size() != amountLamps) {
        unsigned size = lamps.size();
        int i = size + 1, left = 0, right = size - 1;
        int middle;
        while ((left <= right)) {
            middle = (left + right) / 2;
            cout.flush();
            cout << "1 " << i << " " << lamps[middle] << "\n";
            cout.flush();
            cin >> s;
            if (s == "YES") {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
        if (s == "YES") {
            lamps.insert(lamps.begin() + middle, i);
        } else {
            lamps.insert(lamps.begin() + middle + 1, i);
        }
    }

    cout.flush();
    cout << "0 ";
    for (auto i: lamps) cout << i << " ";


    return 0;
}
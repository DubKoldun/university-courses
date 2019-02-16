#include <iostream>
#include <vector>
#include <cmath>

#define cout std::cout
#define cin std::cin
#define vector std::vector

double MAX = 1000000000000;
double answer = 0;

vector <std::pair<int,int>> field;
vector <bool> used;

double distance(std::pair<int,int> const &a, std::pair<int,int> const &b){
    return std::sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

int main() {
    unsigned amountV;
    cin >> amountV;

    vector <double> d(amountV,MAX);
    used.resize(amountV);

    for (int i = amountV; i > 0; --i){
        int x1, x2;
        cin >> x1 >> x2;
        field.emplace_back(x1,x2);
    }

    d[0] = 0;

    for (auto i: field){
        int min = -1;
        for (int j = 0; j < amountV; ++j)
            if (!used[j] && (min == -1 || d[j] < d[min])) min = j;
        used[min] = true;
        answer += d[min];
        for (int j = 0; j < amountV; ++j){
            double currentD = distance(field[min],field[j]);
            if (d[j] > currentD)
                d[j] = currentD;
        }

    }

    cout << answer;


    return 0;
}
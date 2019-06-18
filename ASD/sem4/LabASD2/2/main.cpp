#include <iostream>
#include <vector>
#include <fstream>

std::ifstream in("assignment.in");
std::ofstream out("assignment.out");

static const long long INF = 1000000000000000000;

//void unused(std::vector<bool> &used, std::vector<long long> &min) {
//
//    for (auto &&j : used) {
//        j = false;
//    }
//
//    for (auto &&i: min) {
//        i = INF;
//    }
//}

std::pair<long long, std::vector<long long>>
greedy(long long n, std::vector<std::vector<long long>> & graph) {


    std::vector<long long> way(n + 1);
    std::vector<long long> match(n + 1);
    std::vector<long long> start(n + 1);
    std::vector<long long> finish(n + 1);


    for (int i = 1; i < n + 1; ++i) {

        std::vector<long long> min(n + 1, INF);
        std::vector<bool> used(n + 1);

        match[0] = i;

        long long cur = 0;

        do {

            used[cur] = true;
            long long curr_path = match[cur];
            long long add = INF;
            long long next = 0;

            for (int j = 1; j < n + 1; ++j) {

                if (!used[j]) {

                    long long current = graph[curr_path][j] - start[curr_path] - finish[j];

                    if (current < min[j]) {
                        min[j] = current;
                        way[j] = cur;
                    }

                    if (min[j] < add) {
                        add = min[j];
                        next = j;
                    }
                }
            }

            for (int j = 0; j < n + 1; ++j) {

                if (used[j]) {
                    start[match[j]] += add;
                    finish[j] -= add;
                } else {
                    min[j] -= add;
                }
            }
            cur = next;
        } while (match[cur] != 0);

        do {

            long long next = way[cur];
            match[cur] = match[next];
            cur = next;

        } while (cur);
    }

    long long sum = 0;
    std::vector<long long> answer;

    for (int j = 1; j < n + 1; ++j) {
        answer.push_back(match[j]);
        sum += graph[match[j]][j];
    }

    return {sum,answer};
}

int main() {

    long long n;

    in >> n;

    std::vector<std::vector<long long>> graph(n + 1, std::vector<long long>(1));

    for(auto i : graph){
        graph[0].push_back(0);
    }

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            long long a;
            in >> a;
            graph[i].push_back(a);
        }
    }

    auto ans = greedy(n,graph);

    out << ans.first << "\n";

    for (size_t j = 0; j < ans.second.size(); ++j) {
        out << ans.second[j] << " " << j+1 << "\n";
    }

    return 0;
}
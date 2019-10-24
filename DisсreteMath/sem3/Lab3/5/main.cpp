#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <iostream>

std::ifstream in("cycles.in");
std::ofstream out("cycles.out");

using std::vector;
std::queue<int> helpQueue;

vector<std::pair<int, int>> weights;
vector<bool> unionS;

int main() {
    long long answer = 0;
	int forceX, forceS;
	in >> forceX >> forceS;

	unionS.resize(static_cast<unsigned long>(1 << forceX));

    for (int i = 0; i < forceX; ++i) {
		int weight;
		in >> weight;
		weights.emplace_back(weight,i);
	}



    std::sort(weights.begin(), weights.end(), std::greater<std::pair<int, int>>());

    //for (auto item: weights) std::cout << item.first;


	for (int i = 0; i < forceS; ++i) {
		int current = 0, size;
		in >> size;

		for (int j = 0; j < size; ++j) {
		    int shift;
			in >> shift;
			--shift;
			current |= static_cast<int>(pow(2,shift));
		}

		unionS[current] = true;
		helpQueue.push(current);

	}




	while (!helpQueue.empty()) {
		int current = helpQueue.front();
		helpQueue.pop();

		for (int i = 0; i < forceX; ++i) {
		    int pow = 1 << i;
			if ((current & pow) == 0) {
				current |= pow;
				if (!unionS[current]) {
					unionS[current] = true;
					helpQueue.push(current);
				}
				current &= ~(pow);
			}
		}
	}



    int current = 0;
	for (int i = 0; i < forceX; ++i) {
	    int pow = 1 << weights[i].second;
		if (!unionS[current | pow]) {
			current |= pow;
			answer += weights[i].first;
		}
	}

	out << answer;


	return 0;
}
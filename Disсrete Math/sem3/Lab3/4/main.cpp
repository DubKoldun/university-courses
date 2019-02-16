//#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>


std::ifstream in("check.in");
std::ofstream out("check.out");

#define sizeV second.size()
#define full(name, name1) for(auto i : name->second){xexcepts[i] = true;} for(auto i : name1->second){xexcepts[i] = false;}
#define fullcheck(name) for (int i = 0; i < amountX; i++) { if (xexcepts[i]) check1 |= (family.find(name->first | (1 << i)) != family.end());}


using std::vector;

std::unordered_map<int, vector<int>> family;
vector<bool> check;



int main() {


    int amountX, amountFamily;
    in >> amountX >> amountFamily;

    int sizeForX = static_cast<int>(std::pow(2, amountX));
    check.resize(static_cast<unsigned long>(sizeForX), true);


    bool itHasEmpty = false;

    for (int i = 0; i < amountFamily; i++) {
        int size, current = 0;
        in >> size;


        vector<int> v;

        if (size == 0) {
            itHasEmpty = true;
            family.insert(std::make_pair(current, v));
            continue;
        }


        for (int j = 0; j < size; j++) {
            int element;
            in >> element;
            --element;
            current |= static_cast<int>(pow(2,element));
            v.emplace_back(element);
        }

        family.insert(std::make_pair(current, v));
    }

    if (!itHasEmpty) {
        out << "NO";
        return 0;
    }



    for (int i = 1; i < sizeForX; i++) {
        int currentIndex = 0, pow = 1 << currentIndex;

        check[i] = (family.find(i) != family.end());

        while (pow < i + 1) {
            int current = i & (~(pow));
            check[i] = check[current] & check[i];
            ++currentIndex;
            pow = 1 << currentIndex;
        }
    }

    for (auto &it : family)
        if (!check[it.first]) {
            out << "NO";
            return 0;
        }


    for (auto elX = family.begin(); elX != family.end(); ++elX) {
        for (auto ElS = elX; ElS != family.end(); ++ElS) {


            vector<bool> xexcepts(amountX);
            bool check1 = false;

            if (elX->sizeV > ElS->sizeV) {

                full(elX,ElS)

                fullcheck(ElS)

                if (!check1) {
                    out << "NO";
                    return 0;
                }


            } else if (elX->sizeV < ElS->sizeV) {

                full(ElS,elX)

                fullcheck(elX)

                if (!check1) {
                    out << "NO";
                    return 0;
                }

            }

        }
    }
    out << "YES";
    return 0;
}
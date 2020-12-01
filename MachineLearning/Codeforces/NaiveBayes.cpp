#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::log;

template <typename T>
void print(T const& mass) {
    for (auto const& i: mass) {
        cout << i << " ";
    }
}

int main() {
    int class_am, train_am;
    long double smooth_intense;
    cin >> class_am;

    vector<long double> penalties(class_am);
    for (auto & i: penalties) {
        cin >> i;
    }

    cin >> smooth_intense >> train_am;

    vector<unordered_map<string, long double>> conditional_probabilities(class_am);
    vector<long double> class_doc_am(class_am, 0);
    unordered_set<string> word_set;

    for (int i = 0; i < train_am; ++i) {
        int cur_class = 0, b = 0;
        cin >> cur_class >> b;
        class_doc_am[--cur_class] += 1;
        unordered_set<string> buff;

        for (int j = 0; j < b; ++j) {
            string cur_word = "";
            cin >> cur_word;
            word_set.insert(cur_word);

            if (conditional_probabilities[cur_class].find(cur_word) != conditional_probabilities[i].end()) {
                if (buff.find(cur_word) != buff.end()) 
                    continue;
                conditional_probabilities[cur_class][cur_word] += 1;
                buff.insert(cur_word);
            } else {
                conditional_probabilities[cur_class][cur_word] = 1;
                buff.insert(cur_word);
            }

        }

    }

    for (int i = 0; i < conditional_probabilities.size(); ++i) {
        for (auto const& key: word_set) {
            if (conditional_probabilities[i].find(key) != conditional_probabilities[i].end()) {
                conditional_probabilities[i][key] = (conditional_probabilities[i][key] + smooth_intense) / (class_doc_am[i] + 2 * smooth_intense);
            } else {
                conditional_probabilities[i][key] = smooth_intense / (class_doc_am[i] + 2 * smooth_intense);
            }

        }
    }

    int test_am = 0;
    cin >> test_am;
    vector<vector<long double>> answers(test_am, vector<long double>(class_am, 1.0));
    
    for (int i = 0; i < test_am; ++i) {
        int mess_am = 0;
        cin >> mess_am;
        unordered_set<string> buff;
        long double denom = 0.0;

        for (int j = 0; j < mess_am; ++j) {
            string cur_mess = "";
            cin >> cur_mess;
            buff.insert(cur_mess);
        } 

        for (int j = 0; j < class_am; ++j) {
            answers[i][j] = penalties[j] * class_doc_am[j];

            for (auto const& elem: conditional_probabilities[j]) {
                // cout << elem.first;
                answers[i][j] *= buff.find(elem.first) != buff.end() ? elem.second : 1.0 - elem.second; 
            }

            denom += answers[i][j];
        }

        for (int j = 0; j < class_am; ++j) {
            cout << std::setprecision(10) << answers[i][j] / denom << " ";
        }
        cout << "\n";
    }

}


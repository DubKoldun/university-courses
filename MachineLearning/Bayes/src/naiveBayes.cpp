#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

// #include "NaiveBayes.h"

using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::log;

void naiveBayes(int nth, const char* from, const char* to) {
    std::ifstream in;
    in.open(from);
    std::ofstream out;
    out.open(to);


    int class_am, train_am;
    long double smooth_intense;
    in >> class_am;
    // cout << class_am;

    vector<long double> penalties(class_am);
    for (auto & i: penalties) {
        in >> i;
    }

    in >> smooth_intense >> train_am;

    vector<unordered_map<string, long double>> conditional_probabilities(class_am);
    vector<long double> class_doc_am(class_am, 0);
    unordered_set<string> word_set;

    for (int i = 0; i < train_am; ++i) {
        int cur_class = 0, b = 0;
        in >> cur_class >> b;
        class_doc_am[--cur_class] += 1;
        unordered_set<string> buff;

        for (int j = 0; j < b; ++j) {
            string cur_word = "", buff_z = "";
            for (int z = 0; z < nth, j < b; ++z, ++j) {
                in >> buff_z;
                cur_word += buff_z;
            }
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
    in >> test_am;
    vector<vector<long double>> answers(test_am, vector<long double>(class_am, 1.0));
    
    for (int i = 0; i < test_am; ++i) {
        int mess_am = 0;
        in >> mess_am;
        unordered_set<string> buff;
        long double denom = 0.0;

        for (int j = 0; j < mess_am; ++j) {
            string cur_mess = "", buff_z = "";
            for (int z = 0; z < nth, j < mess_am; ++z, ++j) {
                in >> buff_z;
                cur_mess += buff_z;
            }
            buff.insert(cur_mess);
        } 

        for (int j = 0; j < class_am; ++j) {
            answers[i][j] = penalties[j] * class_doc_am[j];

            for (auto const& elem: conditional_probabilities[j]) {
                // out << elem.first;
                answers[i][j] *= buff.find(elem.first) != buff.end() ? elem.second : 1.0 - elem.second; 
            }

            denom += answers[i][j];
        }

        for (int j = 0; j < class_am; ++j) {
            out << std::setprecision(10) << answers[i][j] / denom << " ";
        }
        out << "\n";
    }

}

void some(int s, char * path) {
    std::ofstream myfile;
    myfile.open (path);
    cout << path;
    
    if(!myfile) 
        cout << "Something went wrong with file";
    
    myfile << "Writing this to a file.\n" << s;
    myfile.close();
}

extern "C" {
    // void some2(int kek) { some(kek); }
    void some2(int nth, char * path){ 
        printf("%s\n", path);
        some(nth, path);
    }

    void NaiveBayes(int nth, char* from, char* to) { naiveBayes(nth, from, to); }
}

int main() {
    string path_from = "/home/vutaliy/prod/university-courses/MachineLearning/Bayes/test/test1";
    string path_to = "/home/vutaliy/prod/university-courses/MachineLearning/Bayes/ans";

    int nth = 1;

    naiveBayes(nth, path_from.c_str(), path_to.c_str());

}
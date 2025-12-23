#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

using std::vector, std::string, std::cout;

template<typename T>
class ReportGenerator {
private:
    vector<T> data;
public:
    ReportGenerator(const vector<T>& d) : data(d) {}

    void sortByMarks() {
        sort(data.begin(), data.end(), [](const T& a, const T& b){
            return a.second > b.second; // pair<string,int> student, marks
        });
    }

    void printReport() {
        for (auto& r : data) {
            cout << r.first << " : " << r.second << "\n";
        }
    }
};

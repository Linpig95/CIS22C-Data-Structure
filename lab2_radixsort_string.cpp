#include "Linzhu_lab_util.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int get_length(string value)
{
    return value.length();
}

int getMax(vector<string> v)
{
    int max_digits = 0;
    for (auto e : v)
    {
        auto digit_count = get_length(e);
        if (digit_count > max_digits)
        {
            max_digits = digit_count;
        }
    }
    return max_digits;
}

void radix_sort(vector<string>& v)
{
    vector<DList<string>> buckets(128);
    int max_digits = getMax(v);
    for (auto digit_index = 0; digit_index < max_digits; digit_index++) {
        for (auto i = 0; i < v.size(); i++) {
            auto bucket_index = static_cast<int>(*(v[i].end()-digit_index-1));
            buckets[bucket_index].append(make_shared<ListNode<string>>(v[i]));
        }
        auto array_index = 0;
        for (auto i = 0; i < 128; i++) {
            for (auto j = 0; j < buckets[i].size(); j++) {
                v[array_index++] = buckets[i][j];
            }
        }
        buckets = vector<DList<string>>(128);
    }
}

int main() 
{
    vector<string> array_str;
    string info = "";
    ifstream inputFile;
    inputFile.open("Numbers.txt", ios::in);
    if (inputFile.fail()) {
        cerr << "Could not find file" << endl;
    }
    while(inputFile){
        getline(inputFile, info);
        array_str.push_back(info);
    }
    inputFile.close();
    cout << "after sort" << endl;
    radix_sort(array_str);
    for (auto e : array_str) {
        cout << e << endl;
    }
    cout << endl;
}


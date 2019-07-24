#include "Linzhu_lab_util.h"
#include <fstream>
#include <iostream> 
#include <vector>
#include <iomanip>
using namespace std; 

int get_length(int value)
{
    if (value == 0) {
        return 1;
    }
    int digits = 0;
    while (value != 0) {
        digits += 1;
        value /= 10;
    }
    return digits;
}

int radix_get_max_length(vector<int> v)
{
    int max_digits = 0;
    for (auto e : v) {
        auto digit_count = get_length(e);
        if (digit_count > max_digits) {
            max_digits = digit_count;
        }
    }
    return max_digits;
}
void radix_sort(vector<int>& v)
{
    vector<DList<int>> buckets(10);
    int max_digits = radix_get_max_length(v);
    auto pow10 = 1;
    for (auto digit_index = 0; digit_index < max_digits; digit_index++) {
        for (auto i = 0; i < v.size(); i++) {
            auto bucket_index = abs(v[i] / pow10) % 10;
            buckets[bucket_index].append(make_shared<ListNode<int>>(v[i]));
        }
        auto array_index = 0;
        for (auto i = 0; i < 10; i++) {
            for (auto j = 0; j < buckets[i].size(); j++) {
                v[array_index++] = buckets[i][j];
            }
        }
        pow10 *= 10;
        buckets = vector<DList<int>>(10);
    }
}


int main() 
{
    vector<int> array;
    int nums;
    ifstream inputFile;
    inputFile.open("Numbers.txt", ios::in);
    if (inputFile.fail()) {
        cerr << "Could not find file" << endl;
    }
    while(inputFile >> nums){
        array.push_back(nums);
    }
    inputFile.close();
    radix_sort(array);
    for (auto e : array) {
        cout << setw(5) <<  e << ' ' << right;
    }
    cout << endl;
}
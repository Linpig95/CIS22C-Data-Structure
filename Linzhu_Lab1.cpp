#include <iostream>
#include <string>
#include <fstream>
#include "Linzhu_lab1_hashtable.h"
using namespace std;

int main(){
    
    ifstream file("Customer.csv");
    if (!file.is_open()) {
        cout << "Failed to open file " << endl;
        return 1;
    }
    ChainingHashTable cht;
    LinearProbingHashTable lpht;
    DoubleHashingHashTable dhht;
    vector<Customer> customers;
    while (file.good())
    {
        string firstname;
        getline(file, firstname, ',');
        string lastname;
        getline(file, lastname, ',');
        string id;
        getline(file, id, '\n');
        Customer c(firstname, lastname, id);
        // cout << "processing " << id << endl;
        customers.push_back(c);
        cht.insert(c);
        lpht.insert(c);
        dhht.insert(c);
    }
    cout << "\nChaining hash table collision times: " << cht.n_collision() << right << endl;
    cout << "\nLinear probing hash table collision times: " << lpht.n_collision() << right << endl;
    cout << "\nDouble hashing hash table collision times: " <<  dhht.n_collision() << right << endl;
    for (auto c : customers) {
        cht.remove(c);
        lpht.remove(c);
    }
    cout << "\nAfter remove: " << endl;
    cout << "Chaining remains " << cht.n_inserted() << endl;
    cout << "Linear probing remains " << lpht.n_inserted() << endl;
    return 0;

}
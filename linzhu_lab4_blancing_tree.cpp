#include "tree_util.h"
#include <fstream>
#include <utility>

int main(int argc, char* argv[])
{
    string filename = argv[1];
    ifstream file1(filename);
    if (!file1.is_open()) {
        cout << "Failed to open file " << endl;
        return 1;
    }
    BinarySearchTree<int> bst;

    int num;
    while (file1.good())
    {
        file1 >> num;
        bst.insert(num);
    }
    file1.close();
    cout << "Before rebalance" << endl;
    bst.printlevel();
    bst.rebalance();
    cout << "After rebalance" << endl;
    bst.printlevel();
    return 0;
}
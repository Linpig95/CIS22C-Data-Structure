#include "tree_util.h"


int main()
{
    BinarySearchTree<int> bst;
    ifstream file("Numbers_test.txt");
    if (!file.is_open()) {
        cout << "Failed to open file " << endl;
        return 1;
    }

    int num;
    while (file.good())
    {
        file >> num;
        bst.insert(num);
    }
    file.close();
    bst.printlevel();
    cout << endl;
    return 0;
}
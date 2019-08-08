#include "Linzhu_lab_util.h"
#include <vector>
#include <list>
#include <limits>
#include <string>
#include <utility>  
using namespace std;
using namespace lin;

int main()
{
    DynamicArray<int> array;
    for (int i = 0; i < 10; i++)
        array.push_back(i);
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << ' ';
    }
    for (int i = 0; i < 10; i++)
    {
        cout << "popping " << array.back() << endl;
        array.pop_back();
    }
    cout << endl;
    cout << "after pop " << endl;
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << ' ';
    }
    cout << endl;
    return 0;
}
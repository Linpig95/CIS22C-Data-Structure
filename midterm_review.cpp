// Problem 1
// Problem 2 and 3 at the end
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Stack
{
private:
    vector<T> arr_;
public:
    void push(T elem) {arr_.push_back(elem);}
    T pop() {T ret = arr_.back(); arr_.pop_back(); return ret;}
    bool empty() { return arr_.empty(); }
};

template <class T>
void print_stack_fifo(Stack<T> s)
{
    cout << "printing stack in fifo order:" << endl;
    Stack<T> tmp;
    while (!s.empty()) {
        tmp.push(s.pop());
    }
    while (!tmp.empty()) {
        cout << tmp.pop() << ' ';
    }
    cout << endl;
}

int main() 
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    print_stack_fifo<int>(s);
    return 0;
}


// Problem 2
/* 
(1 + n + n) * (1 + 2*logn + 1)
O(n*logn)
*/

// Problem 3
/*
Swap and Comparison are the most expensive tasks in the sorting algorithms. 
Selection sort taks at most n times of swpas while bubble sort takes about n/4 times per entry in average.
On comparison, bubbble sort takes k*n where k is the maximum distance between an entry's initial position and
it's final position, while selection sort always takes (n-1)*(n-2)/2 comparisons.
*/
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
#include<iostream>
using namespace std;
template <class T>
struct DlistNode{
    DlistNode(T v)
        : val(v)
    {
    }
    DlistNode()
        : val(0)
    {
    }
    DlistNode<T>* prev;
    DlistNode<T>* next;
    T val;
};
template <class T>
class Dlist{
private:
    DlistNode<T>* head;
    DlistNode<T>* tail;
public:
    Dlist()
        : head(nullptr),
          tail(nullptr)
    {
    }
    ~Dlist(){

    }
    void append(DlistNode<T>* cur){
        if(!head){
            head = cur;
            tail = cur;
        }else{
            tail->next = cur;
            cur->prev = tail;
            tail = cur;
        }
    }
    void print(){
        DlistNode<T>* p = head; 
        while(p){
             cout << p->val << " ";
             p = p->next;
        }
    }
};


int main()
{
    Dlist<int> num;
    num.append(new DlistNode<int>(1));
    num.append(new DlistNode<int>(2));
    num.print();
    return 0;
}
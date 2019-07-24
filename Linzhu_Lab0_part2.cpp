#include "Linzhu_lab_util.h"
#include<string>
template<class T>
class Stack : public DList<T>
{
public:
    void push(shared_ptr<ListNode<T>> newItem)
    {
        this->prepend(newItem);
    }

    shared_ptr<ListNode<T>> pop()
    {
        shared_ptr<ListNode<T>> poppedItem = this->head_;
        this->remove(nullptr);
        return poppedItem;
    }
};
int main()
{
    Stack<string>* route = new Stack<string>();
    route->push(make_shared<ListNode<string>>("Tokyo"));
    route->push(make_shared<ListNode<string>>("Asaka"));
    route->push(make_shared<ListNode<string>>("Nara"));
    cout << "print Result: ";
    route->print();
    cout << endl;
    route->pop();
    cout << "print Result: ";
    route->print();
    cout << endl;
    route->pop();
    cout << "print Result: ";
    route->print();
    cout << endl << endl;

    Stack<int>* item = new Stack<int>();
    item->push(make_shared<ListNode<int>>(45));
    item->push(make_shared<ListNode<int>>(56));
    item->push(make_shared<ListNode<int>>(11));
    cout << "print Result: ";
    item->print();
    cout << endl;
    item->pop();
    cout << "print Result: ";
    item->print();
    cout << endl;

    return 0;
}
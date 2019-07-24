#include "practice-07-22-2019.h"
#include <string>
template <class T>
class Stack : public DList<T>
{
public:
    void push(shared_ptr<DListNode<T>> newItem)
    {
        this->prepend(newItem);
    }

    shared_ptr<DListNode<T>> pop()
    {
        shared_ptr<DListNode<T>> poppedItem = this->head;
        this->remove(nullptr);
        return poppedItem;
    }
};
int main()
{
    shared_ptr<Stack<string>> route = make_shared<Stack<string>>();
    route->push(make_shared<DListNode<string>>("Tokyo"));
    route->push(make_shared<DListNode<string>>("Asaka"));
    route->push(make_shared<DListNode<string>>("Nara"));
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
    route->pop();
    cout << "print Result: ";
    route->print();
    cout << endl << endl;
}
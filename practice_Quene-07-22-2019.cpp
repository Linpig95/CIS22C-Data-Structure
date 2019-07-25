#include"practice-07-22-2019.h"
#include<string>
template <class T>
class Queue : public DList<T>
{
    public:
    void push(shared_ptr<DListNode<T>> newItem)
    {
        this->append(newItem);
    }

    shared_ptr<DListNode<T>> pop()
    {
        shared_ptr<DListNode<T>> poppedItem = this->head;
        this->remove(0);
        return poppedItem;
    }
};

int main() {
    shared_ptr<Queue<string>> WQueue = make_shared<Queue<string>>();
    WQueue->push(make_shared<DListNode<string>>("Mel"));
    WQueue->push(make_shared<DListNode<string>>("Nina"));
    WQueue->push(make_shared<DListNode<string>>("Ruth"));
    cout << "print Result: ";
    WQueue->print();
    cout << endl;
    WQueue->pop();
    cout << "print Result: ";
    WQueue->print();
    cout << endl;
    WQueue->pop();
    cout << "print Result: ";
    WQueue->print();
}
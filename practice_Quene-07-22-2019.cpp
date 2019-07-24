#include"practice-07-22-2019.h"
#include<string>
template <class T>
class Queue : public DList<T>
{
    public:
    void push(shared_ptr<DList<T>> newItem)
    {
        this->append(newItem);
    }

    shared_ptr<DList<T>> pop()
    {
        shared_ptr<DList<T>> poppedItem = head;
        this->remove(head);
        return poppedItem;
    }
};

int main() {
    shared_ptr<Queue<string>> WQueue = new shared_ptr<Queue<string>>();
    WQueue->push(new shared_ptr<DListNode<string>>("Mel"));
    WQueue->push(new DListNode<string>("Nina"));
    WQueue->push(new DListNode<string>("Ruth"));
    cout << "print Result: ";
    WQueue->print();
    cout << endl;
    WQueue->pop();
    cout << "print Result: ";
    WQueue->print();
    cout << endl;
    cout << endl;
}
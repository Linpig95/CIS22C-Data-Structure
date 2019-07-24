#include "Linzhu_lab_util.h"
#include<string>
template <class T>
class Queue : public DList<T>
{
    public:
    void push(ListNode<T> *newItem)
    {
        this->append(newItem);
    }

    ListNode<T>* pop()
    {
        ListNode<T>* poppedItem = this->head_;
        this->remove(0);
        return poppedItem;
    }
};

int main() {
    Queue<string>* WQueue = new Queue<string>();
    WQueue->push(new ListNode<string>("Mel"));
    WQueue->push(new ListNode<string>("Nina"));
    WQueue->push(new ListNode<string>("Ruth"));
    cout << "print Result: ";
    WQueue->print();
    cout << endl;
    WQueue->pop();
    cout << "print Result: ";
    WQueue->print();
    cout << endl;
    cout << endl;

    Queue<int>* newValue = new  Queue<int>();
    newValue->push(new ListNode<int>(17));
    newValue->push(new ListNode<int>(24));
    newValue->push(new ListNode<int>(18));
    cout << "print Result: ";
    newValue->print();
    cout << endl;
    newValue->pop();
    cout << "print Result: ";
    newValue->print();
    cout << endl;
    return 0;
}
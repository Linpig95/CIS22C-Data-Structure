#include <iostream>
#include <memory>
using namespace std;

template <class T>
struct DListNode
{
    DListNode(T v) : val(v) {}
    shared_ptr<struct DListNode> next;
    T val;
};

template <class T>
class DList
{
protected:
    shared_ptr<DListNode<T>> head;
    shared_ptr<DListNode<T>> tail;

public:
    DList()
    {
        head = nullptr;
        tail = nullptr;
    }
    
    ~DList()
    {
        shared_ptr<DListNode<T>> nodePtr;   
        shared_ptr<DListNode<T>> nextNode; 

        nodePtr = head;

        while (nodePtr != nullptr)
        {
            nextNode = nodePtr->next;
            nodePtr = nextNode;
        }
    }
    virtual void append(shared_ptr<DListNode<T>> cur);
    virtual void prepend(shared_ptr<DListNode<T>> cur);
    virtual void remove(shared_ptr<DListNode<T>> cur);
    virtual shared_ptr<DListNode<T>> search(T);

    virtual void print()
    {
        shared_ptr<DListNode<T>> cur = head;
        while (cur)
        {
            cout << cur->val << " ";
            cur = cur->next;
        }
    }
};
template <class T>
void DList<T>::append(shared_ptr<DListNode<T>> cur)
{
    if (!head)
    {
        head = cur;
        tail = cur;
    }
    else
    {
        tail->next = cur;
        tail = cur;
    }
}
template <class T>
void DList<T>::prepend(shared_ptr<DListNode<T>> cur)
{
    if (!head)
    {
        head = cur;
        tail = cur;
    }
    else
    {
        cur->next = head;
        head = cur;
    }
}
template <class T>
void DList<T>::remove(shared_ptr<DListNode<T>> cur)
{
    shared_ptr<DListNode<T>> prev = head;
    while (prev->next != cur) {
        prev = prev->next;
    }
    if (cur == nullptr && head || head == cur)
    {
        head = head->next;
        if (!head)
        {
            tail = nullptr;
        }
    }
    else if (tail == cur)
    {
        prev->next = nullptr;
        tail = prev;
        prev = cur;
    }

    else if (head != cur && tail != cur && !cur)
    {
        prev->next = cur->next;
    }
}

template <class T>
shared_ptr<DListNode<T>> DList<T>::search(T v)
{
    shared_ptr<DListNode<T>> p = head;
    while (p)
    {
        if (p->val == v)
        {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

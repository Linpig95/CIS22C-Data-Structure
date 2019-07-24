#include <iostream>
#include <memory>
using namespace std;
template<class T>
struct ListNode
{
    ListNode(T a) : value(a) {}
    T value;
    std::shared_ptr<struct ListNode> next;
    std::shared_ptr<struct ListNode> prev;
};

enum class EmptyState {
    EMPTY_SINCE_START = 0,
    EMPTY_AFTER_REMOVAL = 1,
    NOT_EMPTY = 2
};

template<class T>
class DList
{
protected:
    std::shared_ptr<ListNode<T>> head_;
    std::shared_ptr<ListNode<T>> tail_;
    uint32_t size_;
    EmptyState empty_state_;

public:
    shared_ptr<ListNode<T>> head() { return head_; }
    bool is_empty() { return !head_; }
    EmptyState empty_state() { return empty_state_; }
    uint32_t size() { return size_; }
    virtual T operator[] (uint32_t i) {
        shared_ptr<ListNode<T>> p = head_;
        auto counter = 0;
        while (p && counter < i) {
            counter++;
            p = p->next;
        }
        return p->value;
    }
    DList()
    {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        empty_state_ = EmptyState::EMPTY_SINCE_START;
    }
    DList(const DList &other)
        : head_(other.head_),
          tail_(other.tail_),
          empty_state_(other.empty_state_)
    {
    }

    ~DList()
    {
        shared_ptr<ListNode<T>> nodePtr;   
        shared_ptr<ListNode<T>> nextNode; 

        nodePtr = head_;

        while (nodePtr != nullptr)
        {
            nextNode = nodePtr->next;
            nodePtr = nextNode;
        }
    }
    void append(shared_ptr<ListNode<T>> newNode);
    void prepend(shared_ptr<ListNode<T>> newNode);
    void remove(shared_ptr<ListNode<T>> curNode);
    shared_ptr<ListNode<T>> search(T);
    void print(){
        printRecursive(head_);
    }

    void printRecursive(shared_ptr<ListNode<T>> node){
        if(node == nullptr){
            return;
        }
        cout << node->value << " ";
        printRecursive(node->next);
    }
};

template <class T>
void DList<T>::append(shared_ptr<ListNode<T>> newNode)
{
    if (head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        tail_->next = newNode;
        newNode->prev = tail_;
        tail_ = newNode;
    }
    size_++;
    empty_state_ = EmptyState::NOT_EMPTY;
}

template <class T>
void DList<T>::prepend(shared_ptr<ListNode<T>> newNode)
{
    if (head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
    }
    size_++;
    empty_state_ = EmptyState::NOT_EMPTY;
}

template <class T>
void DList<T>::remove(shared_ptr<ListNode<T>> curNode)
{
    shared_ptr<ListNode<T>> SucNode;
    shared_ptr<ListNode<T>> PrevNode;
    if (!curNode && head_)
    {
        SucNode = head_->next;
        head_ = SucNode;
        if (head_) head_->prev = nullptr;
        if (!SucNode)
        {
            tail_ = nullptr;
        }
    }
    else
    {
        SucNode = curNode->next;
        PrevNode = curNode->prev;
        if (SucNode != nullptr)
        {
            SucNode->prev = PrevNode;
        }

        if (PrevNode != nullptr)
        {
            PrevNode->next = SucNode;
        }

        if (curNode == head_)
        {
            head_ = SucNode;
        }

        if (curNode == tail_)
        {
            tail_ = PrevNode;
        }
    }
    size_--;
    if (!size_) {
        empty_state_ = EmptyState::EMPTY_AFTER_REMOVAL;
    }
}

template <class T>
shared_ptr<ListNode<T>> DList<T>::search(T v) 
{
    shared_ptr<ListNode<T>> p = head_;
    while (p) {
        if (p->value == v) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}
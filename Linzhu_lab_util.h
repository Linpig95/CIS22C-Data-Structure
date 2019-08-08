#include <iostream>
#include <memory>
#include <ostream>
using namespace std;
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier() : code(FG_DEFAULT) {}
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}
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
    virtual T& operator[] (uint32_t i) {
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

struct Customer {
    string firstName;
    string lastName;
    string id;
    bool operator ==(const Customer& other) {
        return (firstName == other.firstName) &&
            (lastName == other.lastName) && (id == other.id);
    }

    bool operator < (const Customer& other) {
        if (firstName.length() < other.firstName.length()) {
            return true;
        } else if (firstName.length() > other.firstName.length()) {
            return false;
        }
        return firstName < other.firstName;
    }

    bool operator > (const Customer& other) {
        if (firstName.length() > other.firstName.length()) {
            return true;
        } else if (firstName.length() < other.firstName.length()) {
            return false;
        }
        return firstName > other.firstName;
    }
    Customer(){}
    Customer(string f, string l, string id)
        : firstName(f),
          lastName(l),
          id(id)
    {
    }
    friend ostream& operator<<(ostream& os, const Customer&);
};

ostream& operator<<(ostream& os, const Customer& c)
{
    os << c.firstName;
    return os;
}

template <class T>
class DynamicArray : public DList<T>
{
public:
    void push_back(T val) { this->append(make_shared<ListNode<T>>(val)); }
    void push_front(T val) { this->prepend(make_shared<ListNode<T>>(val)); }
    void pop_back() { this->remove(this->tail_); }
    void pop_front() { this->remove(nullptr); }
    bool empty() { return this->is_empty(); }
    T& front() { return this->head_->value; }
    T& back() { return this->tail_->value; }
    void resize(int n)
    {
        int size = this->size();
        if (size > n)
        {
            for (int i = 0; i < size - n; i++)
            {
                pop_back();
            }
        } else if (size < n)
        {
            for (int i = 0; i < n - size; i++)
            {
                push_back(T());
            }
        }
    }
};

template <class T>
class PriorityQueue
{
private:
    int max_n_;
    int n_;
    DynamicArray<int> pq_;
    DynamicArray<int> qp_;
    DynamicArray<T> keys_;

public:
    PriorityQueue(int max_n)
        : n_(0),
          max_n_(max_n)
    {
        qp_.resize(max_n_ + 1);
        pq_.resize(max_n_ + 1);
        keys_.resize(max_n_ + 1);
        for (int i = 0; i <= max_n_; i++)
        {
            qp_[i] = -1;
        }
    }
    bool greater(int i, int j)
    {
        return keys_[pq_[i]] > keys_[pq_[j]];
    }
    void exch(int i, int j)
    {
        int swap = pq_[i];
        pq_[i] = pq_[j];
        pq_[j] = swap;
        qp_[pq_[i]] = i;
        qp_[pq_[j]] = j;
    }
    void swim(int k)
    {
        while (k > 1 && greater(k/2, k)) {
            exch(k, k/2);
            k /= 2;
        }
    }

    void sink(int k)
    {
        while (2 * k <= n_)
        {
            int j = 2*k;
            if (j < n_ && greater(j, j+1)) j++;
            if (!greater(k, j)) break;
            exch(k, j);
            k = j;
        }
    }
    bool empty() { return n_ == 0; }
    int size() { return n_; }
    bool contains(int i) { return qp_[i] != -1; }
    void push(int i, T key)
    {
        if (contains(i)) {
            return;
        }
        n_++;
        qp_[i] = n_;
        pq_[n_] = i;
        keys_[i] = key;
        swim(n_);
    }
    int pop()
    {
        int min = pq_[1];
        exch(1, n_--);
        sink(1);
        qp_[min] = -1;
        keys_[min] = T();
        pq_[n_+1] = -1;
        return min;
    }
    void decrease_key(int i, T key)
    {
        keys_[i] = key;
        swim(qp_[i]);
    }
};
// Midterm
// Name : LinZhu
// Question 1.
template <class T>
class Queue
{
    bool empty();
    int size();
};

template <class T>
void queue_push(Queue<T> q, T item);

template <class T>
T queue_pop(Queue<T> q);

template <class T>
void stack_push(Queue<T> q, T item)
{
    queue_push(q, item);
}

template <class T>
T stack_pop(Queue<T>& q)
{
    Queue<T> tmp;
    T ret;
    while (!q.empty()) {
        ret = queue_pop(q);
        if (q.size() > 1) {
            queue_push(tmp, ret);
        }
    }
    q = tmp;
    return ret;
}

template <class T>
T stack_top(Queue<T>& q)
{
    Queue<T> tmp;
    T ret;
    while (!q.empty()) {
        ret = queue_pop(q);
        queue_push(tmp, ret);
    }
    q = tmp;
    return ret;
}
// Question 2.
template <class T>
struct ListNode
{
    ListNode<T>* next;
    T val;
};

template <class T>
class LinkedList {
private:
    ListNode<T>* head_;
    ListNode<T>* tail_;
public:
    ListNode<T>* head() { return head_; }
    virtual void append(ListNode<T>*) = 0;
    virtual void prepend(ListNode<T>*) = 0;
    virtual void remove(ListNode<T>*) = 0;
};


template <class T>
LinkedList<T> convert_2d_to_1d(LinkedList<LinkedList<T>> list)
{
    LinkedList<T> ret;
    ListNode<LinkedList<T>>* p = list.head();
    while (p) {
        ListNode<T>* q = p->val.head();
        while (q) {
            ret.append(q);
            q = q->next;
        }
        p = p->next;
    }
    return ret;
}


// Question 3.
/*QSort and Merge Sort are divide and conquer algorithms and 
  both use recursion while the other sorting algorithms
  such as bubble sort, insert sort, etc. uses iteration. */


// Question 4.

template <class T>
class HashTable
{
public:
    LinkedList<T>& operator[](uint32_t);
    uint32_t size();
};

template <class T>
int collision_detect(HashTable<T> hashTable)
{
    int ret = 0;
    for (auto i = 0; i < hashTable.size(); i++) {
        ListNode<T>* p = hashTable[i].head();
        int collision = 0;
        while (p) {
            collision++;
            p = p->next;
        }
        ret += collision > 0 ? collision - 1 : collision;
    }
    return ret;
}

// Question 5.
/*
Algorithm 1:
Determins how many digits does a number have and return the result. 
O(n): n is the number of digits in the number.

Algorithm 2:
Find the longest number in array A and return the number of digits.
 O(n): n is the number of nums in the array.

Algorithm 3:
 O(m*n*k)
 */
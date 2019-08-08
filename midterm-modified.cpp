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


// Question  1  
// Correction:
// I didn't see the requirements clearly, and missed the top function
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
// Correction:
// I didn't see the requirements clearly, missed the BigO notation.
// The BigO notation should be O(m*n), m is the length of longest linked list
// before merging and n is the number of linked list getting merged.
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
// Correction:
/* 

QSort and Merge sort are dive and conquer algorithms which divide the 
array into two parts, and sort the two parts recursively with the same
algorithm. Parent arrays are getting sorted after all the subarrays are
sorted. Bubble sort, insertion sort, selection sort and shell sort algorithms
are sorting algorithms treating the array as a while. They all iterate the 
whole array, and make swaps based on the comparison of two elements.

*/



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
        // Explanation:
        // I don't think it's off by one for each row.
        // Suppose three rows in the hash table is like the follows:
        // [1] 1, 21, 31
        // [2] 2
        // [3]
        // The first column means the bucket index.
        // after the while loop, bucket 1 gives collision == 3,
        // bucket 2 gives collision == 1
        // and bucket 3 gives collision == 0
        // After the following expression, we got collision for bucket 1 == 2,
        // collision for bucket 2 == 0, and collision for bucket 3 == 0
        ret += collision > 0 ? collision - 1 : collision;
    }
    return ret;
}

// Question 5.
/*
Algorithm 1:
Determins how many digits does a number have and return the result. 
O(n): n is the number of digits in the number.
correction: O(n): log(n) where n is the value of integer n

Algorithm 2:
Find the longest number in array A and return the number of digits.
 O(n): n is the number of nums in the array.

// Correction:
Algorithm 3:
 radix sort:
 O(d*n) d is the longest number's digit count, and n is the number 
 of value in the array
 */
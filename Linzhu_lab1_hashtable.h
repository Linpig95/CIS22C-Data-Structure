#include "Linzhu_lab_util.h"
#include <vector>
#include <utility>
#include <iomanip>
#include <algorithm>
using std::vector;
using std::pair;

struct Customer
{
    string firstName;
    string lastName;
    string id;
    bool operator==(const Customer& other) {
        return (firstName == other.firstName) &&
        (lastName == other.lastName) && (id == other.id);
    }
    Customer(string f, string l, string id)
        : firstName(f),
          lastName(l),
          id(id)
    {
    }
};

bool is_prime(int n)
{
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    int div = 6;
    while (div * div - 2 * div + 1 <= n)
    {
        if (n % (div - 1) == 0)
            return false;
        if (n % (div + 1) == 0)
            return false;
        div += 6;
    }
    return true;
}

long long next_prime(int n) 
{
    while (!is_prime(++n));
    return n;
}

using HashV = DList<Customer>;

class HashTable
{
public:
    HashTable() : 
    n_inserted_(0), 
    n_collision_(0)
    { resize(10); }
    virtual void insert(Customer) = 0;
    virtual void remove(Customer) = 0;
    virtual Customer* search(string) = 0;
    // virtual Customer* remove(string) = 0;
    void resize(int n = 0);
    uint32_t hash(string key);
    uint32_t n_collision() { return n_collision_; }
    uint32_t n_inserted() { return n_inserted_; }
protected:
    vector<HashV> arr_;
    uint32_t n_collision_;
    uint32_t n_inserted_;
};


void HashTable::resize(int n)
{
    int new_size = (n == 0 ? next_prime(arr_.size() * 2) : n);
    cout << "resizing to " << setw(8) << new_size << right << endl << endl;
    vector<HashV> cp_arr(arr_);
    arr_ = vector<HashV>(new_size, HashV());
    n_inserted_ = 0;
    n_collision_ = 0;
    for (auto i = 0; i < cp_arr.size(); i++) {
        while (!cp_arr[i].is_empty()) {
            auto customer = cp_arr[i].head()->value;
            cp_arr[i].remove(nullptr);
            insert(customer);
        }
    }
}

uint32_t HashTable::hash(string key)
{
    const int p = 31;
    const int m = arr_.size();
    uint32_t hash = 0;
    for (auto c : key) {
        hash = (hash * p) + c;
    }
    return hash % m;
}


class ChainingHashTable : public HashTable
{
public:
    virtual void insert(Customer) override;
    virtual void remove(Customer) override;
    virtual Customer* search(string) override;
};

void ChainingHashTable::insert(Customer c)
{
    if (all_of(arr_.begin(), arr_.end(), [](HashV v) { return !v.is_empty(); }))
    {
        resize();
    }
    cout << "chain insert " << setw(2) <<  c.firstName << " " << c.lastName << " " << c.id << right << endl;
    if (!search(c.id)) {
        DList<Customer>& list = arr_[hash(c.id)];
        if (!list.is_empty()) n_collision_++;
        list.append(make_shared<ListNode<Customer>>(c));
        n_inserted_++;
    }
}

void ChainingHashTable::remove(Customer c)
{
    DList<Customer>& list = arr_[hash(c.id)];
    auto p = list.search(c);
    if (p) {
        list.remove(p);
        n_inserted_--;
    }
}

Customer* ChainingHashTable::search(string key)
{
    DList<Customer>& list = arr_[hash(key)];
    auto p = list.head();
    while (p) {
        if (key == p->value.id) {
            return &(p->value);
        }
        p = p->next;
    }
    return nullptr;
}

class LinearProbingHashTable : public HashTable
{
public:
    virtual void insert(Customer) override;
    virtual void remove(Customer) override;
    virtual Customer* search(string) override;
};


void LinearProbingHashTable::insert(Customer c)
{
    if (n_inserted_ == arr_.size()) {
        resize();
    }
    cout << "lp insert " << setw(2) << c.firstName << " " << c.lastName << " " << c.id << right << endl;
    auto bucket = hash(c.id);
    bool collision_added{false};
    while (true) {
        if (arr_[bucket].is_empty()) {
            arr_[bucket].append(make_shared<ListNode<Customer>>(c));
            n_inserted_++;
            break;
        }
        if (!collision_added) {
            n_collision_++;
            collision_added = true;
        }
        bucket = (bucket + 1) % arr_.size();
    }
}
void LinearProbingHashTable::remove(Customer c)
{
    auto bucket = hash(c.id);
    int probeCount = 0;
    auto start_bucket = bucket;
    while ((arr_[bucket].empty_state() != EmptyState::EMPTY_SINCE_START) &&
           probeCount < arr_.size())
    {
        if(!arr_[bucket].is_empty() && arr_[bucket].head()->value.id == c.id) {
            arr_[bucket].remove(nullptr);
            n_inserted_--;
            return;
        }
        bucket = (bucket + 1) % arr_.size();
        ++ probeCount;
    }
}

Customer* LinearProbingHashTable::search(string key)
{
    auto bucket = hash(key);
    if (arr_[bucket].is_empty()) {
        return nullptr;
    }
    auto bucket_probed = 0;
    while (bucket_probed < arr_.size()) {
        if (!arr_[bucket].is_empty() && arr_[bucket].head()->value.id == key) {
            return &(arr_[bucket].head()->value);
        }
        bucket = (bucket + 1) % arr_.size();
    }
    return nullptr;
}

class DoubleHashingHashTable : public HashTable
{
public:
    virtual void insert(Customer) override;
    virtual void remove(Customer) override {}
    virtual Customer* search(string) override;
    uint32_t hash2(string key);
};

void DoubleHashingHashTable::insert(Customer c)
{
    if (arr_.size() == n_inserted_) {
        resize();
    }
    cout << "Double hashing insert " << setw(2) << c.firstName << " " << c.lastName << " " << c.id << right << endl;
    int tried = 1;
    bool retry = true;
    do {
        if (tried > 1) cout << "trying " << tried << " time." << endl;
        auto key = c.id;
        int index = hash(key);
        if (arr_[index].is_empty()) {
            arr_[index].append(make_shared<ListNode<Customer>>(c));
            n_inserted_++;
            return;
        }
        auto start_index = index;
        auto step_size = hash2(key) + 1;
        n_collision_++;
        do {
            retry = false;
            index = (index + step_size) % arr_.size();
            if (index == start_index) {
                cout << "Failed to insert " << c.id << endl;
                resize();
                tried++;
                retry = true;
                break;
            }
        } while (!arr_[index].is_empty());
        if (!retry) {
            arr_[index].append(make_shared<ListNode<Customer>>(c));
            n_inserted_++;
            return;
        }
    } while (true);
}

Customer* DoubleHashingHashTable::search(string key)
{
    int index = hash(key);
    if (!arr_[index].is_empty()) {
        return nullptr;
    }
    auto start_index = index;
    auto step_size = hash2(key) + 1;
    for (;;) {
        index = (index + step_size) % arr_.size();
        if (index == start_index) return nullptr;
        if (arr_[index].is_empty()) return nullptr;
        if (key.compare(arr_[index].head()->value.id) == 0) {
            return &(arr_[index].head()->value);
        }
    }
    return nullptr;

}

uint32_t DoubleHashingHashTable::hash2(string key)
{
    uint32_t hash = 0;
    for (auto c : key) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

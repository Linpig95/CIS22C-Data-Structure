#include <iostream>
#include <ctime>
#include <memory>
#include <queue>
#include <fstream>
#include <utility>
#include "Linzhu_lab_util.h"
#include <tuple>
#include <sstream>
#include <cmath>
using namespace std;

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);

template <class T>
class TreeNode 
{
public:
    TreeNode(T a) : data(a) {}
    T data;          // The data in this node.
    shared_ptr<struct TreeNode<T>> left = nullptr;  // Pointer to the left subtree.
    shared_ptr<struct TreeNode<T>> right = nullptr; // Pointer to the right subtree.
    bool operator < (const TreeNode<T>& other) {
        return data < other->data;
    }
    bool operator > (const TreeNode<T>& other) {
        return data > other->data;
    }
};

template<class T>
class BinarySearchTree
{
private:
    shared_ptr<TreeNode<T>> root_;
    int height_{0};
    int size_{0};
public:
    BinarySearchTree()
        : root_(nullptr)
    {
    }
    bool isEmpty() const { return !root_; }
    void insert(T val);
    void parent(T x);
    void inorder();
    void inorder_recursion(shared_ptr<TreeNode<T>>);
    shared_ptr<TreeNode<T>> search(T);
    virtual void printlevel();
    void rebalance();
    void vine_to_tree(shared_ptr<TreeNode<T>>, uint32_t);
    void tree_to_vine(shared_ptr<TreeNode<T>>);
    void compress(shared_ptr<TreeNode<T>>, uint32_t);
    int height(shared_ptr<TreeNode<T>>);
    void update_height();
};


template <class T>
void BinarySearchTree<T>::update_height()
{
    height_ = height(root_);
}


template <class T>
int BinarySearchTree<T>::height(shared_ptr<TreeNode<T>> root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

template <class T>
void BinarySearchTree<T>::rebalance()
{
    shared_ptr<TreeNode<T>> pseudo_root = make_shared<TreeNode<T>>(-1);
    pseudo_root->right = root_;
    tree_to_vine(pseudo_root);
    vine_to_tree(pseudo_root, size_);
    root_ = pseudo_root->right;
    update_height();
}

template <class T>
void BinarySearchTree<T>::tree_to_vine(shared_ptr<TreeNode<T>> root)
{
    shared_ptr<TreeNode<T>> tail = root;
    shared_ptr<TreeNode<T>> rest = tail->right;
    while (rest)
    {
        if (!rest->left) {
            tail = rest;
            rest = rest->right;
        } else {
            auto temp = rest->left;
            rest->left = temp->right;
            temp->right = rest;
            rest = temp;
            tail->right = temp;
        }
    }
}

template <class T>
void BinarySearchTree<T>::vine_to_tree(shared_ptr<TreeNode<T>> root, uint32_t size)
{
    auto leaves = size + 1 - pow(2, floor(log2((size+1))));
    compress(root, leaves);
    size = size - leaves;
    while (size > 1)
    {
        compress(root, floor(size / 2));
        size = floor(size / 2);
    }
}


template <class T>
void BinarySearchTree<T>::compress(shared_ptr<TreeNode<T>> root, uint32_t count)
{
    shared_ptr<TreeNode<T>> scanner = root;
    for (auto i = 0; i < count; i++)
    {
        shared_ptr<TreeNode<T>> child = scanner->right;
        scanner->right = child->right;
        scanner = scanner->right;
        child->right = scanner->left;
        scanner->left = child;
    }
}

template <class T>
void BinarySearchTree<T>::printlevel()
{
    if (!this->root_)
        return;
    queue<tuple<shared_ptr<TreeNode<T>>, int, Color::Modifier, string>> q;
    {
        stringstream sst;
        sst << root_->data;
        q.push({root_, 1, def, sst.str()});
    }
    tuple<shared_ptr<TreeNode<T>>, int, Color::Modifier, string> p;
    int cur_level = 1;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (cur_level < get<1>(p)) {
            cout << endl;
            cur_level++;
        }
        if (cur_level > height_) {
            break;
        }
        cout << get<2>(p) << get<3>(p) << " ";
        if (!get<0>(p)) {
            q.push({nullptr, get<1>(p) + 1, def, string("-")});
            q.push({nullptr, get<1>(p) + 1, def, string("-")});
            continue;
        }

        if (get<0>(p)->left) {
            stringstream sst;
            sst << get<0>(p)->left->data;
            q.push({get<0>(p)->left, get<1>(p) + 1, red, sst.str()});
        }
        else
            q.push({nullptr, get<1>(p) + 1, def, string("-")});
        if (get<0>(p)->right) {
            stringstream sst;
            sst << get<0>(p)->right->data;
            q.push({get<0>(p)->right, get<1>(p) + 1, green, sst.str()});
        }
        else
            q.push({nullptr, get<1>(p) + 1, def, string("-")});
    }
    cout << def << endl;
}

template <class T>
void BinarySearchTree<T>::inorder()
{
    inorder_recursion(root_);
}

template <class T>
void BinarySearchTree<T>::inorder_recursion(shared_ptr<TreeNode<T>> cur)
{
    if (!cur) {
        return;
    }
    inorder_recursion(cur->left);
    cout << cur->data << " ";
    inorder_recursion(cur->right);
}

template<class T>
void BinarySearchTree<T>::insert(T val)
{
    if (!root_)
    {
        root_ = make_shared<TreeNode<T>>(val);
        height_ = 1;
        return;
    }
    shared_ptr<TreeNode<T>> cur = root_;
    shared_ptr<TreeNode<T>> parent{nullptr};
    int cur_height = 1;
    while (cur)
    {
        parent = cur;
        if (val > cur->data)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
        cur_height += 1;
    }
    if (val > parent->data) {
        parent->right = make_shared<TreeNode<T>>(val);
    } else {
        parent->left = make_shared<TreeNode<T>>(val);
    }
    height_ = cur_height > height_ ? cur_height : height_;
    size_ += 1;
}

template<class T>
shared_ptr<TreeNode<T>> BinarySearchTree<T>::search(T a)
{
  shared_ptr<TreeNode<T>> cur = root_;
  while (cur)
  {
      if (a == cur->data)
      {
          return cur;
      }
      else if (a < cur->data)
      {
          cur = cur->left;
      }
      else
      {
          cur = cur->right;
      }
  }
  return cur;
}
#include "tree_util.h"

template <class T>
class AvlNode
{
public:
    AvlNode(T a)
        : data(a),
          height(1) {}
    shared_ptr<AvlNode<T>> left = nullptr;  // Pointer to the left subtree.
    shared_ptr<AvlNode<T>> right = nullptr; // Pointer to the right subtree.
    bool operator < (const AvlNode<T>& other) {
        return data < other->data;
    }
    bool operator > (const AvlNode<T>& other) {
        return data > other->data;
    }
    T data;
    int height;
};

template <class T>
int height(shared_ptr<AvlNode<T>> N)
{
    if(!N)
        return 0;
    return N->height;
}

template <class T>
class AvlTree : public BinarySearchTree<T>
{
public:
    shared_ptr<AvlNode<T>> r_rotation(shared_ptr<AvlNode<T>>);
    shared_ptr<AvlNode<T>> l_rotation(shared_ptr<AvlNode<T>>);
    shared_ptr<AvlNode<T>> minValueNode(shared_ptr<AvlNode<T>>);
    shared_ptr<AvlNode<T>> insert_recursion(shared_ptr<AvlNode<T>>, int);
    void insert(int);

    int getBalance(shared_ptr<AvlNode<T>> N);

    void preorder_recursion(shared_ptr<AvlNode<T>>);
    void postorder_recursion(shared_ptr<AvlNode<T>>);
    void display_recursion(shared_ptr<AvlNode<T>>, int);
    void preorder();
    void postorder();
    void display();
    virtual void printlevel();
private:
    shared_ptr<AvlNode<T>> root_;
};

template <class T>
void AvlTree<T>::printlevel()
{
    if (!this->root_)
        return;
    queue<tuple<shared_ptr<AvlNode<T>>, int, Color::Modifier, string>> q;
    {
        stringstream sst;
        sst << root_->data;
        q.push({root_, 1, def, sst.str()});
    }
    tuple<shared_ptr<AvlNode<T>>, int, Color::Modifier, string> p;
    int cur_level = 1;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (cur_level < get<1>(p)) {
            cout << endl;
            cur_level++;
        }
        if (cur_level > root_->height) {
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
shared_ptr<AvlNode<T>> AvlTree<T>::r_rotation(shared_ptr<AvlNode<T>> y)
{
    shared_ptr<AvlNode<T>> x = y->left;
    shared_ptr<AvlNode<T>> T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
    return x;  
}

template <class T>
shared_ptr<AvlNode<T>> AvlTree<T>::l_rotation(shared_ptr<AvlNode<T>> x)
{
    shared_ptr<AvlNode<T>> y = x->right;
    shared_ptr<AvlNode<T>> T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
    return y;  
}
template <class T>
int AvlTree<T>::getBalance(shared_ptr<AvlNode<T>> N)
{
    if (!N)
        return 0;
    return height(N->left) - height(N->right);
}

template <class T>
void AvlTree<T>::insert(int value)
{
    root_ = insert_recursion(root_, value);
}

template <typename T>
shared_ptr<AvlNode<T>> AvlTree<T>::insert_recursion(shared_ptr<AvlNode<T>> root, int value)
{
    if (!root)
    {
        return make_shared<AvlNode<T>>(value);
    }
    if (value < root->data)
    {
        root->left = this->insert_recursion(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = this->insert_recursion(root->right, value);
    }
    else
    {
        return root;
    }
    root->height = 1 + max(height(root->left),  
                           height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && value < root->left->data)  
        return r_rotation(root);  

    if (balance < -1 && value > root->right->data)  
        return l_rotation(root);  

    if (balance > 1 && value > root->left->data)  
    {  
        root->left = l_rotation(root->left);  
        return r_rotation(root);  
    }  

    if (balance < -1 && value < root->right->data)  
    {  
        root->right = r_rotation(root->right);  
        return l_rotation(root);  
    }  

    return root; 
}

template <typename T>
shared_ptr<AvlNode<T>> AvlTree<T>::minValueNode(shared_ptr<AvlNode<T>> root)
{
    shared_ptr<AvlNode<T>> current = root;
    while(current->left){
        current = current->left;
    }
    return current;
}

template <class T>
void AvlTree<T>::display()
{
    if (!root_) {
        return;
    }
    display_recursion(root_, 0);
}

template <class T>
void AvlTree<T>::display_recursion(shared_ptr<AvlNode<T>> ptr, int level)
{
    int i;
    if (ptr)
    {
        display_recursion(ptr->right, level + 1);
        cout << endl;
        if (ptr == root_)
            cout << "Root -> ";
        for (auto i = 0; i < level && ptr != root_; i++)
            cout << "\t";
        cout << ptr->data;
        display_recursion(ptr->left, level + 1);
    }
}


template <class T>
void AvlTree<T>::preorder()
{
    preorder_recursion(root_);
}

template <class T>
void AvlTree<T>::preorder_recursion(shared_ptr<AvlNode<T>> tree)
{
    if (!tree)
        return;
    cout << tree->data << "  ";
    preorder_recursion(tree->left);
    preorder_recursion(tree->right);
}

template <class T>
void AvlTree<T>::postorder()
{
    postorder_recursion(root_);
}

template <class T>
void AvlTree<T>::postorder_recursion(shared_ptr<AvlNode<T>> tree)
{
    if (!tree)
        return;
    postorder_recursion(tree->left);
    postorder_recursion(tree->right);
    cout << tree->data << "  ";
}

int main()
{
    AvlTree<int> avl;
    ifstream file1("Numbers_test.txt");
    if (!file1.is_open()) {
        cout << "Failed to open file " << endl;
        return 1;
    }

    int num;
    while (file1.good())
    {
        file1 >> num;
        avl.insert(num);
    }
    file1.close();
    // avl.display();
    cout << endl;
    avl.printlevel();
    // avl.preorder();
    // avl.postorder();
    cout << endl;
    return 0;
}



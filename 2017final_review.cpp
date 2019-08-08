#include <stdlib.h>
#include <limits>
#include <cmath>
#include <iostream>
using namespace std;
class BST
{
public:
    int data;
    BST *parent;
    BST *left;
    BST *right;
};

BST *createBSTNode(int data)
{
    BST *newNode = new BST();
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

void bst_insert(BST *&tree, BST *node)
{
    BST *prev = NULL;
    BST *iter = tree;
    while (iter != NULL)
    {
        prev = iter;
        if (node->data < iter->data)
            iter = iter->left;
        else
            iter = iter->right;
    }
    node->parent = prev;
    if (prev == NULL)
        tree = node;
    else
    {
        if (node->data < prev->data)
            prev->left = node;
        else
            prev->right = node;
    }
}

BST *convert_arr_bst(int *arr, int size)
{
    BST *tree = NULL;
    for (int i = 0; i < size; i++)
    {
        bst_insert(tree, createBSTNode(arr[i]));
    }
    return tree;
}

void ascending(BST *root)
{
    if (root == NULL)
        return;
    ascending(root->left);
    std::cout << static_cast<char>(root->data) << " ";
    ascending(root->right);
}

void descending(BST *root)
{
    if (root == NULL)
        return;
    descending(root->right);
    std::cout << static_cast<char>(root->data) << " ";
    descending(root->left);
}

int main()
{
    int Alph[] = {'A', 'B', 'C'};
    BST *root = convert_arr_bst(Alph, sizeof(Alph) / sizeof(int));
    ascending(root);
    std::cout << std::endl;
    descending(root);
    std::cout << std::endl;
}
2. //////////////////////////////////////////////////////////////
class Solution
{
public:
    bool isBalanced(TreeNode *root)
    {
        if (checkDepth(root) == -1)
            return false;
        else
            return true;
    }
    int checkDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        int left = checkDepth(root->left);
        if (left == -1)
            return -1;
        int right = checkDepth(root->right);
        if (right == -1)
            return -1;
        int diff = abs(left - right);
        if (diff > 1)
            return -1;
        else
            return 1 + max(left, right);
    }
};
3.//////////////////////////////////////////////////////////////////
void seach(string text, string pattern)
{
    while (!iFile.eof())
    {
        if (text.length() == pattern.length())
        {
            if (text[0] == pattern[0])
            {
                for (int i = 0; i < pattern.length(); i++)
                {
                    int cur_count = 0;
                    for (int j = 0; j < text.length(); j++)
                    {
                        if (text[i] == pattern[j])
                        {
                            cout << text[i] << "\t" << pattern[j] << endl;
                        }
                        else
                        {
                            break;
                            cur_count++;
                        }
                    }
                }
            }
        }
    }
}
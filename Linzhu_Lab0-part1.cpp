#include "Linzhu_lab_util.h"

int main(){
    DList<int>* ages = new DList<int>();
    ListNode<int>* node1 = new ListNode<int>(55);
    ages->append(node1);
    ListNode<int>* node2 = new ListNode<int>(88);
    ages->append(node2);
    ListNode<int>* node3 = new ListNode<int>(66);
    ages->append(node3);
    
    cout << "print Result: ";
    ages->print();
    cout << endl;
    ages->remove(node2);
    cout << "print Result: ";
    ages->print();
    cout << endl;
    return 0;
}

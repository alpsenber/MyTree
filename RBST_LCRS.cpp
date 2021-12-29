
#include <iostream>
#include "RBST_helper.h"

using namespace RBST_helper;
int main()
{
    srand(time(0));
    LCRS_node* TreeA = 0;
    LCRS_node* TreeB = 0;
    for (int i = 0; i < 20; i++) //заполнение дерева А
    {
        TreeA = randinsert(TreeA, i);
        setsize(TreeA);
        cout << TreeA->size << "  ";
    }
    cout << "\n\n";
    for (int i = 20; i < 30; i++) // Заполнение дерева B
    {
        TreeB = randinsert(TreeB, i);
        setsize(TreeB);
        cout << TreeB->size << "  ";
    }
    cout << "\n\n\n";
    printtree(TreeA, 0);
    cout << "\n\n\n";
    printtree(TreeB, 0);
    cout << "\n\n\n";
    inorder_merge(TreeA, TreeB);
    cout << "\n\n\n";
    printtree(TreeA, 0);



    delete TreeB;
    delete TreeA;
}


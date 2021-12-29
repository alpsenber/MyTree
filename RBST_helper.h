#pragma once
#include <cstdlib>
#include "LCRS_node.h"  
using namespace std;

namespace RBST_helper
{
    unsigned long  N_op;
    LCRS_node* find(LCRS_node* p, int k) // поиск значение k в дереве p
    {
        if (!p) return 0; // в пустом дереве можно не искать
        if (k == p->value)
            return p;
        if (k < p->value)
            return find(p->L_child, k);
        else if (p->L_child != 0);
            return find(p->R_sibling, k);
    }

    int getsize(LCRS_node* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
    {
        N_op++;
        if (!p) return 0;
        return p->size;
    }

    void setsize(LCRS_node* p) // установление корректного размера дерева
    {                           //  (logN/2)*12
        if (!p) return;   
        setsize(p->L_child);  
        p->size = getsize(p->L_child); //3
        p->size++;                          //1
        if (p->L_child != 0)            //2   
        {
            setsize(p->L_child->R_sibling); //2
            p->size += getsize(p->L_child->R_sibling); //4
        }
        N_op += 12;
    }

    LCRS_node* rotateright(LCRS_node* p) // правый поворот вокруг узла p
    {                                    // 11
        LCRS_node* q = p->L_child;      // 2
        if (!q) return p;
        if (!q->L_child) return p;
        p->L_child = q->L_child->R_sibling; //4
        if (q->L_child != 0) q->L_child->R_sibling = p;    //5
        return q;
        N_op += 11;
    }

    LCRS_node* rotateleft(LCRS_node* q) // правый поворот вокруг узла p
    {
        LCRS_node* p = q->L_child->R_sibling; //4
        if (!p) return q;
        q->L_child->R_sibling = p->L_child; //4
        p->L_child = q;                     //2
        N_op += 10;
        return p;
    }
    
    LCRS_node* baseinsert(LCRS_node* p, int k) // классическая вставка нового узла с ключом k в дерево p
    {
        if (!p) return new LCRS_node(k);    //5
        if (p->value > k)                   //2
            p->L_child = baseinsert(p->L_child, k); //3
        else if (p->L_child != 0)           //2
            p->L_child->R_sibling = baseinsert(p->L_child->R_sibling, k); //5
        else
        {    
            int tmp = p->value;     //
            p->value = k;
            p->L_child = baseinsert(p->L_child, tmp);
        }
        return p;
    }

    LCRS_node* rootinsert(LCRS_node* p, int k) // вставка нового узла с ключом k в корень дерева p 
    {
        if (!p) return new LCRS_node(k);
        if (k < p->value)
        {
            p->L_child = rootinsert(p->L_child, k);
            return rotateright(p);
        }
        else if (p->L_child != 0)
        {
            p->L_child->R_sibling = rootinsert(p->L_child->R_sibling, k);
            return rotateleft(p);
        }
        else
        {
            int tmp = p->value;
            p->value = k;
            p->L_child = rootinsert(p->L_child, tmp);
            return p;
        }
    }




    LCRS_node* randinsert(LCRS_node* p, int k) // рандомизированная вставка нового узла с ключом k в дерево p
    {
        if (!p) return new LCRS_node(k);
        int r = rand();
        r = r % (p->size + 1);
        if ( r == 0)
            return rootinsert(p, k);
        else
            if (p->value > k)
                p->L_child = baseinsert(p->L_child, k);
            else if (p->L_child != 0)
                p->L_child->R_sibling = baseinsert(p->L_child->R_sibling, k);
            else
            {
                int tmp = p->value;
                p->value = k;
                p->L_child = baseinsert(p->L_child, tmp);
            }
        return p;
    }

    void printtree(LCRS_node* p, int level)
    {
        if (!p) return;
        if (p->L_child != 0 && p->L_child->R_sibling != 0)    
            printtree(p->L_child->R_sibling, level + 1);
        for (int i = 0; i < level; ++i)
            cout << "    ";
        cout << p->value << endl;
        if (p->L_child != 0) printtree(p->L_child, level + 1);
    }


    void inorder_merge(LCRS_node* T, LCRS_node* p)
    {
        if (!p) return;
        inorder_merge(T, p->L_child);
        randinsert(T, p->value);
        if (p->L_child != 0) inorder_merge(T, p->L_child->R_sibling);
    }

}
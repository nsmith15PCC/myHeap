#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

enum HEAP_ERRORS {HEAP_EMPTY};

template<typename T>
struct node
{
    T data;
    node<T>* child[2];

    node(T d = T())
    {
        data = d;
        child[0] = child[1] = NULL;
    }


    ~node()
    {
        data = T();
        child[0] = child[1] = NULL;
    }
};

template<typename T>
class heap
{
public:
    heap();
    heap(const T &data);
    ~heap();
    heap(const heap<T> &other);
    heap<T>& operator=(const heap<T> &other);

    bool empty();
    size_t size();
    void clear();

    heap<T>& operator<<(const T & data);
    heap<T>& operator>>(T & data);

    template<typename U>
    friend
    ostream& operator<<(ostream& out, const heap<U> &h);

    template<typename U>
    friend
    istream& operator>>(istream& in, heap<U> &h);

private:
    node<T> *root;
    size_t lastEntered;

    void copy(heap<T> *r, heap<T> *&myR);

    node<T>* findParent(size_t n);
    void reheapifyUp(size_t last);
    void reheapifyDown(node<T> *parent);
};

template<typename T>
heap<T>::heap()
{
    root = NULL;
    lastEntered = 0;
}

template<typename T>
heap<T>::heap(const T &data)
{
    root = new node<T>(data);
    lastEntered = 1;
}

template<typename T>
heap<T>::~heap()
{
    clear();
}

template<typename T>
heap<T>::heap(const heap<T> &other)
{
    copy(other.root, root);
}

template<typename T>
heap<T>& heap<T>::operator=(const heap<T> &other)
{
    if(this != &other)
    {
        clear();
        copy(other.root,root);
    }
    return *this;
}

template<typename T>
bool heap<T>::empty()
{
    return !lastEntered;
}

template<typename T>
size_t heap<T>::size()
{
    return lastEntered;
}

template<typename T>
void heap<T>::clear()
{
    T data;
    while(!empty())
        *this>>data;
    root = NULL;
    lastEntered = 0;
}

template<typename T>
heap<T>& heap<T>::operator<<(const T & data)
{
    node<T> *newNode = new node<T>(data);
    ++lastEntered;
    if(!root)
        root = newNode;
    else
    {
        node<T> *parent = findParent(lastEntered);
        parent->child[lastEntered & 1] = newNode;
        reheapifyUp(lastEntered);
    }
    return *this;
}

template<typename T>
heap<T>& heap<T>::operator>>(T &data)
{
    if(empty())
        throw HEAP_EMPTY;
    //    cout<<"Starting >>\n";
    data = root->data;
    if(!root->child[0])
    {
        delete root;
        root = NULL;
        lastEntered--;
        return *this;
    }
    //    cout<<"Finding parent\n";
    node<T>* parent = findParent(lastEntered);
    //    cout<<"Swapping with root\n";
    swap(root->data, parent->child[lastEntered & 1]->data);
    //    cout<<"Delete lastEntered\n";
    delete parent->child[lastEntered & 1];
    parent->child[lastEntered & 1] = NULL;
    lastEntered--;
    //    cout<<"reHeapify down\n";
    reheapifyDown(root);
    return *this;
    //    cout<<"Ending >>\n";
}

template<typename T>
void heap<T>::copy(heap<T> *r, heap<T> *&myR)
{
    if(!r)
        return;
    myR = new node<T>*(r->data);\
    for(size_t i = 0; i < 2; ++i)
        if(r->child[i])
            copy(r->child[i], myR->child[i]);
}

template<typename T>
node<T>* heap<T>::findParent(size_t n)
{
    size_t mask = 1 << (int)(log2((double)n)-1);
    node<T>* parent = root;
//    cout<<endl<<"mask = "<<mask<<endl;
    if(n == 1)
        return NULL;
    while(mask > 1)
    {
        parent = parent->child[(mask & n) > 0];
        mask /= 2;
    }
    return parent;
}

template<typename T>
void heap<T>::reheapifyUp(size_t last)
{
    if (last > 1)
    {
        node<T> *parent = findParent(last),
                *child = parent->child[last & 1];
        if (parent->data < child->data)
            swap (parent->data, child->data);
        reheapifyUp(last/2);
    }
    else
        return;

    //    bool notDone = true;
    //    size_t last = lastEntered;

    //    node<T> *parent = findParent(lastEntered),
    //            *child;
    //    while(notDone && parent)
    //    {
    //        child = parent->child[last & 1];
    //        if(child->data > parent->data)
    //        {
    //            swap(child->data,parent->data);
    //            child = parent;
    //            last/=2;
    //            parent = findParent(last);
    //        }
    //        else
    //          notDone = false;
    //    }
}

template<typename T>
void heap<T>::reheapifyDown(node<T> *parent)
{
    if (parent->child[0])
    {
        node<T> *toSwap = parent->child[0];
        if (parent->child[1])
            toSwap = parent->child[parent->child[0]->data <= parent->child[0]->data];
        if (parent->data < toSwap->data)
        {
            swap(parent->data, toSwap->data);
            reheapifyDown(toSwap);
        }
    }
    else
        return;


    //    bool notDone = true;
    //    node<T>* parent = root;
    //    while(parent->child[0] && notDone )
    //        if(!parent->child[1])
    //        {
    //           //cout<<"Has only 1 child\n";
    //           if(parent->child[0]->data > parent->data)
    //              swap(parent->child[0]->data, parent->data);
    //           notDone = false;
    //        }
    //        else
    //        {
    //           // cout<<"Has two children\n";
    //            size_t toSwap = parent->child[1]->data > parent->child[0]->data;
    //            if(parent->data < parent->child[toSwap]->data)
    //            {
    //                swap(parent->data, parent->child[toSwap]->data);
    //                parent = parent->child[toSwap];
    //            }
    //            else
    //                notDone = false;
    //        }
}

template<typename U>
ostream& operator<<(ostream& out, const heap<U> &h)
{
    heap<U> theCopy(h);
    U data;
    while(!theCopy.empty())
    {
        theCopy>>data;
        out<<data;
    }
    return out;
}

template<typename U>
istream& operator>>(istream& in, heap<U> &h)
{
    U data;
    while(in>>data)
        h << data;
    return in;
}


#endif // HEAP_H

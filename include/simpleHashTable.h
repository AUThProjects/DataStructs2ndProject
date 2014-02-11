#ifndef SIMPLEHASHTABLE_H
#define SIMPLEHASHTABLE_H

#include "treeNode.h"

class simpleHashTable
{
    public:
        simpleHashTable(int sizeToInitializeTo);
        virtual ~simpleHashTable();
        int getCapacity();
        int getCurrentSize();
        *treeNode getElement(int value);
        bool addElement(treeNode* value);
        bool exists(treeNode* toCompare);
    protected:
    private:
        int hashFunction(int value);
        treeNode** theArray; // T** for nullable
        int capacity;
        int currentSize;
};

#endif // SIMPLEHASHTABLE_H

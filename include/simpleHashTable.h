#ifndef SIMPLEHASHTABLE_H
#define SIMPLEHASHTABLE_H

#include "treeNode.h"

class simpleHashTable
{
    public:
        simpleHashTable(int sizeToInitializeTo);
        simpleHashTable(int sizeToInitializeTo, int defaultValue);
        virtual ~simpleHashTable();
        int getCapacity();
        int getCurrentSize();
        int getElement(int value);
        bool addElement(int value);
        bool exists(int toCompare);

    protected:
    private:
        int hashFunction(int value);
        int* theArray; // T** for nullable
        int capacity;
        int currentSize;
};

#endif // SIMPLEHASHTABLE_H

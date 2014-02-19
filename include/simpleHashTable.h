#ifndef SIMPLEHASHTABLE_H
#define SIMPLEHASHTABLE_H

#include "treeNode.h"

class SimpleHashTable
{
    public:
        SimpleHashTable(int sizeToInitializeTo); // ctor with size
        // ctor with size and initial value that fills the HashTable
        SimpleHashTable(int sizeToInitializeTo, int defaultValue);
        virtual ~SimpleHashTable(); // dtor
        int getCapacity();
        int getCurrentSize();
        int getElement(int value);
        bool addElement(int value);
        bool exists(int toCompare);
        void print();
    protected:
    private:
        int hashFunction(int value);
        int defaultFillValue; // the value to which empty fields in the HashTable correspond to
        int* theArray; // the actual HashTable
        int capacity; // max size of the HashTable
        int currentSize; // current size of the HashTable (number of Records)
};

#endif // SIMPLEHASHTABLE_H

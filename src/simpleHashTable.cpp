#include <climits>
#include "../include/SimpleHashTable.h"
#define A_BIG_PRIME_NUMBER 993319
#define A_SMALL_PRIME_NUMBER 13
#include <iostream>

using namespace std;

// /*
/* DEBUGGING */
void SimpleHashTable::print()
{
    for (int i=0;i<capacity;i++)
    {
        cout << i << "." <<theArray[i] << endl;
    }
}
// */


SimpleHashTable::SimpleHashTable(int sizeToInitializeTo, int defaultValue)
{
    //ctor
    this->theArray = new int[sizeToInitializeTo];
    this->capacity = sizeToInitializeTo;
    this->currentSize = 0;
    this->defaultFillValue = defaultValue;
    for (int i=0;i<capacity;++i)
    {
        this->theArray[i] = defaultFillValue;
    }

}

SimpleHashTable::SimpleHashTable(int sizeToInitializeTo) : SimpleHashTable(sizeToInitializeTo, -INT_MAX)
{
    /* does not need to run any commands */
}

SimpleHashTable::~SimpleHashTable()
{
    //dtor
    /*
     * Delete theArray only as the elements in the hashtable are allocated
     * on the stack, not on the heap.
     */
    delete this->theArray;
}

/*----------------------------Accessors ------------------------------*/
int SimpleHashTable::getCapacity()
{ return this->capacity; }

int SimpleHashTable::getCurrentSize()
{ return this->currentSize; }

int SimpleHashTable::hashFunction(int value)
{
    // The hashing function h(x) = (x%BigPrime)^SmallPrime%capacity
    return ((value%A_BIG_PRIME_NUMBER)^A_SMALL_PRIME_NUMBER)%capacity;
}


bool SimpleHashTable::addElement(int id)
{
    int hashingPosition = hashFunction(id);
    if (currentSize == capacity) // finiteness of the algorithm
    {
        throw -2; // the HashTable is full
        return false;
    }
    bool flag = false;
    while (!flag && hashingPosition < capacity)
    if (theArray[hashingPosition]==defaultFillValue)
    {
        theArray[hashingPosition] = id;
        ++currentSize;
        flag = true;
    }
    else if (theArray[hashingPosition] == id)
    {
        // the record already exists
        flag = false;
        return false;
    }
    else
    {
        hashingPosition = (hashingPosition+1)%capacity; // cyclical linear hashing
    }
    return flag; // not really used.
}

bool SimpleHashTable::exists(int id)
{
    int hashingPosition = hashFunction(id);
    bool result = false;
    int counter = 0;
    while (!result)
    {
        if (counter++ == capacity)
        {
            return false;
        }
        if (theArray[hashingPosition] == defaultFillValue)
            return false; // actually finds empty spot in the hashTable
        if (theArray[hashingPosition] == id)
        {
            result = true;
            return result;
        }
        else
        {
            hashingPosition = (1+hashingPosition)%capacity;
        }
    }
}

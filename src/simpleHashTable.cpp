#include "../include/simpleHashTable.h"
#define A_BIG_PRIME_NUMBER 993319


simpleHashTable::simpleHashTable(int sizeToInitializeTo)
{
    //ctor
    this->theArray = new T*[sizeToInitializeTo];
    this->capacity = sizeToInitializeTo;
    this->currentSize = 0;
    for (int i=0;i<capacity;++i)
    {
        this->theArray+i = nullptr;
    }

}

simpleHashTable::~simpleHashTable()
{
    //dtor
    delete this->theArray;
}

int simpleHashTable::getCapacity()
{ return this->capacity; }

int simpleHashTable::getCurrentSize()
{ return this->currentSize; }

int simpleHashTable::hashFunction(int value)
{
    return (value%A_BIG_PRIME_NUMBER)%capacity;
}

bool simpleHashTable::addElement(treeNode* toBeAdded)
{
    int hashingPosition = hashFunction((toBeAdded->getValue());
    bool flag = false;
    while (!flag && hashingPosition < capacity)
    if (theArray[hashingPosition]==nullptr)
    {
        theArray[hashingPosition] = toBeAdded;
        flag = true;
    }
    else
    {
        ++hashingPosition;
    }
    return flag;
}

bool simpleHashTable::exists(treeNode* toCompare)
{
    int hashingPosition = hashFunction(toCompare->getValue());
    bool result = false;
    while (!result)
    {
        if (theArray[hashingPosition] == nullptr)
            return false;
        if (theArray[hashingPosition] == toCompare->getValue())
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

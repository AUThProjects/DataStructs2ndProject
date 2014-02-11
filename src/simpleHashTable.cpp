#include <climits>
#include "../include/simpleHashTable.h"
#define A_BIG_PRIME_NUMBER 993319


simpleHashTable::simpleHashTable(int sizeToInitializeTo)
{
    //ctor
    this->theArray = new int[sizeToInitializeTo];
    this->capacity = sizeToInitializeTo;
    this->currentSize = 0;
    for (int i=0;i<capacity;++i)
    {
        this->theArray+i = -INT_MAX;
    }

}

simpleHashTable::simpleHashTable(int sizeToInitializeTo, int defaultValue)
{
    //ctor
    this->theArray = new int[sizeToInitializeTo];
    this->capacity = sizeToInitializeTo;
    this->currentSize = 0;
    for (int i=0;i<capacity;++i)
    {
        this->theArray+i = defaultValue;
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

bool simpleHashTable::addElement(int id)
{
    int hashingPosition = hashFunction(id);
    bool flag = false;
    while (!flag && hashingPosition < capacity)
    if (theArray[hashingPosition]==-INT_MAX)
    {
        theArray[hashingPosition] = id;
        flag = true;
    }
    else
    {
        ++hashingPosition;
    }
    return flag;
}

bool simpleHashTable::exists(int id)
{
    int hashingPosition = hashFunction(id);
    bool result = false;
    while (!result)
    {
        if (theArray[hashingPosition] == -INT_MAX)
            return false;
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

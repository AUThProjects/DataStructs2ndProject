/*

C/C++ File
Anagnostou Antonis

Comments:


*/#include "../include/ComplexHashTable.h"
#define A_BIG_PRIME_NUMBER 993319

ComplexHashTable::ComplexHashTable(int sizeToInitializeTo)
{
    this->theArray = new complexHashEntry*[sizeToInitializeTo];
    this->capacity = sizeToInitializeTo;
    this->currentSize = 0;
    for(int i=0;i<capacity; i++)
    {
        this->theArray[i]= nullptr;
    }
}

ComplexHashTable::~ComplexHashTable()
{
    delete this->theArray;
}

int ComplexHashTable::getCapacity()
{ return this->capacity; }

int ComplexHashTable::getCurrentSize()
{ return this->currentSize; }

ComplexHashTable::complexHashEntry* ComplexHashTable::getElement(int id)
{
    int hashingPosition = hashFunction(id);
    complexHashEntry* result = nullptr;
    while (result==nullptr)
    {
        if (theArray[hashingPosition] == nullptr)
            return nullptr;
        if (theArray[hashingPosition]->id == id)
        {
            result = theArray[hashingPosition];
            return result;
        }
        else
        {
            hashingPosition = (1+hashingPosition)%capacity;
        }
    }
    return nullptr;
}
bool ComplexHashTable::addElement(complexHashEntry* value)
{
    int hashingPosition = hashFunction(value->id);
    bool flag = false;
    while (!flag && hashingPosition < capacity)
    if (theArray[hashingPosition]==nullptr)
    {
        theArray[hashingPosition] = value;
        flag = true;
    }
    else
    {
        ++hashingPosition;
    }
    return flag;
}
bool ComplexHashTable::exists(int id)
{
    int hashingPosition = hashFunction(id);
    bool result = false;
    while (!result)
    {
        if (theArray[hashingPosition] == nullptr)
            return false;
        if (theArray[hashingPosition]->id == id)
        {
            result = true;
            return result;
        }
        else
        {
            hashingPosition = (1+hashingPosition)%capacity;
        }
    }
    return false;
}
int ComplexHashTable::hashFunction(int value)
{
    return (value%A_BIG_PRIME_NUMBER)%capacity;
}

ComplexHashTable::complexHashEntry* ComplexHashTable::getFirstSpecificOccurence(int valueToSearch)
{
    for (int i=0;i<this->capacity;i++)
    {
        if (this->theArray[i]!= nullptr && this->theArray[i]->weight == valueToSearch)
        {
            return this->theArray[i];
        }
    }
    return nullptr;
}

int ComplexHashTable::sumOfValues()
{
    int sum = 0;
    for (int i = 0;i<this->capacity, i++)
    {
        if (theArray[i] != nullptr)
            sum += this->theArray[i]->weight;
    }

    return sum;
}

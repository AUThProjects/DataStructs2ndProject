/*

C/C++ File
Anagnostou Antonis

Comments:


*/#include "../include/ComplexHashTable.h"
#define A_BIG_PRIME_NUMBER 993319
#define A_SMALL_PRIME_NUMBER 13

#include <iostream>

using namespace std;

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

void ComplexHashTable::onDestroy()
{
    for (int i = 0; i<this->capacity;i++)
    {
        if (theArray[i]!=nullptr)
            delete theArray[i];
    }

    this->currentSize = 0;
}


/************************ Accessors ******************************/
int ComplexHashTable::getCapacity()
{ return this->capacity; }

int ComplexHashTable::getCurrentSize()
{ return this->currentSize; }

ComplexHashTable::complexHashEntry* ComplexHashTable::getElement(int id)
{
    int hashingPosition = hashFunction(id);
    complexHashEntry* result = nullptr;
    int counter = 0;
    while (result==nullptr)
    {
        if (counter++ == capacity)
            return nullptr;
        if (theArray[hashingPosition] == nullptr) // finds empty entry in the hashtable
            return nullptr;
        if (theArray[hashingPosition]->id == id) // hash found the entry
        {
            result = theArray[hashingPosition];
            return result;
        }
        else
        {
            hashingPosition = (1+hashingPosition)%capacity; // linear cyclical hashing
        }
    }
    return nullptr;
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


bool ComplexHashTable::addElement(complexHashEntry* value)
{
    cout << "inside add ele";
    int hashingPosition = hashFunction(value->id);
    bool flag = false;
    if (this->capacity == this->currentSize)
    {
        throw -2;
        return false;
    }
    while (!flag)
    {
            cout << hashingPosition << endl;
        if (theArray[hashingPosition]==nullptr)
        {
            theArray[hashingPosition] = new complexHashEntry;
            // make a deep copy.
            theArray[hashingPosition]->id = value->id;
            theArray[hashingPosition]->position = value->position;
            theArray[hashingPosition]->weight = value->weight;
            flag = true; // return true that the value has been added
            ++currentSize;
            return flag;
        }
        else if (theArray[hashingPosition]->id == value->id)
        {
            // the id that you are trying to add already exists
            cout << "Hello";
            flag = false;
            return flag;
        }
        else
        {
            hashingPosition = (hashingPosition+1)%capacity; // cuclical linear hashing
        }
    }
    return flag;
}


bool ComplexHashTable::exists(int id)
{
    if (this->getElement(id) == nullptr)
        return false;
    else
        return true;
}


int ComplexHashTable::hashFunction(int value)
{
   return ((value%A_BIG_PRIME_NUMBER)^A_SMALL_PRIME_NUMBER)%capacity;
}



int ComplexHashTable::sumOfValues()
{
    int sum = 0;
    for (int i = 0;i<this->capacity; i++)
    {
        if (theArray[i] != nullptr)
            sum += this->theArray[i]->weight;
    }

    return sum;
}

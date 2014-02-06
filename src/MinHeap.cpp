/*

C/C++ File
Anagnostou Antonis

Comments:


*/#include "MinHeap.h"

MinHeap::MinHeap(int size)
{
    theMinHeap = new int[size];
    theIndex = new int[size];

    this->maxSize = size;
}

MinHeap::MinHeap(int* array, int* indexArray ,int size): MinHeap(size)
{
    if(theMinHeap!=nullptr)
    {
        delete[] (theMinHeap);
        theMinHeap = nullptr;
    }
    if(theIndex!=nullptr)
    {
        delete[] (theIndex);
        theIndex = nullptr;
    }
    this->theMinHeap = array;
    this->theIndex = indexArray;
    this->currentSize = size;
    makeHeap(array, size);
}

MinHeap::~MinHeap()
{
    //dtor
}

bool MinHeap::insert(int key)
{
    return true;
}

int MinHeap::getMin()
{
    if(currentSize==0)
        throw -2; //Out of bounds..

    return theMinHeap[0];
}

idWeightResult MinHeap::popMin()
{
    if(currentSize==0)
        throw -2; //Out of bounds..

    idWeightResult toBeReturned;
    toBeReturned.id = theIndex[0];
    toBeReturned.weight = theMinHeap[0];

    int y = theMinHeap[currentSize-- - 1];

    int i = 0;
    int child = 1;
    while(child <= currentSize)
    {
        if(child<currentSize && theMinHeap[child] > theMinHeap[child +1])
            child++;
        if(y < theMinHeap[child])
            break;

        theMinHeap[i] = theMinHeap[child];
        i = child;
        child *=2;
    }
    heap[i] = y;
    return toBeReturned;
}

void MinHeap::editById(int id, int value)
{
    int position = returnPosition(id);
    theMinHeap[position] = value;
    // two checks, mutually exclusive
    // 1. Check if value<parent
    // 2. Check if value>children

    this->checkLower(position);
    this->checkUpper(position);
}

void MinHeap::checkUpper(int position)
{
    while(position > 0)
    {
        int parentPosition = position/2;
        if(theMinHeap[position] < theMinHeap[parentPosition])
        {
            // swap the parent with the child
            int temp = theMinHeap[position];
            theMinHeap[position] = theMinHeap[parentPosition];
            theMinHeap[parentPosition] = temp;

            temp = theIndex[position];
            theIndex[position] = theIndex[parentPosition];
            theIndex[parentPosition] = temp;

            position = parentPosition;
        }
        else
            return;
    }
}

void MinHeap::checkLower(int position)
{
    int childPosition = 2*position+1;
    while (childPosition < this->currentSize)
    {
        if (childPosition+1 < currentSize && theMinHeap[childPosition] > theMinHeap[childPosition+1])
        {
            childPosition = childPosition+1;
        }
        if (theMinHeap[position]>theMinHeap[childPosition])
        {
            // swap
            int temp = theMinHeap[position];
            theMinHeap[position] = theMinHeap[childPosition];
            theMinHeap[childPosition] = temp;

            temp = theIndex[position];
            theIndex[position] = theIndex[childPosition];
            theIndex[childPosition] = theIndex[position];
            position = childPosition;
        }
        else
            return;
    }
}
int MinHeap::returnPosition(int id)
{
    for(int i = 0; i< this->currentSize; i++)
    {
        if(this->theIndex[i] == id)
            return i;
    }
}

bool MinHeap::makeHeap(int* array, int size)
{

    for(int i = currentSize/2; i>=0; i--)
    {
        int root = theMinHeap[i];

        int child = 2*i +1;

        while(child <= currentSize)
        {
            if(child<currentSize && theMinHeap[child] > theMinHeap[child+1])
                child++;
            if(root < theMinHeap[child])
                break;

            theMinHeap[child/2] = theMinHeap[child];
            theIndex[child/2] = theIndex[child];
            child *= 2;
        }
        theMinHeap[child/2] = root;
        theIndex[child/2] = theIndex[i];
    }
}

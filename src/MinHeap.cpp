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

bool MinHeap::editById(int id, int value)
{
    int position = returnPosition(id);
    theMinHeap[position] = value;
    if(theMinHeap[position] < theMinHeap[position/2])
    {
        // Case where the element has to go "up"

    }
    else if(theMinHeap[position] > theMinHeap[2*position + 1]
            || theMinHeap[position] > theMinHeap[2*position + 1])
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

/*

C/C++ File
Anagnostou Antonis

Comments:


*/#include "../include/MinHeap.h"


MinHeap::MinHeap(int size)
{
    theMinHeap = new minHeapEntry*[size];
    for(int i = 0 ; i< size; i++)
    {
        theMinHeap[i] = nullptr;
    }
    theIndex = new ComplexHashTable(size*2);

    this->maxSize = size;
}

MinHeap::MinHeap(AVL *anAVL ,int size): MinHeap(size)
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
    treeNode** inOrderArray = anAVL->getInOrder(anAVL->getHead());
    minHeapEntry** initialMinHeapArray = new minHeapEntry*[size];
    for(int i=0; i<size; i++)
    {
        initialMinHeapArray[i] = new minHeapEntry;
        initialMinHeapArray[i]->id = inOrderArray[i]->getValue();
        initialMinHeapArray[i]->weight = inOrderArray[i]->getWeight();
        ComplexHashTable::complexHashEntry* entry = new ComplexHashTable::complexHashEntry;
        entry->id = inOrderArray[i]->getValue();
        entry->weight = inOrderArray[i]->getWeight();
        entry->position = i;
        this->theIndex->addElement(entry);
    }

    this->theMinHeap = initialMinHeapArray;
    this->currentSize = size;
    makeHeap();
}

MinHeap::~MinHeap()
{
    //dtor
    // Has to delete each struct.

}

int MinHeap::getMin()
{
    if(currentSize==0)
        throw -2; //Out of bounds..

    return theMinHeap[0]->weight;
}

MinHeap::minHeapEntry MinHeap::popMin()
{
    if(currentSize==0)
        throw -2; //Out of bounds..

    minHeapEntry toBeReturned;
    toBeReturned.id = theMinHeap[0]->id;
    toBeReturned.weight = theMinHeap[0]->weight;

    minHeapEntry* lastElementInHeap = theMinHeap[currentSize-- - 1];

    int posOfCheckingNode = 0;
    theMinHeap[0] = lastElementInHeap; //put the last element in the position of the root
    theIndex->getElement(theMinHeap[0]->id)->position = 0; //changes the last element's position in the index

    checkLower(posOfCheckingNode);

    return toBeReturned;
}

void MinHeap::editById(int id, int value)
{
    // get the element from the index with the id provided
    ComplexHashTable::complexHashEntry* elementToChange = theIndex->getElement(id);
    int positionToCheck = elementToChange->position;

    elementToChange->weight = value;

    // change inside the minHeap;
    theMinHeap[positionToCheck]->weight = value;

    // make the necessary checks

    // two checks, mutually exclusive
    // 1. Check if value<parent
    // 2. Check if value>children
    // 3. Check if parent<value<minOfChildren

    this->checkLower(positionToCheck);
    this->checkUpper(positionToCheck);
}

void MinHeap::checkUpper(int position)
{
    while(position > 0)
    {
        int parentPosition = position/2;
        if(theMinHeap[position] < theMinHeap[parentPosition])
        {
            // swap the parent with the child
            minHeapEntry* temp = theMinHeap[position];
            theMinHeap[position] = theMinHeap[parentPosition];
            theMinHeap[parentPosition] = temp;

            theIndex->getElement(theMinHeap[position]->id)->position = position;
            theIndex->getElement(theMinHeap[parentPosition]->id)->position = parentPosition;


            position = parentPosition;
        }
        else
            return;
    }
}

void MinHeap::checkLower(int posOfCheckingNode)
{
    while(posOfCheckingNode < currentSize)
    {
        //find min of children, if it has children
        //3 alternatives
        //1. no children (leaf)
        //2. one child (swap)
        //3. two children (find min and swap)
        int firstChildPosition = posOfCheckingNode*2+1;
        if (firstChildPosition >= currentSize && firstChildPosition+1 >= currentSize)
        {
            // case 1.
            // do nothing.
        }
        else if (firstChildPosition+1 == currentSize)
        {
            // case 2.
            // check and swap
            if (theMinHeap[firstChildPosition]->weight < theMinHeap[posOfCheckingNode]->weight)
            {
                int parentID = theMinHeap[posOfCheckingNode]->id;
                int childID = theMinHeap[firstChildPosition]->id;
                // swap
                minHeapEntry *temp = theMinHeap[firstChildPosition];
                theMinHeap[firstChildPosition] = theMinHeap[posOfCheckingNode];
                theMinHeap[posOfCheckingNode] = temp;

                // change the index
                int parentPosition = theIndex->getElement(parentID)->position;
                theIndex->getElement(parentID)->position = theIndex->getElement(childID)->position;
                theIndex->getElement(childID)->position = parentPosition;

                posOfCheckingNode *=2;
            }
        }
        else if (firstChildPosition < currentSize && firstChildPosition+1 < currentSize)
        {
            // case 3.
            // find min weight between child nodes
            minHeapEntry** minElement = &theMinHeap[firstChildPosition];
            if ((*minElement)->weight > theMinHeap[firstChildPosition+1]->weight)
            {
                minElement = &theMinHeap[firstChildPosition+1];
            }

            if ((*minElement)->weight < theMinHeap[posOfCheckingNode]->weight)
            {
                int parentID = theMinHeap[posOfCheckingNode]->id;
                int childID = (*minElement)->id;
                // swap
                minHeapEntry *temp = *minElement;
                *minElement = theMinHeap[posOfCheckingNode];
                theMinHeap[posOfCheckingNode] = temp;

                // change the index
                int parentPosition = theIndex->getElement(parentID)->position;
                theIndex->getElement(parentID)->position = theIndex->getElement(childID)->position;
                theIndex->getElement(childID)->position = parentPosition;
                posOfCheckingNode *=2;
            }
        }
    }
}


bool MinHeap::makeHeap()
{

    for(int i = currentSize/2; i>=0; i--)
    {
        minHeapEntry* root = theMinHeap[i];

        int child = 2*i +1;

        while(child <= currentSize)
        {
            if(child<currentSize && theMinHeap[child]->weight > theMinHeap[child+1]->weight)
                child++;
            if(root->weight < theMinHeap[child]->weight)
                break;

            //Check for potential mistakes
            theMinHeap[child/2] = theMinHeap[child];
            ComplexHashTable::complexHashEntry* element = theIndex->getElement(theMinHeap[child/2]->id);
            element->position = child;
            child *= 2;
        }
        theMinHeap[child/2] = root;
        ComplexHashTable::complexHashEntry* element = theIndex->getElement(theMinHeap[child/2]->id);
        element->position = i;
    }
}

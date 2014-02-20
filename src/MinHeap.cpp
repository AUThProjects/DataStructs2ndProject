/*

C/C++ File
Anagnostou Antonis

Comments:


*/#include "../include/MinHeap.h"

/* DEBUGGING PURPOSES
void MinHeap::print()
{
    cout << "Printing the minheap.. " <<endl;
    for (int i=0;i<currentSize;i++)
    {
        cout << theMinHeap[i]->id << ", " << theMinHeap[i]->weight << endl;
    }

    cout<< "Printing the hashtable.. "<< endl;
    theIndex->print();
}
*/


MinHeap::MinHeap(int size)
{
    theMinHeap = new minHeapEntry*[size];
    theIndex = new ComplexHashTable(size*2); // initializes its contents to nullptr inside the class
    // initilize the values of the minHeap to default value (nullptr)
    for(int i = 0 ; i< size; i++)
    {
        theMinHeap[i] = nullptr;
    }
    this->currentSize = 0;
    this->maxSize = size;
}

MinHeap::MinHeap(AVL *anAVL ,int size): MinHeap(size)
{
    if (anAVL->getNumberOfLeaves()>size)
        throw -3;
    treeNode** inOrderArray = anAVL->getInOrder(anAVL->getHead());
    minHeapEntry** initialMinHeapArray = new minHeapEntry*[size];
    this->currentSize = anAVL->getNumberOfLeaves();
    for(int i=0; i<currentSize; i++)
    {
        //cout << i;
        initialMinHeapArray[i] = new minHeapEntry;
        // make deep copies
        // 1. to the MinHeapArray
        initialMinHeapArray[i]->id = inOrderArray[i]->getValue();
        initialMinHeapArray[i]->weight = inOrderArray[i]->getWeight();
        // 2. to the CompexHashTable
        ComplexHashTable::complexHashEntry* entry = new ComplexHashTable::complexHashEntry;
        entry->id = inOrderArray[i]->getValue();
        entry->weight = inOrderArray[i]->getWeight();
        entry->position = i;
        this->theIndex->addElement(entry);
    }
   // cout << "end";
    this->theMinHeap = initialMinHeapArray;
    makeHeap();
}

MinHeap::~MinHeap()
{
    //dtor
    // Has to delete each struct.
    for(int i=0; i< this->currentSize; i++)
    {
        if(this->theMinHeap[i]!=nullptr)
        {
            delete theMinHeap[i];
        }
    }
    delete theMinHeap;
    delete theIndex;
}

bool MinHeap::isEmpty()
{
    return (this->currentSize == 0);
}
// adds only the element that are non-existent
bool MinHeap::addElement(treeNode* treeNodeToInsert)
{
    this->addElement(treeNodeToInsert,0);
}

bool MinHeap::addElement(treeNode* treeNodeToInsert, int toBeIncreased)
{
    if (this->theIndex->exists(treeNodeToInsert->getValue()))
    {
        return false;
    }
    else if (this->currentSize == this->maxSize)
    {
        throw -2; // full heap
        return false;
    }
    else
    {
        // create the struct entries
        // Deep copy
        // 1. in minheeap
        minHeapEntry* toBeAddedInHeap = new minHeapEntry;
        toBeAddedInHeap->id = treeNodeToInsert->getValue();
        toBeAddedInHeap->weight = treeNodeToInsert->getWeight() + toBeIncreased;
        // 2. in index.
        ComplexHashTable::complexHashEntry* toBeAddedInIndex = new ComplexHashTable::complexHashEntry;
        toBeAddedInIndex->id = treeNodeToInsert->getValue();
        toBeAddedInIndex->weight = treeNodeToInsert->getWeight() + toBeIncreased;
        toBeAddedInIndex->position = this->currentSize;

        theIndex->addElement(toBeAddedInIndex);

        this->theMinHeap[currentSize] = toBeAddedInHeap;
        this->checkUpper(currentSize);
        ++currentSize;
        return true;
    }
    return false;
}

MinHeap::minHeapEntry MinHeap::getMin()
{
    if(currentSize==0)
        throw -2; //Out of bounds..

    return *(theMinHeap[0]);
}

MinHeap::minHeapEntry MinHeap::popMin()
{

    if(currentSize==0)
        throw -2; //Out of bounds..

    // Deep copy of the element to be returned
    minHeapEntry toBeReturned;
    toBeReturned.id = theMinHeap[0]->id;
    toBeReturned.weight = theMinHeap[0]->weight;

    minHeapEntry* lastElementInHeap = theMinHeap[currentSize-- - 1];

    int posOfCheckingNode = 0;
    theMinHeap[0] = lastElementInHeap; //put the last element in the position of the root

    theIndex->deleteElement(toBeReturned.id);
    theIndex->getElement(lastElementInHeap->id)->position = 0;
    //cout << "ftasame ew" << endl;
    checkLower(posOfCheckingNode);

    return toBeReturned;
}

MinHeap::minHeapEntry* MinHeap::getElement(int id)
{
    // get the element from the index with the id provide
    ComplexHashTable::complexHashEntry* searchElement = theIndex->getElement(id);
    if(searchElement == nullptr)
        return nullptr;
    // if the element has been deleted and it is still on the hashtable
    if(searchElement->position==-1)
        return nullptr;

    return theMinHeap[searchElement->position];
}

bool MinHeap::editById(int id, int value)
{
    // get the element from the index with the id provide
    ComplexHashTable::complexHashEntry* elementToChange = theIndex->getElement(id);
    if(elementToChange == nullptr)
        return false;

    int positionToCheck = elementToChange->position;

    // if the element has been deleted and it is still on the hashtable
    if(positionToCheck==-1)
        return false;

    // change inside the index
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
    return true;
}

void MinHeap::checkUpper(int position)
{
    //cout<< "inside check upper"<< endl;
    while(position > 0)
    {
        int parentPosition = position/2;
        //cout << "Parent position: " <<parentPosition << "Child position: " <<position << endl;
        if(theMinHeap[position]->weight < theMinHeap[parentPosition]->weight)
        {
            // swap the parent with the child
            //cout << "Attempting to swap.." << endl;
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
            //cout << "No children" <<endl;
            return;
        }
        else if (firstChildPosition+1 == currentSize)
        {
            // case 2.
            // check and swap
            //cout << "One child" << endl;
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

            }
            posOfCheckingNode = posOfCheckingNode* 2 + 1;

        }
        else if (firstChildPosition < currentSize && firstChildPosition+1 < currentSize)
        {
            // case 3.
            // find min weight between child nodes
            //cout << "Two children" << endl;
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

                // checking positions
                //cout << "Parent Position before" << theIndex->getElement(parentID)->position << endl;
                //cout << "Child Position before" << theIndex->getElement(childID)->position << endl;
                // change the index
                int parentPosition = theIndex->getElement(parentID)->position;
                theIndex->getElement(parentID)->position = theIndex->getElement(childID)->position;
                theIndex->getElement(childID)->position = parentPosition;
                //cout << "Parent Position after" << theIndex->getElement(parentID)->position << endl;
                //cout << "Child Position after" << theIndex->getElement(childID)->position << endl;
            }
            posOfCheckingNode = posOfCheckingNode* 2 + 1;
        }
    }
}


bool MinHeap::makeHeap()
{
   // cout << "Making heap.. current size= " << this->currentSize<<endl;
    for(int i = currentSize/2; i>=0; i--)
    {
        minHeapEntry* root = theMinHeap[i];

        int child = 2*i +1;

        while(child < currentSize)
        {
            if(child<currentSize-1 && theMinHeap[child]->weight > theMinHeap[child+1]->weight)
            {
                child++;
                //cout << "Here " <<endl;
            }
            if(root->weight < theMinHeap[child]->weight)
            {
              //  cout << "Here2 " <<endl;
                break;
            }
            //Check for potential mistakes
            theMinHeap[child/2] = theMinHeap[child];
            child *= 2;
        }
        theMinHeap[child/2] = root;
    }

    for(int i=0; i<currentSize; i++)
    {
        theIndex->getElement(theMinHeap[i]->id)->position = i;
    }
}
/*
void MinHeap::visitNewNode(int startingID, AVL* theAvl, ComplexHashTable* previousAndDistanceHash)
{
    treeNode** inorderOfAvl = theAvl->getInOrder(theAvl->getHead());
    for (int i=0;i<theAvl->getNumberOfLeaves();i++)
    {
        try
        {
            if (!this->addElement(inorderOfAvl[i]))
            {
                int idToCheck = inorderOfAvl[i]->getValue();
                int idOfPrevious = previousAndDistanceHash->getElement(idToCheck)->position;
                if (inorderOfAvl[i]->getWeight()
                    + theIndex->getElement(idOfPrevious)->weight < previousAndDistanceHash->getElement(idToCheck)->weight)
                {

                }
            }
        }
        catch(int number)
        {
            if (number == -2)
                cerr << "Full minHeap" << endl;
        }
    }
}
*/

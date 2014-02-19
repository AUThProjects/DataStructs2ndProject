#include "../include/Database.h"
#include "../include/MinHeap.h"
#include <cmath>
#include <ctime>
#include <climits>
#define INITIAL_SIZE 100000


using namespace std;

Database::Database()
{
    //ctorc
    theDatabase = new Node*[INITIAL_SIZE];

    capacity = INITIAL_SIZE;
    for(int i =0; i<capacity; ++i)
    {
        theDatabase[i] = nullptr;
    }

    sizeOfDatabase = 0;
}

Database::~Database()
{
    //dtor
    delete(theDatabase);
    theDatabase = nullptr;
    capacity = 0;
    sizeOfDatabase = 0;
}

// public

int Database::hashFunction(int key)
{
    int myIterator = 0;
    int pos = 0;
    if (key<0)
        return -1;

    pos = hashFunction(key, myIterator);
    while (theDatabase[pos]!=nullptr && theDatabase[pos]->getID()!=key)
        pos = hashFunction(key, ++myIterator);
    //cout << "pos=" << pos << endl;
    return pos;

}

int Database::hashFunction(int key, int iteration)
{
    return (auxHashFunction1(key)+iteration*auxHashFunction2(key))%capacity;
}

int Database::auxHashFunction1(int key)
{
    return key%capacity;
}

int Database::auxHashFunction2(int key)
{
    return 1+key%(capacity-1);
}


/* inserts a new Node to the Database Array
 * to the position to remain sorted
*/
bool Database::insertNewLink(int leftId, int rightId, int weight)
{
    bool toBeReturned = false;
    /*
    for (int i=0;i<=1;++i)
    {
        Node** resultNode = searchNodeByID(leftId);
        if (*resultNode == nullptr)
        {
            *resultNode = new Node(leftId);
        }
        toBeReturned = toBeReturned || (*resultNode)->addNewNode(rightId, weight);
        cout << **resultNode << endl;
        int temp = leftId;
        leftId = rightId;
        rightId = temp;
    }
    //cout << *theDatabase[21] << endl;
    return toBeReturned;
    */
    for (int i=0;i<=1;++i)
    {

        if (theDatabase[hashFunction(leftId)] != nullptr)
        {
            toBeReturned = theDatabase[hashFunction(leftId)]->addNewNode(rightId, weight);
        }
        else
        {
            Node* nodeToInsert = new Node(leftId);
            ++(this->sizeOfDatabase);
            nodeToInsert->addNewNode(rightId, weight);
            theDatabase[hashFunction(leftId)] = nodeToInsert;
        }
        int temp = leftId;
        leftId = rightId;
        rightId = temp;

    }
    //cout << *theDatabase[hashFunction(leftId)] << endl;
    //cout << *this << endl;
    return toBeReturned;
}


bool Database::deleteExistingLink(int leftId, int rightId)
{
    bool toBeReturned = false;
    for (int i=0;i<=1;++i)
    {
        if (theDatabase[hashFunction(leftId)] != nullptr)
        {
            toBeReturned = theDatabase[hashFunction(leftId)]->deleteNode(rightId);
        }
        int temp = leftId;
        leftId = rightId;
        rightId = temp;
    }
    return toBeReturned;
}



Node ** Database::searchNodeByID(int idToSearch)
{
    int res = hashFunction(idToSearch);
    cout << "res=" << res << endl;
    return &(theDatabase[res]);
}


Database::resultOfMST Database::calculateMST()
{

    time_t beginTimestamp;
    time(&beginTimestamp); // get starting timestamp
    int idOfStartingNode = -1;
    AVL* avlOfStartingNode = nullptr;

    /*
        Correspondence:
        id = id;
        position = previous;
        weight = key;
    */
    ComplexHashTable *previousAndDistanceHash = new ComplexHashTable(2*this->sizeOfDatabase);
    for(int i=0; i<this->capacity; i++)
    {
        if (theDatabase[i]!=nullptr)
        {
            // initialization of previous and distance hash
            Node* elementFromDatabase = theDatabase[i];
            ComplexHashTable::complexHashEntry* tempEntry = new ComplexHashTable::complexHashEntry;
            tempEntry->id = elementFromDatabase->getID();
            tempEntry->weight = INT_MAX;
            tempEntry->position = -INT_MAX; // signifies null
            previousAndDistanceHash->addElement(tempEntry);
        }
    }

    previousAndDistanceHash->print();


    // get the first record in the previousAndDistanceHash to start the MST algo
    ComplexHashTable::complexHashEntry* nextToVisit = previousAndDistanceHash->getFirstSpecificOccurence(INT_MAX);
    cout << "starting" << nextToVisit->id << endl;

    bool flag = false;
    MinHeap* Q;
    // get the next unvisited node if any
    while (nextToVisit != nullptr)
    {
        // initialize the first AVL (for ctor of minHeap)
        if (!flag)
        {
            AVL* avlOfStartingNode = (*this->searchNodeByID(nextToVisit->id))->getAVLTree();
            Q = new MinHeap(avlOfStartingNode ,this->sizeOfDatabase);
            flag = true;
        }
        Q->print();
        // initialize default value for starting point of MST
        //nextToVisit->position = -INT_MAX; // unnecessary
        nextToVisit->weight = 0;
        bool flag1 = false;
        // do the MST
        while(!Q->isEmpty())
        {
            MinHeap::minHeapEntry U = Q->popMin();
            if (flag1 == false)
            {
                previousAndDistanceHash->getElement(U.id)->position = nextToVisit->id;
                flag1 = true;
            }
            previousAndDistanceHash->getElement(U.id)->weight = U.weight;
            Q->print();
            AVL* neighboursAVL = (*this->searchNodeByID(U.id))->getAVLTree();
            treeNode** inOrderAVL = neighboursAVL->getInOrder(neighboursAVL->getHead());



            cout << "the inorder" << endl;
            for(int i=0; i<neighboursAVL->getNumberOfLeaves(); i++)
            {
                cout << inOrderAVL[i]->getValue() << endl;
            }

            previousAndDistanceHash->print();

            for(int i=0; i<neighboursAVL->getNumberOfLeaves(); i++)
            {
                if (previousAndDistanceHash->getElement(inOrderAVL[i]->getValue())->weight == INT_MAX)
                {
                    bool justAdded = Q->addElement(inOrderAVL[i]);
                    if (!justAdded && inOrderAVL[i]->getWeight() < (Q->getElement(inOrderAVL[i]->getValue()))->weight)
                    {
                        Q->editById(inOrderAVL[i]->getValue(), inOrderAVL[i]->getWeight());
                        previousAndDistanceHash->getElement(inOrderAVL[i]->getValue())->position = U.id;
                        // do not change the weight in previousAndDistanceHash -> haven't visited it yet.
                    }
                    else if (justAdded)
                    {
                        previousAndDistanceHash->getElement(inOrderAVL[i]->getValue())->position = U.id;
                    }
                }
            }
            delete inOrderAVL;


        }
        nextToVisit = previousAndDistanceHash->getFirstSpecificOccurence(INT_MAX);
        //cout  << "Now preparing to visit"<< nextToVisit->id << endl;
    }

    time_t endingTimestamp;
    time(&endingTimestamp); // get ending timestamp
    resultOfMST toBeReturned;
    toBeReturned.timeElapsedInSec = difftime(endingTimestamp, beginTimestamp);
    toBeReturned.totalCost = previousAndDistanceHash->sumOfValues();
    delete Q;
    delete previousAndDistanceHash;
    cout << beginTimestamp << endl;
    cout << endingTimestamp << endl;
    double time1 = time(0)*1000;
    cout << time << endl;
    return toBeReturned;
}

int Database::commonNeighbours(int idOfNode1, int idOfNode2)
{
    Node* node1;
    Node* node2;
    Node** temp;
    temp = this->searchNodeByID(idOfNode1);
    if (temp!=nullptr)
        node1 = *temp;
    else
        return 0;
    temp = this->searchNodeByID(idOfNode2);
    if (temp!=nullptr)
        node2 = *temp;
    else return 0;
    return commonNeighbours(node1, node2);
}

int Database::commonNeighbours(Node* node1, Node* node2)
{
    AVL::resultOfIntesection res = node1->getAVLTree()->intersectWithAVL(node2->getAVLTree());
    return res.sizeOfArray;
}

ComplexHashTable* Database::shortestPath_Dijkstra(int idOfStartingNode)
{
    /*
     * Correspondence between complexHashEntry and dijkstra variables.
     *  id->id
     *  weight->distance
     *  position->previous
     */
    ComplexHashTable *previousAndDistanceHash = new ComplexHashTable(2*this->sizeOfDatabase);
    // populate the previous and distance hash
    for (int i=0;i<capacity;i++)
    {
        if (theDatabase[i]!=nullptr)
        {
            Node* elementFromDatabase = theDatabase[i];
            ComplexHashTable::complexHashEntry* tempEntry = new ComplexHashTable::complexHashEntry;
            tempEntry->id = elementFromDatabase->getID();
            tempEntry->weight = INT_MAX;
            tempEntry->position = -INT_MAX; // signifies null
            previousAndDistanceHash->addElement(tempEntry);
           //cout << "Put id " << tempEntry->id << "with weight " << tempEntry->weight <<endl;
        }
    }
   // cout << (*this->searchNodeByID(8))->getID();

    previousAndDistanceHash->getElement(idOfStartingNode)->position = 0;
    previousAndDistanceHash->getElement(idOfStartingNode)->weight = 0;
    int counter = 0;
    int* mySet = new int[sizeOfDatabase];


    AVL* avlToAdd = (*(this->searchNodeByID(idOfStartingNode)))->getAVLTree();
    treeNode** inOrderOfAVL = avlToAdd->getInOrder(avlToAdd->getHead());
    for(int i=0; i<avlToAdd->getNumberOfLeaves(); i++)
    {
        previousAndDistanceHash->getElement(inOrderOfAVL[i]->getValue())->position = idOfStartingNode;
    }
    delete inOrderOfAVL;

    MinHeap* myQ = new MinHeap(avlToAdd, this->sizeOfDatabase);
    cout << "Initial minheap"<<endl;
    myQ->print();
    cout << "Initial p&d hash" <<endl;
    previousAndDistanceHash->print();
    int idOfCurrentNode = idOfStartingNode;
    mySet[counter++] = idOfCurrentNode;
    while(!(myQ->isEmpty()))
    {
        MinHeap::minHeapEntry min = myQ->popMin();
        previousAndDistanceHash->getElement(min.id)->weight = min.weight;

        idOfCurrentNode = min.id;
        mySet[counter++] = idOfCurrentNode;

        avlToAdd = (*(this->searchNodeByID(min.id)))->getAVLTree();
        treeNode** inOrderOfAVL = avlToAdd->getInOrder(avlToAdd->getHead());
        for(int i=0; i<avlToAdd->getNumberOfLeaves(); i++)
        {
            if(inOrderOfAVL[i]->getValue() != idOfStartingNode)
            {
                bool flag = false;
                for(int j = 0; j<counter; j++)
                {
                    if(mySet[j]==inOrderOfAVL[i]->getValue())
                    {
                        flag = true;
                        break;
                    }
                }
                if(!flag)
                {

                    int idOfCheckingNeighbour = inOrderOfAVL[i]->getValue();
                    int weightOfCheckingNeighbour = inOrderOfAVL[i]->getWeight();
                    if(!myQ->addElement(inOrderOfAVL[i], previousAndDistanceHash->getElement(min.id)->weight))
                    {

                        previousAndDistanceHash->print();

                        //int currentMinWeightOfCheckingNeighbour = previousAndDistanceHash->getElement(idOfCheckingNeighbour)->weight;
                        int currentMinWeightOfCheckingNeighbour = myQ->getElement(idOfCheckingNeighbour)->weight;
                        int previousOfCheckingNeighbour = previousAndDistanceHash->getElement(idOfCheckingNeighbour)->position;
                        if(weightOfCheckingNeighbour + min.weight < currentMinWeightOfCheckingNeighbour)
                        {
                            // Change weight

                            previousAndDistanceHash->getElement(idOfCheckingNeighbour)->weight =
                                weightOfCheckingNeighbour + min.weight;
                            myQ->editById(idOfCheckingNeighbour, weightOfCheckingNeighbour + min.weight);

                            // Change previous
                            previousAndDistanceHash->getElement(idOfCheckingNeighbour)->position = min.id;
                        }
                    }
                    else
                    {
                        previousAndDistanceHash->getElement(idOfCheckingNeighbour)->position = min.id;
                    }
                }
            }

        }
        delete inOrderOfAVL;
        myQ->print();
    }


    return previousAndDistanceHash;
}


#include "../include/Database.h"
#include <cmath>
#define INITIAL_SIZE 16000

using namespace std;

Database::Database()
{
    //ctorc
    theDatabase = new Node*[INITIAL_SIZE];
    capacity = INITIAL_SIZE;
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
/* inserts a new Node to the Database Array
 * to the position to remain sorted
*/

bool Database::insertNewLink(int leftId, int rightId)
{
    //cout << "Trying to insert: " << leftId << " " << rightId << endl;

    resultOfBinary result = binarySearch(leftId);

    Node * nodeFound;
    if(result.found==true)
    {
        nodeFound = theDatabase[result.position];
    }
    else
    {
        nodeFound = nullptr;
    }

    if (nodeFound == nullptr)
    {
        // non existent left id
        Node *toBeAdded = new Node(leftId);
        toBeAdded->addNewNode(rightId);
        if(sizeOfDatabase==capacity)
        {
            myRealloc();
        }

        for(int i=sizeOfDatabase-1; i>result.position; i--)
        {
            theDatabase[i+1] = theDatabase[i];
        }
        theDatabase[result.position+1] = toBeAdded;
        sizeOfDatabase++;
        //cout << "inserted" << endl;
        return true;
    }
    else
    {
        // existent left id
        //cout << "id found and inserted" << endl;
        return nodeFound->addNewNode(rightId);
    }
}


bool Database::myRealloc()
{
    // this is called when capacity == sizeOfDatabase
    //cout << "entering myRealloc" << endl;
    Node ** dbToCopy = theDatabase;
    Node ** newDatabase = new Node*[capacity*2];
    for (int i=0;i<capacity;i++)
    {
        newDatabase[i] = dbToCopy[i];
    }
    delete (dbToCopy);
    theDatabase = newDatabase;
    capacity*=2;
    //cout << "done" << endl;
    return true;
}

bool Database::deleteExistingLink(int leftId, int rightId)
{
    Node * nodeFound = searchNodeByID(leftId);
    if (nodeFound == nullptr)
    {
        return false;
    }
    else
    {
        return nodeFound->deleteNode(rightId);
    }
}

struct resultOfBinary
{
    bool found;
    int position;
};
typedef struct resultOfBinary resultOfBinary;

Database::resultOfBinary Database::binarySearch(int idToSearch)
{
    //cout << "\n searching for: " << idToSearch << endl;

    int beginIndex = 0;
    int endIndex = sizeOfDatabase -1;
    //cout << "begin index: " << beginIndex;
    //cout << "end index: " << endIndex;
    int midIndex = (beginIndex+endIndex)/2;
    //cout << "mid index: " << midIndex;

    resultOfBinary result;
    if(this->sizeOfDatabase == 0)
    {
        result.found = false;
        result.position = -1;
        return result;
    }
    while (beginIndex <= endIndex)
    {
        //cout << "with:\n*beginIndex=" << beginIndex << "\n*endIndex=" << endIndex << "\n*midIndex=" << midIndex << endl;
        if (idToSearch > (theDatabase[midIndex])->getID() )
        {
            beginIndex = midIndex+1;
        }
        else if (idToSearch < theDatabase[midIndex]->getID())
        {
            endIndex = midIndex-1;
        }
        else
        {
            result.found = true;
            result.position = midIndex;
            return result;
        }
        midIndex = ceil((double)(beginIndex+endIndex)/2);
    }
    result.found = false;
    //cout << "with:\n*beginIndex=" << beginIndex << "\n*endIndex=" << endIndex << "\n*midIndex=" << midIndex << endl;
    result.position=midIndex-1;
    //cout << result.position << endl;
    return result;
}

Node * Database::searchNodeByID(int idToSearch)
{
    //Binary search
    resultOfBinary result = binarySearch(idToSearch);
    if (result.found==false)
        return nullptr;
    else
        return theDatabase[result.position];
}





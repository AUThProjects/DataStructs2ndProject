#ifndef DATABASE_H
#define DATABASE_H
#include "Node.h"
#include "ComplexHashTable.h"

class Database
{
    public:

        // struct for the result of Prim's algorithm
        struct resultOfMST
        {
            int totalCost;
            double timeElapsedInSec;
        };
        typedef struct resultOfMST resultOfMST;

        //ctor and dtor
        Database();
        virtual ~Database();

        //operators overloads declarations
        friend ostream& operator<< (ostream& myStream, Database& obj);
        friend istream& operator>> (istream& myStream, Database& obj);

        //insertions and deletions
        bool insertNewLink(int leftId, int rightId, int weight);
        bool deleteExistingLink(int leftId, int rightId);
        int hashFunction(int key); // the hashing function
        resultOfMST calculateMST(); // Prim's algorithm for MST (or possible forests..)
        int commonNeighbours(int idOfNode1, int idOfNode2); // Common neighbours algorithm
        ComplexHashTable* shortestPath_Dijkstra(int idOfStartingNode); // Shortest path - returns only the minimum costs array

    protected:
    private:
        // Data Structure --
        Node **  theDatabase; // hashtable

        int sizeOfDatabase; // current load of database
        int capacity; // max size to accommodate
        // internally used hashing functions
        int hashFunction(int key, int iteration);
        int auxHashFunction1(int key);
        int auxHashFunction2(int key);
        int commonNeighbours(Node* node1, Node* node2);


        //search functions
        Node** searchNodeByID(int idToSearch); // returns pointer to Node from DB
};

#endif // DATABASE_H

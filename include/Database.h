#ifndef DATABASE_H
#define DATABASE_H
#include "Node.h"

class Database
{
    private:
        // this is the type of data that BinarySearch function returns
        // we need to know if the value was found (bool found)
        // and where (int position)
        struct resultOfBinary
        {
            bool found;
            int position;
        };
        typedef struct resultOfBinary resultOfBinary;

    public:
        //ctor and dtor
        Database();
        virtual ~Database();

        //operators overloads declarations
        friend ostream& operator<< (ostream& myStream, Database& obj);
        friend istream& operator>> (istream& myStream, Database& obj);

        //insertions and deletions
        bool insertNewLink(int leftId, int rightId);
        bool deleteExistingLink(int leftId, int rightId);

    protected:
    private:
        // Data Structure --
        Node **  theDatabase; //sortedArray

        int sizeOfDatabase; // current load of database
        int capacity; // max size to accommodate
        bool myRealloc(); // realloc function

        //------------------

        //inner use for inserting new node
        bool insertNode(Node nodeToBeInserted);

        //search functions
        resultOfBinary binarySearch(int idToSearch); //general binary search function
        Node* searchNodeByID(int idToSearch); // returns pointer to Node from DB
};

#endif // DATABASE_H

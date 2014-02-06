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
        bool insertNewLink(int leftId, int rightId, int weight);
        bool deleteExistingLink(int leftId, int rightId);
        int hashFunction(int key); // the hashing function


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



        //search functions
        Node** searchNodeByID(int idToSearch); // returns pointer to Node from DB
};

#endif // DATABASE_H

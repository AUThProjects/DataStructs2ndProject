#ifndef COMPLEXHASHTABLE_H
#define COMPLEXHASHTABLE_H
#include <iostream>
using namespace std;
class ComplexHashTable
{
    public:
        void print();

        // Struct representing the records in the HashTable
        struct complexHashEntry
        {
            // the field name are relative. They don't correspond necessarily to id, weight and position.
            int id;
            int weight;
            int position;
        };
        typedef struct complexHashEntry complexHashEntry;

        // ctor
        ComplexHashTable(int sizeToInitialiizeTo);
        // dtor
        virtual ~ComplexHashTable();
        void onDestroy();
        // accessors
        int getCapacity();
        int getCurrentSize();
        complexHashEntry* getElement(int value);

        //overload operators
        friend ostream& operator<< (ostream& myStream, ComplexHashTable& obj);

        bool addElement(complexHashEntry* value);
        bool deleteElement(int id);
        bool exists(int toCompare);
        // returns the first element whose weight field equals to valueToSearch
        complexHashEntry* getFirstSpecificOccurence(int valueToSearch);

        int sumOfValues();
    protected:
    private:
        int hashFunction(int value);
        complexHashEntry** theArray; // Heap allocated Array of pointers to compexHashEntry
        int capacity;
        int currentSize;
};

#endif // COMPLEXHASHTABLE_H

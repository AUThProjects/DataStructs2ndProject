#ifndef COMPLEXHASHTABLE_H
#define COMPLEXHASHTABLE_H


class ComplexHashTable
{
    public:
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


        bool addElement(complexHashEntry* value);
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

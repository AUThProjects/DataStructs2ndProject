#ifndef COMPLEXHASHTABLE_H
#define COMPLEXHASHTABLE_H


class ComplexHashTable
{
    public:
        struct complexHashEntry
        {
            int id;
            int weight;
            int position;
        };
        typedef struct complexHashEntry complexHashEntry;
        ComplexHashTable(int sizeToInitialiizeTo);
        virtual ~ComplexHashTable();
        int getCapacity();
        int getCurrentSize();
        int getElement(int value);
        bool addElement(complexHashEntry* value);
        bool exists(int toCompare);
    protected:
    private:
        int hashFunction(int value);
        complexHashEntry** theArray; // T** for nullable
        int capacity;
        int currentSize;
};

#endif // COMPLEXHASHTABLE_H

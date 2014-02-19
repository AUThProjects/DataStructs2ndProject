#ifndef MINHEAP_H
#define MINHEAP_H
#include "ComplexHashTable.h"
#include "AVL.h"

class MinHeap
{
    public:
        void print();
        // struct that consists of the fields the minHeap contains
        struct minHeapEntry
        {
            int id; // id of record
            int weight; // weight of record
        };
        typedef struct minHeapEntry minHeapEntry;

        MinHeap(int size);
        MinHeap(AVL *anAVL ,int size); // overload to intialize MinHeap from AVL in O(n)
        virtual ~MinHeap();

        bool addElement(treeNode* treeNodeToInsert);
        minHeapEntry getMin(); // get the record with min weight without deleting it.
        minHeapEntry popMin(); // get and delete the record with min weight
        void editById(int id, int value); // edits specific item within the minHeap and index
        bool isEmpty(); // returns true if the minHeap is empty, false otherwise
    protected:
        minHeapEntry **theMinHeap; // the actual minHeap
        ComplexHashTable* theIndex; // assistive Data Structure to support quick search

        int currentSize;
        int maxSize;
    private:
        bool makeHeap();
        void checkUpper(int position); // checks the upper part of the minheap for swaps needed to be made
        void checkLower(int position); // checks the lower part of the minheap for swaps needed to be made
};

#endif // MINHEAP_H

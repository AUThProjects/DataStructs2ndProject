#ifndef MINHEAP_H
#define MINHEAP_H
#include "ComplexHashTable.h"
#include "AVL.h"

class MinHeap
{
    public:
        struct minHeapEntry
        {
            int id;
            int weight;
        };
        typedef struct minHeapEntry minHeapEntry;

        MinHeap(int size);
        MinHeap(AVL *anAVL ,int size);
        virtual ~MinHeap();

        bool addElement(treeNode* treeNodeToInsert);
        void visitNewNode(AVL* theAvl, ComplexHashTable* previousAndDistanceHash);
        int getMin(); // simply get the Node with the min cost
        minHeapEntry popMin(); // get and delete from the heap the Node with the min cost
        void editById(int id, int value);

    protected:
        minHeapEntry **theMinHeap;
        ComplexHashTable* theIndex;

        int currentSize;
        int maxSize;
    private:
        bool makeHeap();
        void checkUpper(int position);
        void checkLower(int position);

};

#endif // MINHEAP_H

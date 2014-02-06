#ifndef MINHEAP_H
#define MINHEAP_H


class MinHeap
{
    public:
        struct idWeightResult
        {
            int id;
            int weight;
        };
        typedef struct idWeightResult idWeightResult;

        MinHeap();
        MinHeap(int* array, int* indexArray ,int size);
        virtual ~MinHeap();

        bool insert(int key);
        int getMin(); // simply get the Node with the min cost
        idWeightResult popMin(); // get and delete from the heap the Node with the min cost

    protected:
        int *theMinHeap;
        int *theIndex;

        int currentSize;
        int maxSize;
    private:
        bool makeHeap(int* array, int size);

};

#endif // MINHEAP_H

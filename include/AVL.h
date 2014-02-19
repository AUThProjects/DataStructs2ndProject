#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "../include/treeNode.h"

using namespace std;

class AVL
{
    private:
    public:
        // struct for showing the intersecting nodes between two AVL trees.
        struct resultOfIntesection
        {
            int* commonNodes;
            int sizeOfArray;
        };
        typedef struct resultOfIntesection resultOfIntesection;

        AVL(); //ctor
        virtual ~AVL(); //dtor

        //operator overloads
        friend ostream& operator<< (ostream& myStream, AVL& obj);

        // called from outside
        void insertTreeNode(int idOfConnectedNode, int weight); // inserts a new treeNode to the AVL. If existent, does nothing.
        void deleteTreeNode(int idOfConnectedNode); // deletes a treeNode from the AVL. If non existent, does nothing.
        void printTree(treeNode* root, ostream& myStream); // prints inOrder
        //void print(); needed when printing without operator overload

        // accessors
        int getNumberOfLeaves();
        treeNode* getHead();
        treeNode** getInOrder(treeNode *root);


        resultOfIntesection intersectWithAVL(AVL* avlForIntersection);
    protected:
    private:
        // member variables
        treeNode* head;
        int numberOfLeaves;
        // called from inside the class, for recursion
        treeNode* insertTreeNode(int idOfConnectedNode,int weight, treeNode* root);
        treeNode* deleteTreeNode(int idOfConnectedNode, treeNode * root);


        static int calculateBf(treeNode* node); // returns the bf of a specific node
        //bool findTreeNode(int value); not implemented

        //Rotations
        /* the parameter is the first node that has problem with the bf*/
        static treeNode* rotateLL(treeNode* node); // Makes a LL rotation
        static treeNode* rotateRR(treeNode* node); // Makes a RR rotation
        static treeNode* rotateLR(treeNode* node); // Makes a LR rotation
        static treeNode* rotateRL(treeNode* node); // Makes a RL rotation
        static treeNode* fixTree(treeNode* node); // called for fixing the tree, when inserting nodes

        void reallocateArray(int** theArray, int* currentSize); // used to allocate more space to the array of intersecting nodes
        void  getInOrderRecursive(treeNode* root, treeNode** inOrderArray, int* counter);
};

#endif // AVL_H

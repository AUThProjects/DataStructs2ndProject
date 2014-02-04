#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "../include/treeNode.h"

using namespace std;

class AVL
{
    private:
        //implemented with class, not struct
        /*
        struct treeNode
        {
            treeNode* leftChild;
            treeNode* rightChild;
            int value;
            int height=0;
        };
        typedef struct treeNode treeNode;
        */
    public:
        AVL(); //ctor
        virtual ~AVL(); //dtor
        //operator overloads
        friend ostream& operator<< (ostream& myStream, AVL& obj);

        int getNumberOfLeaves(); // accessor, retuns numberOfLeaves
        // called from outside
        void insertTreeNode(int idOfConnectedNode, int weight); // inserts a new treeNode to the AVL. If existent, does nothing.
        void deleteTreeNode(int idOfConnectedNode); // deletes a treeNode from the AVL. If non existent, does nothing.
        //bool hasConnectedNode(int idOfConnectedNode); // not implemented
        void printTree(treeNode* root, ostream& myStream); // prints inOrder
        //void print(); needed when printing without operator overload
    protected:
    private:
        // member variables
        treeNode* head;
        int numberOfLeaves;
        // called from inside tha class, for recursion
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
};

#endif // AVL_H

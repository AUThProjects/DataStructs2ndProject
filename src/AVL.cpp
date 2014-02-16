#include "../include/AVL.h"
#include "../include/treeNode.h"
#include "../include/simpleHashTable.h"
#include <iostream>
#include <cmath>

#define INITIAL_SIZE_OF_CN 100
using namespace std;
AVL::AVL()
{
    head = nullptr; // the head points to nullptr, when there is no head
    numberOfLeaves = 0; // default value for empty tree
}

AVL::~AVL()
{
    delete(head); // deallocates the head, when the AVL is destroyed
}

int AVL::getNumberOfLeaves()
{
    return this->numberOfLeaves;
}

/*
void AVL::print()
{
    cout << "the root is: " << head->getValue() << endl;
    printTree(head);
}*/

void AVL::printTree(treeNode* root, ostream& myStream)
{
    //------------------For Debugging -------------------------
    // shows the whole AVL
    /*
    if (root!=nullptr)
    {
        printTree(root->getLeft(), myStream);
        myStream <<root->getValue();
        if (root->getRight()==nullptr)
            myStream << " rightChild= " << "nullptr ";
        else
            myStream << " rightChild= " << root->getRight()->getValue();
        if (root->getLeft()==nullptr)
            myStream << " leftChild= " << "nullptr ";
        else
            myStream << " leftChild=" << root->getLeft()->getValue();
        cout << " height = " << root->getHeight();
        myStream << endl;
        printTree(root->getRight(), myStream);
    }
    */
    //------------------------------------------------------------
    // if root is null, it prints nothing, as the tree is empty
    if(root!= nullptr)
    {
        printTree(root->getLeft(), myStream);
        myStream <<", " << root->getValue() << '(' << root->getWeight() << ')';
        printTree(root->getRight(), myStream);
    }

}

void AVL::insertTreeNode(int idOfConnectedNode, int weight)
{
    head =  insertTreeNode(idOfConnectedNode, weight, head); // calls the recursive private overloaded method with the head(root) of the tree
}

treeNode* AVL::insertTreeNode(int idOfConnectedNode, int weight, treeNode* root)
{
    if(root == nullptr)
    {
        treeNode* newNode = new treeNode(idOfConnectedNode, weight); // if nullptr, create a new node and add the value
        numberOfLeaves++; // increment the numberOfLeaves by 1
        return newNode; //return the new node (for recursion)
    }
    else
    {
        if(idOfConnectedNode < root->getValue()) // (recursion) on the left
        {
            root->setLeft(insertTreeNode(idOfConnectedNode, weight, root->getLeft()));
            return fixTree(root);
        }
        else if (idOfConnectedNode > root->getValue()) // (recursion) on the right
        {
            root->setRight(insertTreeNode(idOfConnectedNode, weight, root->getRight()));
            return fixTree(root);
        }
        else
        {
            return root; // the id exists
        }
    }
}

void AVL::deleteTreeNode(int idOfConnectedNode)
{
    head = deleteTreeNode(idOfConnectedNode, head); // calls the recursive private overloaded method with the head(root) of the tree
}

treeNode * AVL::deleteTreeNode(int idOfConnectedNode, treeNode * root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (idOfConnectedNode < root->getValue())
        {
            root->setLeft(deleteTreeNode(idOfConnectedNode, root->getLeft())); // recursive call on the left node
        }
        else if (idOfConnectedNode > root->getValue())
        {
            root->setRight(deleteTreeNode(idOfConnectedNode, root->getRight())); // recursive call on the right node
        }
        else // if equals
        {
            treeNode * tempLeft = root->getLeft();
            treeNode * tempRight = root->getRight();
            /*//-----------------------checks for debugging----------------------------
            cout << "trying to delete: " << root->getValue() << endl;
            if (tempRight==nullptr)
                cout << "tempRight=" << "nullptr" <<endl;
            else
                cout << "tempRight=" << tempRight->getValue() << endl;
            if (tempLeft==nullptr)
                cout << "tempLeft=" << "nullptr" <<endl;
            else
                cout << "tempLeft=" << tempLeft->getValue() << endl;
            //---------------------endofchecks------------------------------------------*/

            if (tempLeft == nullptr && tempRight == nullptr) // when it has no children, just delete
            {
                delete(root);
                root = nullptr;
                numberOfLeaves--;
            }
            // when it has one child, put it on the position of the root
            else if (tempRight == nullptr)
            {
                delete (root);
                root = tempLeft;
                numberOfLeaves--;
            }
            else if (tempLeft == nullptr)
            {
                delete(root);
                root = tempRight;
                numberOfLeaves--;
            }
            // has both childree
            else
            {
                // go to the immediate bigger number
                treeNode * successor = tempRight; //definitely not nullptr, caught above

                while(successor->getLeft() != nullptr)
                {
                    successor = successor->getLeft();
                }
                int tempInt = successor->getValue();
                root->setValue(tempInt); // copy the immediate bigger value to the value of the root
                root->setRight(deleteTreeNode(tempInt, tempRight)); // delete the reduntant value from the tree
            }
        }
        if (root!=nullptr) // if the root has changed as is not null. For fixing purposes
        {
            root->fixHeight(); // fix the root's height
            int checkingBalance = calculateBf(root); // calculate the bf of the root

            // fixing with rotations, when needed
            if (checkingBalance == 2 && calculateBf(root->getLeft())>=0)
            {
                return rotateLL(root);
            }
            if (checkingBalance == 2 && calculateBf(root->getLeft())<0)
            {
                return  rotateLR(root);
            }
            if (checkingBalance == -2 && calculateBf(root->getRight())<=0)
            {
                return rotateRR(root);
            }
            if (checkingBalance == -2 && calculateBf(root->getRight())>0)
            {
                return rotateRL(root);
            }
        }
        // returns the root, if not returned
        return root;

    }
}

treeNode* AVL::rotateLL(treeNode* node)
{
    // node is the first node with problem (bf==abs(2)) for the first time
    treeNode* temp;
    temp = node->getLeft();
    node->setLeft(temp->getRight());
    temp->setRight(node);
    return temp;

}

treeNode * AVL::rotateRR(treeNode* node)
{
    // node is the first node with problem (bf==abs(2)) for the first time
    treeNode* temp;
    temp = node->getRight();
    node->setRight((node->getRight())->getLeft());
    temp->setLeft(node);
    return temp;
}

treeNode * AVL::rotateLR(treeNode* node)
{
    // node is the first node with problem (bf==abs(2)) for the first time
    node->setLeft(rotateRR(node->getLeft()));
    return rotateLL(node);
}

treeNode * AVL::rotateRL(treeNode* node)
{
    // node is the first node with problem (bf==abs(2)) for the first time
    node->setRight(rotateLL(node->getRight()));
    return rotateRR(node);
}

int AVL::calculateBf(treeNode* node)
{
    // given by the height of left node-height of right node
    if (node->getLeft() == nullptr && node->getRight() == nullptr)
    {
        return 0;
    }
    else
    {
        if (node->getLeft() == nullptr)
        {
            return 0-(node->getRight())->getHeight();
        }
        else if (node->getRight() == nullptr)
        {
            return (node->getLeft())->getHeight();
        }
        else
        {
            return (node->getLeft())->getHeight() - (node->getRight())->getHeight();
        }
    }

}


treeNode* AVL::fixTree(treeNode* node)
{
    int bf = calculateBf(node);
    if(node == nullptr)
    {
        return node;
    }
    if(abs(bf) < 2)
    {
        return node;
    }
    else if (bf == 2)
    {
        if(calculateBf(node->getLeft()) >0 )
        {
            node = rotateLL(node);
        }
        else
        {
            node = rotateLR(node);
        }
    }
    else if (bf == -2)
    {
        if(calculateBf(node->getRight()) <0)
        {
            node = rotateRR(node);
        }
        else
        {
            node = rotateRL(node);
        }
    }
    return node;
}

void AVL::getInOrderRecursive(treeNode* root, treeNode* inOrderArray[], int* counter)
{
    if (root==nullptr)
        return;
    else
    {
        getInOrderRecursive(root->getLeft(), inOrderArray, counter);
        inOrderArray[*(counter)++] = root;
        getInOrderRecursive(root->getRight(), inOrderArray, counter);
    }
}

treeNode** AVL::getInOrder(treeNode* root) //
{
    treeNode* inOrderArray[this->numberOfLeaves];
    int counter = 0;
    getInOrderRecursive(this->head, inOrderArray, &counter);

    return inOrderArray;
}

treeNode* AVL::getHead()
{
    return this->head;
}

AVL::resultOfIntesection AVL::intersectWithAVL(AVL* avlForIntersection)
{
    AVL* biggestAVL = this;
    int max_size = this->numberOfLeaves;
    AVL* smallestAVL = avlForIntersection;
    int min_size = avlForIntersection->numberOfLeaves;
    // take the biggest avl
    if (max_size < min_size)
    {
        smallestAVL = biggestAVL;
        biggestAVL = avlForIntersection;
        min_size = max_size;
        max_size = biggestAVL->numberOfLeaves;

    }
    simpleHashTable *sht = new simpleHashTable(2*max_size);
    treeNode** arrayOfInorder;
    arrayOfInorder = biggestAVL->getInOrder(biggestAVL->head);


    for (int i=0;i<max_size;i++)
    {
        sht->addElement(arrayOfInorder[i]->getValue());
    }

    arrayOfInorder = smallestAVL->getInOrder(smallestAVL->head);

    int * arrayOfCommonNeighbours = new int[INITIAL_SIZE_OF_CN];
    int counter = 0;
    int maxSizeOfCN = INITIAL_SIZE_OF_CN;
    for (int i=0;i<min_size;i++)
    {
        if (counter>=maxSizeOfCN)
        {
            reallocateArray(&arrayOfCommonNeighbours, &maxSizeOfCN);
        }
        if (sht->exists(arrayOfInorder[i]->getValue()))
        {
            arrayOfCommonNeighbours[counter++] = arrayOfInorder[i]->getValue();
        }
    }

    resultOfIntesection theResult;
    theResult.commonNodes = arrayOfCommonNeighbours;
    theResult.sizeOfArray = counter;
    return theResult;
}

void AVL::reallocateArray(int **theArray, int* currentSize)
{
    int *newArray = new int[*currentSize*2];
    for(int i=0;i<*currentSize;i++)
    {
        newArray[i] = *theArray[i];
    }
    delete *theArray;
    *theArray = newArray;
    *currentSize *= 2;
}

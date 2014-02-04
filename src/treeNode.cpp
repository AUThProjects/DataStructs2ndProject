#include "../include/treeNode.h"
#include <cmath>
#include <iostream>

using namespace std;
treeNode::treeNode()
{
    value = -1; // defaults to -1
    height = 1; // defaults to 1
    weight = -1;
    leftChild = nullptr;
    rightChild = nullptr;
}

treeNode::treeNode(int value) : treeNode()
{
    this->value = value;
}

treeNode::treeNode(int value, int weight) : treeNode(value)
{
    this->weight = weight;
}

treeNode::~treeNode()
{
    // definitely not needed. If deleting a node, the tree beneath should not be deleted.
    /*
    delete(leftChild);
    delete(rightChild);
    */
}

int treeNode::getWeight()
{
    return this->weight;
}

int treeNode::getHeight()
{
    return height;
}
int treeNode::getValue()
{
    return value;
}
treeNode* treeNode::getLeft()
{
    return leftChild;
}
treeNode* treeNode::getRight()
{
    return rightChild;
}

void treeNode::setLeft(treeNode* left)
{
    this->leftChild = left;
    fixHeight(); // when setting a new treeNode as left, you have to fix the node's height
}
void treeNode::setRight(treeNode* right)
{
    this->rightChild = right;
    fixHeight(); // when setting a new treeNode as right, you have to fix the node's height
}
void treeNode::setValue(int idOfConnectedNode)
{
    value = idOfConnectedNode;
}

void treeNode::fixHeight()
{
    if (this->leftChild == nullptr && this->rightChild== nullptr)
    {
        this->height = 1; // the default height, if it has no child nodes
    }
    else
    {
        // if it has one child, then the height is the height of the child +1
        if (this->leftChild == nullptr)
        {
            this->height = (this->rightChild->height) + 1;
        }
        else if (this->rightChild == nullptr)
        {
            this->height = (this->leftChild)->height + 1;
        }
        else
        {
            // if it has both childs, the height is the max of children's heigths +1
            this->height = ((this->leftChild)->getHeight()>(this->rightChild)->getHeight()) ? this->leftChild->getHeight() +1 : (this->rightChild)->getHeight()+1;
        }
    }
}

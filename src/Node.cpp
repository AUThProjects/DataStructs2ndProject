/*

C/C++ File
Anagnostou Antonis

Comments:


*/
#include "../include/Node.h"


Node::Node()
{
    //ctor
    this->id = -1;
    this->avlTree = new AVL();
    this->numberOfConnectedNodes = 0; // in case of check, check the id as well.
}

Node::Node(int id)
{
    this->id = id;
    this->avlTree = new AVL();
    this->numberOfConnectedNodes = 0;
}

Node::Node(int id, AVL* avlTree)
{
    this->id = id;
    this->avlTree = avlTree;
    this->numberOfConnectedNodes = avlTree->getNumberOfLeaves();
}


Node::~Node()
{
    delete (avlTree);
}


bool Node::addNewNode(int idOfNewNode, int weight)
{
    int previousSize = numberOfConnectedNodes;
    this->avlTree->insertTreeNode(idOfNewNode, weight);
    numberOfConnectedNodes = avlTree->getNumberOfLeaves();
    if (previousSize == numberOfConnectedNodes)
    {
        return false;
    }
    else return true;
}

bool Node::deleteNode(int idOfExistingNode)
{
    int previousSize = numberOfConnectedNodes;
    this->avlTree->deleteTreeNode(idOfExistingNode);
    numberOfConnectedNodes = avlTree->getNumberOfLeaves();
    if (previousSize == numberOfConnectedNodes)
    {
        return false;
    }
    else return true;
}

int Node::getID()
{
    return id;
}

int Node::getNumberOfConnectedNodes()
{
    return numberOfConnectedNodes;
}

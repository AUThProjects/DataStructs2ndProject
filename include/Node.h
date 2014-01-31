#ifndef NODE_H
#define NODE_H
#include "../include/AVL.h"

class Node
{
    public:
        // ctors
        Node();
        Node(int id);
        Node(int id, AVL* avlTree); // get number of leaves and put it in numberofconnectednodes
        // dtor
        virtual ~Node();
        // operator overload
        friend ostream& operator<< (ostream& myStream, Node& obj);

        int getID(); // accessor for id
        int getNumberOfConnectedNodes(); // accessor for numberOfConnectedNode, needed for the output file

        bool addNewNode(int idOfNewNode); // adds a new node. If existent, returns false
        bool deleteNode(int idOfExistingNode); // deletes a node. If not existent, returns false
    protected:
    private:
        int id; // the id of the node
        int numberOfConnectedNodes; // defaults to -1
        AVL* avlTree; // the avl tree where the connected nodes of this node are saved

};

#endif // NODE_H

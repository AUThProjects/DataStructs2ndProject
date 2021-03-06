#ifndef TREENODE_H
#define TREENODE_H


class treeNode
{
    public:
        // ctors
        treeNode();
        treeNode(int value);
        treeNode(int value, int weight);
        // dtor
        virtual ~treeNode();
        // accessors
        int getHeight();
        int getValue();
        int getWeight();
        treeNode* getLeft();
        treeNode* getRight();
        // mutators
        void setLeft(treeNode* left);
        void setRight(treeNode* right);
        void setValue(int idOfConnectedNode);
        // public methods
        void fixHeight(); // fixes the height of the treeNode, if needed
    protected:
    private:
        treeNode* leftChild; // pointer to left node
        treeNode* rightChild; // pointer to right node
        int weight; // the weight with with the current treeNode is linked to the Node connected.
        int value; // the value of the node
        int height; // the height of the node.
};

#endif // TREENODE_H

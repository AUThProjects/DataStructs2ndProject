/*
 * Data Structures project 1
 *
 * Created by:
 *      Laskaridis Stefanos 2315
 *      Anagnostou Antonis 2268
 *
 * used gcc C++ 11 compiler
 *      and CodeBlocks 12.11 IDE
 *      on Windows 8 Pro x64
 *      without optimization flags
 */

#include <iostream>
#include <cstdlib>
#include <climits>
#include "include/AVL.h"
#include "include/Database.h"
#include "include/IO.h"
#include "include/SimpleHashTable.h"
#include "include/MinHeap.h"


using namespace std;

int main()
{
    /*
    cout << "Hello world!" << endl;
    AVL myAVL;
    srand(5);
    for (int i =0; i< 10; i++)
    {
        cout << i+1 << endl;
        int n = rand()%50;
        cout << n << endl;
        myAVL.insertTreeNode(n);
        cout << endl;
        cout << endl;
    }

    cout << myAVL << endl;
    cout << "-------------" << endl;

    cout << myAVL.getNumberOfLeaves()<<endl;

    cout << endl;
    cout << "deleting 49" << endl;
    myAVL.deleteTreeNode(49);
    cout << myAVL.getNumberOfLeaves() <<endl;
    cout << myAVL << endl;
    cout << endl;
    cout << "deleting 27" << endl;
    myAVL.deleteTreeNode(27);
    cout << endl;
    cout << myAVL.getNumberOfLeaves() <<endl;
    cout << endl;
    cout << myAVL << endl;
    cout << "deleting 5" << endl;
    myAVL.deleteTreeNode(5);
    cout << myAVL.getNumberOfLeaves() <<endl;
    cout << myAVL << endl;
    cout << endl;
    cout << "deleting 10" << endl;
    myAVL.deleteTreeNode(10);
    cout << myAVL.getNumberOfLeaves() <<endl;
    cout << myAVL << endl;
    cout << endl;
    cout << "deleting 49" << endl;
    myAVL.deleteTreeNode(49);

    cout << myAVL.getNumberOfLeaves()<<endl;
    cout << myAVL << endl;
    cout << "deleting 30" << endl;
    myAVL.deleteTreeNode(30);
    cout << myAVL << endl;

    cout << myAVL;
*/

    cout << "Program started" << endl;
    Database* myDB = new Database();
    cout<< *myDB << endl;
    cout << "Reading commands " <<endl;
   // myDB->insertNewLink(1,5, 7);

    myDB->insertNewLink(2,3,3);
    myDB->insertNewLink(2,5,1);
    myDB->insertNewLink(2,1,100);
    myDB->insertNewLink(1,5,10);
    myDB->insertNewLink(5,4,2);
    myDB->insertNewLink(4,6,1);
    myDB->insertNewLink(2,6,10);
    myDB->insertNewLink(4,3,5);
    myDB->insertNewLink(3,6,10);
    myDB->insertNewLink(6,8,2);
    myDB->insertNewLink(6,7,1);
    myDB->insertNewLink(7,8,1);
    cout << *myDB << endl;
    ComplexHashTable* dijkstra = myDB->shortestPath_Dijkstra(3);

    dijkstra->print();
/*
    IO *myIO = new IO();
    if (!myIO->readCommands("commands.txt", myDB))
    {
        cout << "Error while loading file." << endl;
        return -1;
    }
    cout << "Program ended successfully" << endl;
    //cout << *myDB << endl;
*/
    return 0;
}

ostream& operator<< (ostream& myStream, AVL& obj)
{
    //cout << "\ninside <<operator avl" << endl;
    obj.printTree(obj.head, myStream);
    return myStream;
}

ostream& operator<< (ostream& myStream, Node& obj)
{
    //cout << "\ninside <<operator Node" << endl;
    myStream<< obj.id << ", " << obj.numberOfConnectedNodes << ", " << *obj.avlTree;
    return myStream;
}

ostream& operator<< (ostream& myStream, Database& obj)
{
    //cout << "\nInside <<operator Database" << endl;
    //system("pause");
    //cout << "size of database" << obj.sizeOfDatabase << endl;
    for(int i=0; i<obj.capacity; i++)
    {
        if(obj.theDatabase[i]!=nullptr)
            myStream<< i << " - " << *(obj.theDatabase[i]) <<endl ;

        //system("pause");
    }
    return myStream;
}

istream& operator>> (istream& myStream, Database& obj)
{
    while(!myStream.eof())
    {
        int leftParameter;
        int rightParameter;
        int weightParameter;
        myStream >> leftParameter;
        myStream >> rightParameter;
        myStream >> weightParameter;
        //cout << leftParameter << " " << rightParameter << " " << weightParameter << " " << endl;
        obj.insertNewLink(leftParameter, rightParameter, weightParameter);
    }
}

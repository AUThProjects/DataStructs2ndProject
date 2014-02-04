#include "../include/IO.h"
#include <fstream>
#include <cstdlib>
#include <cstring>
#define MAX_AMOUNT_OF_PARAMS 3



using namespace std;

IO::IO()
{
    //ctor
}

IO::~IO()
{
    //dtor
}

bool IO::readCommands(char *filename, Database *myDB)
{
    ifstream myStream;
    myStream.open(filename, ios_base::in);

    if (myStream) // if found
    {
        char myString[MAX_INPUT_SIZE_PER_LINE];
        while(!myStream.eof())
        {
            myStream.getline(myString, MAX_INPUT_SIZE_PER_LINE); // reads a line from the file
            command currentCommand = parseLine(myString); // parses the line read
            //------------------Debugging purposes-----------------
            cout << currentCommand.commandName << endl;
            for (int i=0;i<currentCommand.argc;i++)
            {
                cout << currentCommand.argv[i] << endl;
            }
            //-----------------------------------------------------
            if (strcmp("READ_DATA", currentCommand.commandName)==0) // read from input file
            {
                this->readInput(currentCommand.argv[0], myDB);
            }
            else if (strcmp("WRITE_INDEX", currentCommand.commandName)==0) // write to output file
            {
                this->writeIndex(currentCommand.argv[0], myDB);
            }
            else if (strcmp("INSERT_LINK", currentCommand.commandName)==0) // insert new link
            {
                myDB->insertNewLink(atoi(currentCommand.argv[0]), atoi(currentCommand.argv[1]), atoi(currentCommand.argv[2]));
            }
            else if (strcmp("DELETE_LINK", currentCommand.commandName)==0) // delete existing link
            {
                myDB->deleteExistingLink(atoi(currentCommand.argv[0]), atoi(currentCommand.argv[1]));
            }
            else // command not recognized
            {
                cout << "unknown command" << endl;
            }
        }
        myStream.close();
        return true;
    }
    else // if not found
    {
        cout << "Error while loading file: commands.txt" << endl;
        return false;
    }
}

// we assume that the inputCommands file has one ' ' as delimeter and no extra spaces are used in the input file
IO::command IO::parseLine(char input[])
{
    int numberOfSpaces = 0; // the number of spaces used as delimeters == the number of arguments
    int positionOfSpaces[MAX_AMOUNT_OF_PARAMS]; // saves the position of ' ' inside the input
    // temp values initialization
    int pos = 0;
    char temp = input[0];
    while(temp!='\0' && numberOfSpaces!=MAX_AMOUNT_OF_PARAMS) // read the whole input, until the max amount of params is read
    {
        if (temp == ' ')
        {
            positionOfSpaces[numberOfSpaces] = pos;
            numberOfSpaces++;
            input[pos] = '\0'; // divide the input string in substrings
        }
        pos++;
        temp = input[pos];
    }
    command toBeReturned;
    toBeReturned.commandName = new char[MAX_INPUT_SIZE_PER_LINE];
    strcpy(toBeReturned.commandName, input);
    toBeReturned.argc = numberOfSpaces;

    for(int i=0;i<toBeReturned.argc;i++)
    {
        toBeReturned.argv[i] = new char[MAX_INPUT_SIZE_PER_LINE];
        strcpy(toBeReturned.argv[i], input+positionOfSpaces[i]+1);
    }
    return toBeReturned;
}

bool IO::readInput(char *filename, Database *myDB)
{
    ifstream myStream;
    myStream.open(filename, ios_base::in);
    if (myStream) //file found
    {
        myStream >> *myDB;
        myStream.close();
        return true;
    }
    else // file not found
    {
        cout << "Error while loading " << filename << endl;
        return false;
    }
}

bool IO::writeIndex(char *filename, Database *myDB)
{
    ofstream myStream;
    myStream.open(filename, ios_base::out);
    if (myStream) // file found
    {
        myStream << *myDB;
        myStream.close();
        return true;
    }
    else // file not found
    {
        cout << "Error while loading " << filename << endl;
        return false;
    }

}

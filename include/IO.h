#ifndef IO_H
#define IO_H
#include "Database.h"
#define MAX_INPUT_SIZE_PER_LINE 50

class IO
{
    private:
        struct command // used internally for parsing commands
            {
                char* commandName; // the command's name
                int argc; // number of arguments (max 2)
                char* argv[3]; // aguments
            };
        typedef struct command command;
        command parseLine(char input[]); // parses a line from the commands file
    public:
        // ctor
        IO();
        // dtor
        virtual ~IO();
        // methods used when reading from files
        bool readCommands(char * filename, Database * db); // reads/parses the commands file
        bool readInput(char * filename, Database * db); //reads/parses the input file
        bool writeIndex(char * filename, Database * db); // writes the output file
        bool writeCN(char* filename, int numberOfCommonNeighbours);
    protected:
};

#endif // IO_H

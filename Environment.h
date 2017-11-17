#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Files.h"
#include "Commands.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Environment {
private:
    vector<BaseCommand*> commandsHistory;
    FileSystem fs;
    //rule of 5 methods
    void clean() ;
    void steal(Environment &rhs);
    void copy(const Environment &rhs);

public:
    Environment();
    void start();
    FileSystem& getFileSystem() ; // Get a reference to the file system
    void addToHistory(BaseCommand *command); // Add a new command to the history
    const vector<BaseCommand*>& getHistory() const; // Return a reference to the history of commands
    void createCommand(vector<string> inputStrings) ;
    //rule of 5 methods
    Environment &operator=(const Environment  &rhs);
    Environment &operator=(Environment &&rhs);
    Environment(const Environment &rhs);
    virtual ~Environment();
    Environment(Environment &&rhs);
};

#endif
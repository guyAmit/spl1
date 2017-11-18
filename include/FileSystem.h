#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Files.h"
#include "GlobalVariables.h"


class FileSystem {
private:
    Directory* rootDirectory;
    Directory* workingDirectory;

    //rule of 5 methods
    void clean()  ;
    void steal(FileSystem &rhs);
    void copy(const FileSystem &rhs);

public:
    FileSystem();
    Directory& getRootDirectory() const; // Return reference to the root directory
    Directory& getWorkingDirectory() const; // Return reference to the working directory
    void setWorkingDirectory(Directory *newWorkingDirectory); // Change the working directory of the file system

    //rule of 5 methods
    FileSystem &operator=(const FileSystem  &rhs);
    FileSystem &operator=(FileSystem &&rhs);
    FileSystem(const FileSystem &rhs);
    virtual ~FileSystem();
    FileSystem(FileSystem &&rhs);

};


#endif

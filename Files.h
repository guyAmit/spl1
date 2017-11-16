#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class BaseFile {
private:
    string name;

/**
 *
 * @param name
 * @return true iff name contains digits or letters only.
 */
    bool baseFile_Valid_Name(const string &name);

public:
    BaseFile(string name); //todo:: create test for file name
    string getName() const;

    void setName(string newName);
    /**
     *
     * @return true if the type is directory and false if type is file.
     */
    virtual bool getType()=0;
    virtual int getSize() = 0;
    virtual ~BaseFile()=0;


};

class File : public BaseFile {
private:
    int size;

public:
    File(string name, int size); // Constructor
    //todo:: create positive test for size
    int getSize(); // Return the size of the file
    bool getType();
    virtual ~File();

};

class Directory : public BaseFile {
private:
    vector<BaseFile *> children; //this is a list of both files and folders
    Directory *parent;

    void clean() const;

    void copy(const Directory &rhs);

    void steal(Directory &rhs);

public:


    Directory(string name, Directory *parent); // Constructor
    //todo:: null test for parent
    Directory *getParent() const; // Return a pointer to the parent of this directory

    void setParent(Directory *newParent); // Change the parent of this directory

    //todo:: null check parent
    void addFile(BaseFile *file); // Add the file to children
    //todo:: create add\delete tests
    void removeFile(string name); // Remove the file with the specified name from children
    void removeFile(BaseFile *file); // Remove the file from children


    //todo:: import a generic sort algortim
    void sortByName(); // Sort children by name alphabetically (not recursively)


    void sortBySize(); // Sort children by size (not recursively)
    vector<BaseFile *> getChildren(); // Return children

    int getSize(); // Return the size of the directory (recursively)
    string getAbsolutePath();//Return the path from the root to this(recursively)
    virtual ~Directory();
    Directory(const Directory &rhs);//copy constructor

    Directory &operator=(const Directory &rhs);
    Directory(Directory &&rhs);//move constructor

    Directory &operator=(Directory &&rhs);
    bool getType();
/**
 *
 * @param name of file
 * @return iterator to the file with the same name as the given file
 */
    vector<BaseFile *>::iterator searchFileName(string name);

    BaseFile *getBaseFileByName(string name);

    void eraseByName(string name);
};

#endif
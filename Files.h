#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector

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

    virtual int getSize() = 0;


};

class File : public BaseFile {
private:
    int size;

public:
    File(string name, int size); // Constructor
    //todo:: create positive test for size
    int getSize(); // Return the size of the file

};

class Directory : public BaseFile {
private:
    vector<BaseFile *> children; //this is a list of both files and folders
    Directory *parent;

/**
 *
 * @param file
 * @return true iff there is no file with the same name as the given file
 */
    bool searchFileName(BaseFile *file);
    /**
     * delete all the pointers in children
     */
    void clean() const;
    /**
     * deep copies this children vector into new vector.
     * @return a pointer to the new vector
     */
    vector<BaseFile*> copy()const;

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


    Directory &operator=(const Directory &rhs);
};

#endif
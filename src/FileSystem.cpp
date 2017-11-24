//
// Created by Guy-Amit on 11/8/2017.
//

#include "FileSystem.h"
#include "string"
#include"Commands.h"

using namespace std;

FileSystem::FileSystem():rootDirectory(new Directory("/", nullptr)),workingDirectory(rootDirectory) {
}

Directory& FileSystem::getRootDirectory() const {
    return *rootDirectory;
}

Directory& FileSystem::getWorkingDirectory() const {
    return *workingDirectory;
}

void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory) {
    if(newWorkingDirectory) {
        this->workingDirectory = newWorkingDirectory;
    }
    else{throw std::exception();}
}

/************************************************
implemention of rule of 5
 there should be only one file system.
*************************************************/

void FileSystem::clean()  {
    delete this->rootDirectory;
    this->workingDirectory = nullptr;
}

void FileSystem::copy(const FileSystem &rhs) {
    string path=rhs.workingDirectory->getAbsolutePath();
    this->rootDirectory=new Directory(*rhs.rootDirectory);
    CdCommand::cd(path,rootDirectory,*this);

}

void FileSystem::steal(FileSystem &rhs) {
    this->rootDirectory=rhs.rootDirectory;
    this->workingDirectory=rhs.workingDirectory;
    rhs.workingDirectory= nullptr;
    rhs.rootDirectory= nullptr;
}

FileSystem::FileSystem(const FileSystem &rhs):rootDirectory(nullptr),workingDirectory(nullptr) {
    if(verbose==1 ||verbose==3){
        cout << "FileSystem::FileSystem(const FileSystem &rhs)" << endl;
    }
    copy(rhs);
}

FileSystem::FileSystem(FileSystem &&rhs) :rootDirectory(nullptr),workingDirectory(nullptr){
    if(verbose==1 ||verbose==3){
        cout << "FileSystem::FileSystem(FileSystem &&rhs)" << endl;
    }
    steal(rhs);
}
FileSystem::~FileSystem() {
    if(verbose==1 ||verbose==3){
        cout << "FileSystem::~FileSystem()" << endl;
    }
    clean();
}

FileSystem& FileSystem::operator=(FileSystem &&rhs) {
    if(verbose==1 ||verbose==3){
        cout << "FileSystem& FileSystem::operator=(FileSystem &&rhs)" << endl;
    }
    clean();
    steal(rhs);
    return *this;
}

FileSystem& FileSystem::operator=(const FileSystem &rhs) {
    if(verbose==1 ||verbose==3){
        cout << "FileSystem& FileSystem::operator=(const FileSystem &rhs)" << endl;
    }
    if(this != &rhs){
        clean();
        copy(rhs);
    }
    return *this;
}



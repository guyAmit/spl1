//
// Created by Guy-Amit on 11/8/2017.
//

#include "FileSystem.h"
#include "string"

using namespace std;

FileSystem::FileSystem() {
    this->rootDirectory=new Directory("/", nullptr);
    this->workingDirectory=rootDirectory;
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

void FileSystem::clean() const {
    delete this->rootDirectory;
}

void FileSystem::copy(const FileSystem &rhs) {
    this->rootDirectory=rhs.rootDirectory;
    this->workingDirectory=rhs.workingDirectory;

}

void FileSystem::steal(FileSystem &rhs) {
    this->rootDirectory=rhs.rootDirectory;
    this->workingDirectory=rhs.workingDirectory;
    rhs.workingDirectory= nullptr;
    rhs.rootDirectory= nullptr;
}

FileSystem::FileSystem(const FileSystem &rhs) {
    if(verbose==1 ||verbose==3){
        cout << "FileSystem::FileSystem(const FileSystem &rhs)" << endl;
    }
    copy(rhs);
}

FileSystem::FileSystem(FileSystem &&rhs) {
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



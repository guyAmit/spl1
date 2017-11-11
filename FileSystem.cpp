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
    return this->*rootDirectory;
}

Directory& FileSystem::getWorkingDirectory() const {
    return this->*workingDirectory;
}

void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory) {
    if(!newWorkingDirectory) {
        this->workingDirectory = newWorkingDirectory;
    }
    else{throw std::exception();}
}
/************************************************
for test perpesese only::implamention of rule of 5
 there should be only one file system.
*************************************************/

void FileSystem::clean() const {
    delete this->rootDirectory;
    delete this->workingDirectory;
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
    copy(rhs);
}

FileSystem::~FileSystem() {
    clean();
}

FileSystem& FileSystem::operator=(FileSystem &&rhs) {
    clean();
    steal(rhs);
    return *this;
}

FileSystem& FileSystem::operator=(const FileSystem &rhs) {
    if(this != &rhs){
        clean();
        copy(rhs);
    }
    return *this;
}



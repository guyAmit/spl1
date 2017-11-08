//
// Created by Guy-Amit on 11/8/2017.
//

#include "Files.h"

//BaseFile class
BaseFile::BaseFile(string name) : name("default") {
    if (baseFile_Valid_Name(name))
        this->name = name;
    else {
        throw std::exception();
    }
}

string BaseFile::getName() const { return name; }

void BaseFile::setName(string newName) { name = newName; }

bool BaseFile::baseFile_Valid_Name(const string &name) {
    return (name.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
            std::string::npos);
}

//File class
File::File(string name, int size) : BaseFile(name), size(0) {
    if (size <= 0) {
        throw std::exception();
    } else {
        this->size = size;
    }
}

int File::getSize() { return size; }

//Directory class
//todo: add rule of 5 methods
Directory::Directory(string name, Directory *parent) : BaseFile(name), parent(nullptr) {
    if (parent) {
        this->parent = parent;
        this->children
//        this->children = new vector();
    } else {
        throw std::exception();
    }
}

Directory *Directory::getParent() const {
    return parent;
}

void Directory::setParent(Directory *newParent) {
    if (newParent) {
        parent = newParent;
    } else {
        throw std::exception();
    }
}

void Directory::addFile(BaseFile *file) {
    if (!file)
        throw std::exception();
    if (searchFileName(file)) {
        children.push_back(file);
    } else {
        throw std::exception();
    }

}

Directory::~Directory() {
    clean();
}


void Directory::clean() const {
    for (auto baseFile :children) {
        delete baseFile;
    }
}


bool Directory::searchFileName(BaseFile *file) {
    if (children.empty()) {
        return true;
    } else {//iterate through the vector and find a matching file name
        auto it = std::find_if(children.begin(), children.end(), [](
                const BaseFile &baseFile) -> bool { return baseFile.getName() == file->getName(); });
        return it == children.end();
    }
}

void Directory::removeFile(string name) {

}

void Directory::removeFile(BaseFile *file) {

}

void Directory::sortByName() {

}

void Directory::sortBySize() {

}

vector<BaseFile *> Directory::getChildren() {
    return vector<BaseFile *>();
}

int Directory::getSize() {
    int sumSize = 0;
    for ()
}

string Directory::getAbsolutePath() {
    if (!parent)
        return getName();
    else
        return parent->getAbsolutePath() + getName();
}

 vector<BaseFile*> Directory::copy()const {
    auto newVector = new vector();
    for (auto baseFile :children) {
        //todo: the vectors have the same baseFiles but maybe in different order by default.
        newVector->push_back(baseFile);
    }
    return newVector;
}

Directory &Directory::operator=(const Directory &rhs) {
    if (this != &rhs) {
        clean();
        this->parent = rhs.parent;
        this->children = rhs.copy();

    }
}



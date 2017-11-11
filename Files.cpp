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
    return (name!=""&& name.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
            std::string::npos);
}

//File class
File::File(string name, int size) : BaseFile(name), size(0) {
    if (size < 0) {
        throw std::exception();
    } else {
        this->size = size;
    }
}

int File::getSize() { return size; }

//Directory class
Directory::Directory(string name, Directory *parent) : BaseFile(name) {
    this->parent = parent;
    this->children;

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
    if (children.empty()||searchFileName(file->getName()) == children.end()) {
        children.push_back(file);
    } else {
        throw std::exception();
    }

}

//rule of 5
Directory::~Directory() {
    clean();
}

Directory::Directory(const Directory &rhs) : BaseFile("default") {
    copy(rhs);
}


Directory &Directory::operator=(const Directory &rhs) {
    if (this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

Directory::Directory(Directory &&rhs) : BaseFile("default") {
    steal(rhs);
}

Directory &Directory::operator=(Directory &&rhs) {
    clean();
    steal(rhs);
    return *this;
}

void Directory::steal(Directory &rhs) {
    this->parent = rhs.parent;
    this->setName(rhs.getName());
    this->children = rhs.children;
}

void Directory::copy(const Directory &rhs) {
    this->parent = rhs.parent;
    this->setName(rhs.getName());
    this->children;
    for (auto baseFile:rhs.children) {
        if (dynamic_cast<File *>(baseFile))
            children.push_back(new File(baseFile->getName(), baseFile->getSize()));
        else {
            children.push_back(new Directory(*dynamic_cast<Directory * >(baseFile)));
        }
    }

}

void Directory::clean() const {
    for (auto baseFile :children) {
        delete baseFile;
    }
}

vector<BaseFile *>::iterator Directory::searchFileName(string name) {

    //iterate through the vector and find a matching file name
    auto iterator = find_if(children.begin(), children.end(),
                           [&name](BaseFile *baseFile)->bool { return baseFile->getName() == name; });
    return iterator;

}

void Directory::removeFile(string name) {
    auto iterator =searchFileName(name);
    if(!children.empty() && (iterator != children.end())){
        delete children.at(static_cast<unsigned long>(distance(children.begin(), iterator)));
        children.erase(iterator);
    }
}

void Directory::removeFile(BaseFile *file) {
    removeFile(file->getName());

}

void Directory::sortByName() {
    std::sort(children.begin(), children.end(), []( BaseFile *baseFile1, BaseFile *baseFile2) {
        return  baseFile1->getName() < baseFile2->getName();
    });

}

void Directory::sortBySize() {
    sort(children.begin(), children.end(), [] (BaseFile *baseFile1, BaseFile *baseFile2){
        return baseFile1->getSize() < baseFile2->getSize();
    });
}

vector<BaseFile *> Directory::getChildren() {
    return this->children;
}

int Directory::getSize() {
    int sumSize = 0;
    for (auto baseFile: children) {
        sumSize = sumSize + baseFile->getSize();
    }
    return sumSize;
}

string Directory::getAbsolutePath() {
    if (!parent)
        return"";
    else
        return parent->getAbsolutePath() + "/"+getName();
}




//
// Created by Guy-Amit on 11/8/2017.
//

#include "Files.h"

//BaseFile class
BaseFile::BaseFile(string name) : name("default") {
    this->name = name;
}

string BaseFile::getName() const { return name; }

void BaseFile::setName(string newName) {
    this->name = newName;
}

bool BaseFile::baseFile_Valid_Name(const string &name) {
    return (!name.empty() && name.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
                             std::string::npos);
}
BaseFile::~BaseFile() {}
//File class
File::File(string name, int size) : BaseFile(name), size(0) {
    if (size < 0) {
        throw std::exception();
    } else {
        this->size = size;
    }
}

int File::getSize() { return size; }

bool File::getType() { return false; }

 File::~File() {
 }


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
    if (children.empty() || searchFileName(file->getName()) == children.end()) {
        children.push_back(file);
    }

}

//rule of 5
 Directory::~Directory() {
    if(verbose==1 ||verbose==3){
        cout << "Directory::~Directory()" << endl;
    }
    clean();
}

Directory::Directory(const Directory &rhs) : BaseFile("default") {
    if(verbose==1 ||verbose==3){
        cout << "Directory::Directory(const Directory &rhs)" << endl;
    }
    copy(rhs);
}


Directory &Directory::operator=(const Directory &rhs) {
    if(verbose==1 ||verbose==3){
        cout << "Directory &Directory::operator=(const Directory &rhs)" << endl;
    }
    if (this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

Directory::Directory(Directory &&rhs) : BaseFile("default") {
    if(verbose==1 ||verbose==3){
        cout << "Directory::Directory(Directory &&rhs)" << endl;
    }
    steal(rhs);
}

Directory &Directory::operator=(Directory &&rhs) {
    if(verbose==1 ||verbose==3){
        cout << "Directory &Directory::operator=(Directory &&rhs)" << endl;
    }
    clean();
    steal(rhs);
    return *this;
}

void Directory::steal(Directory &rhs) {
    this->parent = rhs.parent;
    this->setName(rhs.getName());
    this->children = rhs.children;
    rhs.children.erase(rhs.children.begin(), rhs.children.end());
}

void Directory::copy(const Directory &rhs) {
    this->setName(rhs.getName());
    this->children;
    for (auto baseFile:rhs.children) {
        if (!baseFile->getType())
            children.push_back(new File(baseFile->getName(), baseFile->getSize()));
        else {
            Directory *newDirectory = new Directory(*dynamic_cast<Directory * >(baseFile));
            newDirectory->parent = this;
            children.push_back(dynamic_cast<BaseFile*>(newDirectory));
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
                            [&name](BaseFile *baseFile) -> bool { return baseFile->getName() == name; });
    return iterator;

}

void Directory::removeFile(string name) {
    auto iterator = searchFileName(name);
    if (!children.empty() && (iterator != children.end())) {
        delete *iterator;
        children.erase(iterator);
    }
}

void Directory::removeFile(BaseFile *file) {
    removeFile(file->getName());

}

void Directory::sortByName() {
    std::sort(children.begin(), children.end(), [](BaseFile *baseFile1, BaseFile *baseFile2) {
        return baseFile1->getName() < baseFile2->getName();
    });

}

void Directory::sortBySize() {
    sortByName();
    stable_sort(children.begin(), children.end(), [](BaseFile *baseFile1, BaseFile *baseFile2) {
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
        return getName();
    else {
        if (!(parent->getParent()))
            return parent->getName() + getName();
        else
            return parent->getAbsolutePath() + "/" + getName();
    }
}

bool Directory::getType() { return true; }

BaseFile *Directory::getBaseFileByName(string name) {
    auto iterator = searchFileName(name);
    if (!children.empty() && (iterator != children.end()))
        return *iterator;
    return nullptr;
}
void Directory::eraseByName(string name){
    auto it = searchFileName(name);
    if(it != children.end())
    children.erase(it);
}




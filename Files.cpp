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
Directory::Directory(string name, Directory *parent) : BaseFile(name) {
        this->parent = parent;
        this->children = new vector();

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
    if (searchFileName(file->getName())!=children.begin()) {
        children.push_back(file);
    } else {
        throw std::exception();
    }

}
//rule of 5
Directory::~Directory() {
    clean();
}
Directory::Directory(const Directory &rhs):BaseFile("default") {
    copy(rhs);
}

Directory::Directory &operator=(const Directory &rhs);

Directory::&operator=(const Directory &rhs) {

}

void Directory::copy(const Directory &rhs ){
    this->parent = rhs.parent;
    this->setName(rhs.getName());
    this->children = new vector(rhs.children.size());
    for(auto baseFile:rhs.children) {
        children.push_back(new BaseFile(baseFile));
    }

}
void Directory::clean() const {
    for (auto baseFile :children) {
        delete baseFile;
    }
}

vector<BaseFile *>::iterator Directory::searchFileName(string name) {

    //iterate through the vector and find a matching file name
        auto it = std::find_if(children.begin(), children.end(), [](
                const BaseFile &baseFile) -> bool { return baseFile.getName() == name; });
        return it;

}

void Directory::removeFile(string name) {
    children.erase(searchFileName(name));

}

void Directory::removeFile(BaseFile *file) {
    removeFile(file->getName());

}

void Directory::sortByName() {
    std::sort(children.begin(), children.end(), [](const BaseFile &baseFile1, const BaseFile &baseFile2) -> bool {
        return baseFile1.getName() > baseFile2.getName();
    });

}

void Directory::sortBySize() {
    std::sort(children.begin(), children.end(), [](BaseFile &baseFile1, BaseFile &baseFile2) -> bool {
        return baseFile1.getSize() > baseFile2.getSize();
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
    if(!parent)
        return getName();
    else
        return parent->getAbsolutePath() + getName();
}



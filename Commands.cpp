//
// Created by Guy-Amit on 11/8/2017.
//

#include "Commands.h"

BaseCommand::BaseCommand(string args) : args(args) {}


string BaseCommand::getsplittedPath(string &path) {
    string splittedPath;
    size_t pos = 0;
    if ((pos = path.find('/')) != string::npos) {
        splittedPath = path.substr(0, pos);
        path.erase(0, pos + 1);
    } else {
        splittedPath = path;
        path = "";
    }
    return splittedPath;
}

string BaseCommand::getArgs() {
    return args;
}

BaseFile *BaseCommand::getBaseFileByPath(string &path,Directory* current,FileSystem &fs) {
    string splittedPath = getsplittedPath(path);
    if (splittedPath.empty()) {
        return getBaseFileByPath(path, &fs.getRootDirectory(), fs);
    }
    if (splittedPath == "..")
        return getBaseFileByPath(path, current->getParent(), fs);

    BaseFile *basefile = current->getBaseFileByName(splittedPath);
    if (basefile && basefile->getType()&&!path.empty())
        return getBaseFileByPath(path, dynamic_cast<Directory *>(basefile), fs);
    return basefile;
    }
}


PwdCommand::PwdCommand(string args) : BaseCommand(args) {}

void PwdCommand::execute(FileSystem &fs) {
    cout << fs.getWorkingDirectory().getAbsolutePath() << endl;
}

string PwdCommand::toString() {
    return "pwd";
}

CdCommand::CdCommand(string args) : BaseCommand(args) {

}

void CdCommand::cd(string &path, Directory *current, FileSystem &fs) {
    if (!current && !path.empty()) {
        cout << "The system cannot find the path specified" << endl;
    }
    if (path.empty()) {
        fs.setWorkingDirectory(current);
        return;
    }
    string splittedPath = getsplittedPath(path);
    if (splittedPath.empty()) {
        cd(path, &fs.getRootDirectory(), fs);
        return;
    }
    if (splittedPath == "..") {
        cd(path, current->getParent(), fs);
        return;
    }
    BaseFile *basefile = current->getBaseFileByName(splittedPath);
    if (basefile && basefile->getType()) {
        cd(path, dynamic_cast<Directory *>(basefile), fs);
    } else {
        cout << "The system cannot find the path specified" << endl;
    }

}


void CdCommand::execute(FileSystem &fs) {
    string path = getArgs();
    cd(path, &fs.getWorkingDirectory(), fs);
}

string CdCommand::toString() { return "cd"; }

LsCommand::LsCommand(string args) : BaseCommand(args) {}

void LsCommand::execute(FileSystem &fs) {
    string path = getArgs();
    if (path.substr(0, 2) == "-s") {
        path.erase(0, 2);
        ls(path, &fs.getWorkingDirectory(), fs, true);
    } else
        ls(path, &fs.getWorkingDirectory(), fs, false);
}

void LsCommand::ls(string &path, Directory *current, FileSystem &fs, bool sortType) {
    if (!current) {
        cout << "The system cannot find the path specified" << endl;
        return;
    }
    if (path.empty()) {
        if (sortType)
            current->sortBySize();
        else
            current->sortByName();
        for (auto basefile: current->getChildren())
            print(*basefile);
        return;
    }
    string splittedPath = getsplittedPath(path);
    if (splittedPath.empty()) {
        ls(path, &fs.getRootDirectory(), fs, sortType);
        return;
    }
    if (splittedPath == "..") {
        ls(path, current->getParent(), fs, sortType);
        return;
    }
    BaseFile *basefile = current->getBaseFileByName(splittedPath);
    if (basefile && basefile->getType()) {
        ls(path, dynamic_cast<Directory *>(basefile), fs, sortType);
    } else {
        cout << "The system cannot find the path specified" << endl;
    }
}

void LsCommand::print(BaseFile &pFile) {
    string type;
    if (pFile.getType())
        type = "DIR";
    else
        type = "FILE";
    cout << type << "\t" << pFile.getName() << "\t" << pFile.getSize() << endl;
}

string LsCommand::toString() {
    return "ls";
}


MkdirCommand::MkdirCommand(string args) : BaseCommand(args) {

}

void MkdirCommand::execute(FileSystem &fs) {
    string path = getArgs();
    mkdir(path, &fs.getWorkingDirectory(), fs);
}

void MkdirCommand::mkdir(string &path, Directory *current, FileSystem &fs) {
    if (!current) {
        throw std::exception();
    }
    if (path.empty()) {
        return;
    }
    string splittedPath = getsplittedPath(path);
    if (splittedPath.empty()) {
        mkdir(path, &fs.getRootDirectory(), fs);
        return;
    }
    if (splittedPath == "..") {
        mkdir(path, current->getParent(), fs);
        return;
    }
    BaseFile *basefile = current->getBaseFileByName(splittedPath);
    if (!basefile) {
        Directory *newDirectory = new Directory(splittedPath, current);
        current->addFile(newDirectory);
        mkdir(path, newDirectory, fs);
        return;
    }
    if (basefile->getType()) {
        if (!path.empty())
            mkdir(path, dynamic_cast<Directory *>(basefile), fs);
        else cout << "The directory already exists" << endl;
    }
    //todo:: check the case where the name of the the directory is a file
}

string MkdirCommand::toString() {
    return "mkdir";
}

MkfileCommand::MkfileCommand(string args) : BaseCommand(args) {
}

void MkfileCommand::execute(FileSystem &fs) {
    string args = getArgs();
    size_t pos = args.find('$');
    string path = args.substr(0, pos);
    args.erase(0, pos + 1);
    int size = std::stoi(args);
    pos = path.find_last_of('/');
    string fileName = path.substr(pos + 1, path.length() - 1);
    path.erase(pos, path.length() - 1);
    mkfile(path, &fs.getWorkingDirectory(), fs, size, fileName);
}

void MkfileCommand::mkfile(string &path, Directory *current, FileSystem &fs, int size, string &name) {
    if (path.empty()) {
        BaseFile *basefile = current->getBaseFileByName(name);
        if (!basefile) {
            current->addFile(new File(name, size));
            return;
        }
        if (!basefile->getType()) {
            cout << "File already exists" << endl;
            return;
        }
    }
    string splittedPath = getsplittedPath(path);
    if (splittedPath.empty()) {
        mkfile(path, &fs.getRootDirectory(), fs, size, name);
        return;
    }
    if (splittedPath == "..") {
        mkfile(path, current->getParent(), fs, size, name);
        return;
    }
    BaseFile *basefile = current->getBaseFileByName(splittedPath);
    if (basefile && basefile->getType()) {
        mkfile(path, dynamic_cast<Directory *>(basefile), fs, size, name);
    } else {
        cout << "The system cannot find the path specified" << endl;
    }
}

string MkfileCommand::toString() {
    return "mkfile";
}

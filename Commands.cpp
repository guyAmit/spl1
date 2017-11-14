//
// Created by Guy-Amit on 11/8/2017.
//

#include "Commands.h"

BaseCommand::BaseCommand(string args) : args(args) {}


string BaseCommand::getsplittedPath(string path) {
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

void BaseCommand::cd(string path, Directory *current, FileSystem &fs) {
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
    if(basefile&& basefile->getType()) {
        cd(path, dynamic_cast<Directory *>(basefile), fs);
    } else {
        cout << "The system cannot find the path specified" << endl;
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

void CdCommand::execute(FileSystem &fs) {
    cd(getArgs(), &fs.getWorkingDirectory(), fs);
}

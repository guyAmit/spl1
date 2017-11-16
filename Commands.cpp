//
// Created by Guy-Amit on 11/8/2017.
//

#include "Commands.h"

BaseCommand::BaseCommand(string args) : args(args) {}


pair<string, string> BaseCommand::getsplittedPath(string path) {
    string splittedPath;
    size_t pos = 0;
    if ((pos = path.find('/')) != string::npos) {
        splittedPath = path.substr(0, pos);
        path.erase(0, pos + 1);
    } else {
        splittedPath = path;
        path = "";
    }
    pair<string, string> pair1;
    pair1.first = splittedPath;
    pair1.second = path;
    return pair1;
}

string BaseCommand::getArgs() {
    return args;
}

BaseFile *BaseCommand::getBaseFileByPath(string path, Directory *current, FileSystem &fs) {
    if (!current) {
        return nullptr;
    }
    if (path.empty()) {
        return nullptr;
    }
    pair<string, string> splittedPair = getsplittedPath(path);
    string splittedPath = splittedPair.first;
    path = splittedPair.second;
    if (splittedPath.empty()) {
        return getBaseFileByPath(path, &fs.getRootDirectory(), fs);
    }
    if (splittedPath == "..")
        return getBaseFileByPath(path, current->getParent(), fs);

    BaseFile *basefile = current->getBaseFileByName(splittedPath);
    if (basefile && basefile->getType() && !path.empty())
        return getBaseFileByPath(path, dynamic_cast<Directory *>(basefile), fs);
    return basefile;
}

pair<string, string> BaseCommand::splitArgs(string args) {
    pair<string, string> pair;
    size_t pos = args.find(' ');
    string path1 = args.substr(0, pos);
    args.erase(0, pos + 1);
    string path2 = args;
    pair.first = path1;
    pair.second = path2;
    return pair;
}

pair<string, string> BaseCommand::getTwoPaths() {
    pair<string, string> pair;
    string args = getArgs();
    size_t pos = args.find(' ');
    string path1 = args.substr(0, pos);
    args.erase(0, pos + 1);
    string path2 = args;
    pair.first = path1;
    pair.second = path2;
    return pair;
}

string BaseCommand::removeLastPath(string path) {
    size_t pos = path.find_last_of('/');
    if ((pos == 0) && (pos == path.find('/'))) {
        path = "/";
    } else if (pos != string::npos) {
        path.erase(pos, path.length() - 1);
    } else {
        path = "";
    }
    return path;
}

bool BaseCommand::checkParents(BaseFile *basefile, FileSystem &fs) {
    Directory *current = &fs.getWorkingDirectory();
    if (basefile->getType()) {
        while (current != nullptr) {
            if (basefile == current)
                return false;
            current = current->getParent();
        }
    }
    return true;
}


PwdCommand::PwdCommand(string args) : BaseCommand(args) {}

void PwdCommand::execute(FileSystem &fs) {
    cout << fs.getWorkingDirectory().getAbsolutePath() << endl;
    msg = fs.getWorkingDirectory().getAbsolutePath();
}

string PwdCommand::toString() {
    return "pwd";
}

CdCommand::CdCommand(string args) : BaseCommand(args) {

}

void CdCommand::cd(string &path, Directory *current, FileSystem &fs) {
    if (!current && !path.empty()) {
        cout << "The system cannot find the path specified" << endl;
        msg = "The system cannot find the path specified";
    }
    if (path.empty()) {
        fs.setWorkingDirectory(current);
        return;
    }
    pair<string, string> splittedPair = getsplittedPath(path);
    string splittedPath = splittedPair.first;
    path = splittedPair.second;
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
        msg = "The system cannot find the path specified";
    }

}


void CdCommand::execute(FileSystem &fs) {
    string path = getArgs();
    cd(path, &fs.getWorkingDirectory(), fs);
}

string CdCommand::toString() { return "cd"; }

LsCommand::LsCommand(string args) : BaseCommand(args) {}

void LsCommand::execute(FileSystem &fs) {
    pair<string, string> args = getTwoPaths();
    if (args.first == "-s")
        ls(args.second, &fs.getWorkingDirectory(), fs, true);
    else
        ls(args.first, &fs.getWorkingDirectory(), fs, false);
}

void LsCommand::ls(string path, Directory *current, FileSystem &fs, bool sortType) {
    if (!current) {
        cout << "The system cannot find the path specified" << endl;
        msg = "The system cannot find the path specified";
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
    pair<string, string> splittedPair = getsplittedPath(path);
    string splittedPath = splittedPair.first;
    path = splittedPair.second;
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
        msg = "The system cannot find the path specified";
    }
}

void LsCommand::print(BaseFile &pFile) {
    string type;
    if (pFile.getType())
        type = "DIR";
    else
        type = "FILE";
    cout << type << "\t" << pFile.getName() << "\t" << pFile.getSize() << endl;
    msg = type + "\t" + pFile.getName() + "\t" + std::to_string(pFile.getSize());
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

void MkdirCommand::mkdir(string path, Directory *current, FileSystem &fs) {
    if (!current) {
        return;
    }
    if (path.empty()) {
        return;
    }
    pair<string, string> splittedPair = getsplittedPath(path);
    string splittedPath = splittedPair.first;
    path = splittedPair.second;
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
        else {
            cout << "The directory already exists" << endl;
            msg = "The directory already exists";
        }
    }
    //todo:: check the case where the name of the the directory is a file
}

string MkdirCommand::toString() {
    return "mkdir";
}

MkfileCommand::MkfileCommand(string args) : BaseCommand(args) {
}

void MkfileCommand::execute(FileSystem &fs) {
    string args = getArgs();//split the size and the path
    size_t pos = args.find(' ');
    string path = args.substr(0, pos);
    args.erase(0, pos + 1);
    string fileName;
    pos = path.find_last_of('/');
    if ((pos == 0) && (pos == path.find('/'))) {
        fileName = path.substr(1, path.size() - 1);
        path = "/";
    } else if (pos != string::npos) {
        fileName = path.substr(pos + 1, path.length() - 1);
        path.erase(pos, path.length() - 1);
    } else {
        fileName = path;
        path = "";
    }
    int size = std::stoi(args);
    mkfile(path, &fs.getWorkingDirectory(), fs, size, fileName);
}

void MkfileCommand::mkfile(string path, Directory *current, FileSystem &fs, int size, string &name) {
    if (path.empty()) {
        BaseFile *basefile = current->getBaseFileByName(name);
        if (!basefile) {
            current->addFile(new File(name, size));
            return;
        }
        if (!basefile->getType()) {
            cout << "File already exists" << endl;
            msg = "File already exists";
            return;
        }
    }
    pair<string, string> splittedPair = getsplittedPath(path);
    string splittedPath = splittedPair.first;
    path = splittedPair.second;
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
        msg = "The system cannot find the path specified";
    }
}

string MkfileCommand::toString() {
    return "mkfile";
}

CpCommand::CpCommand(string args) : BaseCommand(args) {

}

void CpCommand::execute(FileSystem &fs) {
    pair<string, string> paths = getTwoPaths();
    string source = paths.first;
    string destination = paths.second;
    BaseFile *sourceFile = getBaseFileByPath(source, &fs.getWorkingDirectory(), fs);
    BaseFile *destDirectory = getBaseFileByPath(destination, &fs.getWorkingDirectory(), fs);
    if (sourceFile && destDirectory && destDirectory->getType()) {
        //todo:: check if dest is a child of source
        addcopyFile(sourceFile, destDirectory);
        return;
    }
    cout << "No such file or directory" << endl;
    msg = "No such file or directory";
}

void CpCommand::addcopyFile(BaseFile *sourceFile, BaseFile *destDirectory) {
    if (sourceFile->getType()) {
        (dynamic_cast<Directory *>(destDirectory))->addFile(new Directory(*dynamic_cast<Directory *>(sourceFile)));
    } else {
        (dynamic_cast<Directory *>(destDirectory))->addFile(new File(sourceFile->getName(), sourceFile->getSize()));

    }
}

string CpCommand::toString() {
    return "cp";
}

MvCommand::MvCommand(string args) : BaseCommand(args) {

}

void MvCommand::execute(FileSystem &fs) {
    pair<string, string> paths = getTwoPaths();
    string source = paths.first;
    string destination = paths.second;
    BaseFile *sourceFile;
    if (source == "/")
        sourceFile = &fs.getRootDirectory();
    else
        sourceFile = getBaseFileByPath(source, &fs.getWorkingDirectory(), fs);
    string sourceDirStr = removeLastPath(source);
    BaseFile *sourceDir;
    if (sourceDirStr.empty())
        sourceDir = &fs.getWorkingDirectory();
    else {
        if (sourceDirStr == "/")
            sourceDir = &fs.getRootDirectory();
        else
            sourceDir = getBaseFileByPath(sourceDirStr, &fs.getWorkingDirectory(), fs);
    }
    BaseFile *destDir = getBaseFileByPath(destination, &fs.getWorkingDirectory(), fs);
    if (!sourceDir || !destDir || !sourceFile || !destDir->getType()) {
        cout << "No such file or directory" << endl;
        msg = "No such file or directory";
        return;
    }
    if (!checkParents(sourceFile, fs)) {
        cout << "Can't move directory" << endl;
        msg = "Can't move directory";
        return;
    }
    if (dynamic_cast<Directory *>(destDir)->getBaseFileByName(sourceFile->getName()))
        return;
    dynamic_cast<Directory *>(destDir)->getChildren().push_back(sourceFile);
    (dynamic_cast<Directory *>(sourceDir)->getChildren()).erase(
            remove_if((dynamic_cast<Directory *>(sourceDir)->getChildren()).begin(),
                      (dynamic_cast<Directory *>(sourceDir)->getChildren()).end(), [sourceFile](BaseFile *basefile)->bool{return
                        basefile->getName() == sourceFile->getName();}));
//    auto it = dynamic_cast<Directory *>(sourceDir)->searchFileName(sourceFile->getName());
//    (dynamic_cast<Directory *>(sourceDir)->getChildren()).erase(it);
    if (sourceFile->getType()) {
        dynamic_cast<Directory *>(sourceFile)->setParent(dynamic_cast<Directory *>(destDir));
    }
}

string MvCommand::toString() {
    return "mv";
}

RenameCommand::RenameCommand(string args) : BaseCommand(args) {}

void RenameCommand::execute(FileSystem &fs) {
    pair<string, string> paths = getTwoPaths();
    string source = paths.first;
    string newName = paths.second;
    BaseFile *sourceFile;
    if (source == "/")
        sourceFile = &fs.getRootDirectory();
    else
        sourceFile = getBaseFileByPath(source, &fs.getWorkingDirectory(), fs);
    string sourceDirStr = removeLastPath(source);
    BaseFile *sourceDir = getBaseFileByPath(sourceDirStr, &fs.getWorkingDirectory(), fs);
    if (sourceDirStr == "/") {
        sourceDir = &fs.getRootDirectory();
    }
    if (!sourceDir || !sourceFile) {
        cout << "No such file or directory" << endl;
        msg = "No such file or directory";
        return;
    }
    if (dynamic_cast<Directory *>(sourceDir)->getBaseFileByName(newName))
        return;
    if (!checkParents(sourceFile, fs)) {
        cout << "Can't rename the working directory" << endl;
        msg = "Can't rename the working directory";
        return;
    }
    sourceFile->setName(newName);
}

string RenameCommand::toString() {
    return "rename";
}

RmCommand::RmCommand(string args) : BaseCommand(args) {

}

void RmCommand::execute(FileSystem &fs) {
    string path = getArgs();
    BaseFile *sourceFile = getBaseFileByPath(path, &fs.getWorkingDirectory(), fs);
    string sourceDirStr = removeLastPath(path);
    BaseFile *sourceDir;
    if (sourceDirStr.empty())
        sourceDir = &fs.getWorkingDirectory();
    else {
        if (sourceDirStr == "/")
            sourceDir = &fs.getRootDirectory();
        else
            sourceDir = getBaseFileByPath(sourceDirStr, &fs.getWorkingDirectory(), fs);
    }
    if (!sourceDir || !sourceFile) {
        cout << "No such file or directory" << endl;
        msg = "No such file or directory";
        return;
    }
    if (!checkParents(sourceFile, fs)) {
        cout << "Can't remove the working directory" << endl;
        msg = "Can't remove the working directory";
        return;
    }
    dynamic_cast<Directory *>(sourceDir)->removeFile(sourceFile);
    sourceFile = nullptr;

}

string RmCommand::toString() {
    return "rm";
}

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args),
                                                                                    history(history) {
}

void HistoryCommand::execute(FileSystem &fs) {
    for (size_t i = 0; i < history.size(), ++i;) {
        if (history[i]->getArgs().find(' ') != string::npos) {
            pair<string, string> args = splitArgs(history[i]->getArgs());
            cout << i << "\t" << history[i]->toString() << " " << args.first << " " << args.second << endl;
            msg = std::to_string(i) + history[i]->toString() + " " + args.first + " " + args.second;
        } else {
            cout << i << "\t" << history[i]->toString() << " " << history[i]->getArgs() << endl;
            msg = std::to_string(i) + history[i]->toString() + " " + history[i]->getArgs();

        }
    }
}

string HistoryCommand::toString() {
    return "history";
}

VerboseCommand::VerboseCommand(string args) : BaseCommand(args) {

}

void VerboseCommand::execute(FileSystem &fs) {
    int newVerbose = std::stoi(getArgs());
    if (newVerbose != 0 && newVerbose != 1 && newVerbose != 2 && newVerbose != 3) {
        cout << "Wrong verbose input" << endl;
        msg = "Wrong verbose input";
        return;
    }
    verbose = static_cast<unsigned int>(newVerbose);
}

string VerboseCommand::toString() {
    return "verbose";
}

ErrorCommand::ErrorCommand(string args) : BaseCommand(args) {

}

//todo:: assuming the commands name is the args
void ErrorCommand::execute(FileSystem &fs) {
    cout << getArgs() << ": Unknown command" << endl;
    msg = getArgs() + ": Unknown command";
}

string ErrorCommand::toString() {
    return getArgs();
}

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args), history(history) {

}

void ExecCommand::execute(FileSystem &fs) {
    int commandNumber = std::stoi(getArgs());
    if (commandNumber > history.size() - 1) {
        cout << "Command not found" << endl;
        msg = "Command not found";
    } else {
        history[commandNumber]->execute(fs);
    }
}

string ExecCommand::toString() {
    return "exec";
}

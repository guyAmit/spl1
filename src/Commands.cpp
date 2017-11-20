//
// Created by Guy-Amit on 11/8/2017.
//

#include "../include/Commands.h"

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

BaseCommand::~BaseCommand() {

}

BaseFile *BaseCommand::getBaseFileByPath(string path, Directory *current, FileSystem &fs) {
    if (!current) {
        return nullptr;
    }
    if (path.empty()) {
        return current;
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
    size_t pos= args.find(' ');
    if(pos !=string::npos) {
        string path1 = args.substr(0, pos);
        args.erase(0, pos + 1);
        string path2 = args;
        pair.first = path1;
        pair.second = path2;
    } else {
        pair.first = args;
        pair.second = "";
    }
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

BaseCommand *PwdCommand::copy() {
    return new PwdCommand(this->getArgs());
}

void PwdCommand::execute(FileSystem &fs) {
    cout << fs.getWorkingDirectory().getAbsolutePath() << endl;
}

string PwdCommand::toString() {
    return "pwd";
}

PwdCommand::~PwdCommand() {

}

CdCommand::CdCommand(string args) : BaseCommand(args) {

}

BaseCommand *CdCommand::copy() {
    return new CdCommand(this->getArgs());
}


void CdCommand::cd(string &path, Directory *current, FileSystem &fs) {
    if (!current) {
        cout << "The system cannot find the path specified" << endl;
        return;
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
    }

}


void CdCommand::execute(FileSystem &fs) {
    string path = getArgs();
    cd(path, &fs.getWorkingDirectory(), fs);
}

string CdCommand::toString() { return "cd"; }

CdCommand::~CdCommand() {

}

LsCommand::LsCommand(string args) : BaseCommand(args) {}

BaseCommand *LsCommand::copy() {
    return new LsCommand(this->getArgs());
}


void LsCommand::execute(FileSystem &fs) {
    pair<string, string> args = getTwoPaths();
    if (args.first == "-s")
        ls(args.second, &fs.getWorkingDirectory(), fs, true);
    else
        ls(getArgs(), &fs.getWorkingDirectory(), fs, false);
}

void LsCommand::ls(string path, Directory *current, FileSystem &fs, bool sortType) {
    BaseFile *basefile = getBaseFileByPath(path, current, fs);
    if (basefile && basefile->getType()) {
        Directory *dir = dynamic_cast<Directory *>(basefile);
        if (sortType)
            dir->sortBySize();
        else
            dir->sortByName();
        for (auto file: dir->getChildren())
            print(*file);
        return;
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

LsCommand::~LsCommand() {

}


MkdirCommand::MkdirCommand(string args) : BaseCommand(args) {

}

BaseCommand *MkdirCommand::copy() {
    return new MkdirCommand(this->getArgs());
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
        }

    } else {
        cout << "The directory already exists" << endl;
    }
}

string MkdirCommand::toString() {
    return "mkdir";
}

MkdirCommand::~MkdirCommand() {

}

MkfileCommand::MkfileCommand(string args) : BaseCommand(args) {
}

BaseCommand *MkfileCommand::copy() {
    return new MkfileCommand(this->getArgs());
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
    }
}

string MkfileCommand::toString() {
    return "mkfile";
}

MkfileCommand::~MkfileCommand() {

}

CpCommand::CpCommand(string args) : BaseCommand(args) {

}

BaseCommand *CpCommand::copy() {
    return new CpCommand(this->getArgs());
}


void CpCommand::execute(FileSystem &fs) {
    pair<string, string> paths = getTwoPaths();
    string source = paths.first;
    string destination = paths.second;
    BaseFile *sourceFile = getBaseFileByPath(source, &fs.getWorkingDirectory(), fs);
    BaseFile *destDirectory = getBaseFileByPath(destination, &fs.getWorkingDirectory(), fs);
    if (sourceFile && destDirectory && destDirectory->getType()) {
        addcopyFile(sourceFile, destDirectory);
        return;
    }
    cout << "No such file or directory" << endl;
}

void CpCommand::addcopyFile(BaseFile *sourceFile, BaseFile *destDirectory) {
    if (sourceFile->getType()) {
        Directory *newDirectory = new Directory(*dynamic_cast<Directory *>(sourceFile));
        newDirectory->setParent(dynamic_cast<Directory *>(destDirectory));
        (dynamic_cast<Directory *>(destDirectory))->addFile(newDirectory);
    } else {
        (dynamic_cast<Directory *>(destDirectory))->addFile(new File(sourceFile->getName(), sourceFile->getSize()));

    }
}

string CpCommand::toString() {
    return "cp";
}

CpCommand::~CpCommand() {

}

MvCommand::MvCommand(string args) : BaseCommand(args) {

}

BaseCommand *MvCommand::copy() {
    return new MvCommand(this->getArgs());
}


void MvCommand::execute(FileSystem &fs) {
    pair<string, string> paths = getTwoPaths();
    string source = paths.first;
    string destination = paths.second;
    BaseFile *sourceFile;
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
        return;
    }
    if (!checkParents(sourceFile, fs)) {
        cout << "Can't move directory" << endl;
        return;
    }
    if (dynamic_cast<Directory *>(destDir)->getBaseFileByName(sourceFile->getName()))
        return;
    dynamic_cast<Directory *>(destDir)->addFile(sourceFile);
    Directory *sourceDirCasted = dynamic_cast<Directory *>(sourceDir);
    sourceDirCasted->eraseByName(sourceFile->getName());
    if (sourceFile->getType()) {
        dynamic_cast<Directory *>(sourceFile)->setParent(dynamic_cast<Directory *>(destDir));
    }
}

string MvCommand::toString() {
    return "mv";
}

MvCommand::~MvCommand() {

}

RenameCommand::RenameCommand(string args) : BaseCommand(args) {}

BaseCommand *RenameCommand::copy() {
    return new RenameCommand(this->getArgs());
}


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
        return;
    }
    if (dynamic_cast<Directory *>(sourceDir)->getBaseFileByName(newName))
        return;
    if (!checkParents(sourceFile, fs)) {
        cout << "Can't rename the working directory" << endl;
        return;
    }
    sourceFile->setName(newName);
}

string RenameCommand::toString() {
    return "rename";
}

RenameCommand::~RenameCommand() {

}

RmCommand::RmCommand(string args) : BaseCommand(args) {}

BaseCommand *RmCommand::copy() {
    return new RmCommand(this->getArgs());
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
    if (sourceDirStr == "/" && path == "/") {
        cout << "Can't remove directory" << endl;
        return;
    }
    if (!sourceDir || !sourceFile) {
        cout << "No such file or directory" << endl;
        return;
    }
    if (!checkParents(sourceFile, fs)) {
        cout << "Can't remove directory" << endl;
        return;
    }
    dynamic_cast<Directory *>(sourceDir)->removeFile(sourceFile);
    sourceFile = nullptr;

}

string RmCommand::toString() {
    return "rm";
}

RmCommand::~RmCommand() {

}

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args),
                                                                                    history(history) {
}

BaseCommand *HistoryCommand::copy() {
    return new HistoryCommand(this->getArgs(), this->history);
}


void HistoryCommand::execute(FileSystem &fs) {
    int i = 0;
    while (i < static_cast<int>(history.size())) {
        if (dynamic_cast<ErrorCommand *>(history[i])) {
            cout << i << "\t" << history[i]->toString() << endl;
        } else {
            cout << i << "\t" << history[i]->toString() << " " << history[i]->getArgs() << endl;

        }
        i = i + 1;
    }
}

string HistoryCommand::toString() {
    return "history";
}

HistoryCommand::~HistoryCommand() {

}

VerboseCommand::VerboseCommand(string args) : BaseCommand(args) {

}

BaseCommand *VerboseCommand::copy() {
    return new VerboseCommand(this->getArgs());
}


void VerboseCommand::execute(FileSystem &fs) {
    int newVerbose = std::stoi(getArgs());
    if (newVerbose != 0 && newVerbose != 1 && newVerbose != 2 && newVerbose != 3) {
        cout << "Wrong verbose input" << endl;
        return;
    }
    verbose = static_cast<unsigned int>(newVerbose);
}

string VerboseCommand::toString() {
    return "verbose";
}

VerboseCommand::~VerboseCommand() {

}

ErrorCommand::ErrorCommand(string args) : BaseCommand(args) {

}

BaseCommand *ErrorCommand::copy() {
    return new ErrorCommand(this->getArgs());
}


//todo:: assuming the commands name is the args
void ErrorCommand::execute(FileSystem &fs) {
    string args = getArgs();
    size_t pos = args.find(' ');
    if ((pos != string::npos)) {
        cout << args.substr(0, pos) << ": Unknown command" << endl;
    } else {
        cout << args << ": Unknown command" << endl;

    }
}


string ErrorCommand::toString() {
    return getArgs();
}

ErrorCommand::~ErrorCommand() {

}

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args), history(history) {

}

BaseCommand *ExecCommand::copy() {
    return new ExecCommand(this->getArgs(), this->history);
}

void ExecCommand::execute(FileSystem &fs) {
    int commandNumber = std::stoi(getArgs());
    if (commandNumber > static_cast<int>(history.size()) - 1) {
        cout << "Command not found" << endl;
    } else {
        history[commandNumber]->execute(fs);
    }
}

string ExecCommand::toString() {
    return "exec";
}

ExecCommand::~ExecCommand() {

}

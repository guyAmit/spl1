//
// Created by Guy-Amit on 11/8/2017.
//

#include "../include/Environment.h"

Environment::Environment() : commandsHistory(), fs() {
}

void Environment::start() {
    string line;
    vector<string> inputStrings;
    string string1;
    cout << fs.getWorkingDirectory().getAbsolutePath() << '>';
    getline(cin, line);
    istringstream iss(line);
    while (iss >> string1) {
        inputStrings.push_back(string1);
    }
    while (inputStrings.empty() || inputStrings[0] != "exit") {
        if (!inputStrings.empty()) {
            if (verbose == 2 || verbose == 3) {
                cout << line << endl;
            }
            createCommand(inputStrings, line);
        }
        cout << fs.getWorkingDirectory().getAbsolutePath() << '>';
        inputStrings.clear();
        getline(cin, line);
        istringstream iss(line);
        for (string string1; iss >> string1; inputStrings.push_back(string1));
    }


}


void Environment::createCommand(vector<string> inputStrings, string line) {
    string x = inputStrings[0];
    string y = "";
    string z = "";
    if (inputStrings.size() > 1) {
        y = inputStrings[1];
    }
    if (inputStrings.size() > 2) {
        z = inputStrings[2];
    }
    if (x == "ls") {
        string args;
        if (z.empty())
            args = y;
        else
            args = y + ' ' + z;
        LsCommand *ls = new LsCommand(args);
        ls->execute(fs);
        addToHistory(ls);
        return;
    }
    if (x == "mkdir") {
        MkdirCommand *mkdir = new MkdirCommand(y);
        mkdir->execute(fs);
        addToHistory(mkdir);
        return;
    }
    if (x == "mkfile") {
        string args = y + ' ' + z;
        MkfileCommand *mkfile = new MkfileCommand(args);
        mkfile->execute(fs);
        addToHistory(mkfile);
        return;
    }
    if (x == "cd") {
        string args = y;
        CdCommand *cd = new CdCommand(args);
        cd->execute(fs);
        addToHistory(cd);
        return;
    }
    if (x == "rm") {
        string args = y;
        RmCommand *rm = new RmCommand(args);
        rm->execute(fs);
        addToHistory(rm);
        return;
    }
    if (x == "pwd") {
        PwdCommand *pwd = new PwdCommand("");
        pwd->execute(fs);
        addToHistory(pwd);
        return;
    }
    if (x == "cp") {
        CpCommand *cp = new CpCommand(y + ' ' + z);
        cp->execute(fs);
        addToHistory(cp);
        return;
    }
    if (x == "mv") {
        MvCommand *mv = new MvCommand(y + ' ' + z);
        mv->execute(fs);
        addToHistory(mv);
        return;
    }
    if (x == "rename") {
        RenameCommand *rename = new RenameCommand(y + ' ' + z);
        rename->execute(fs);
        addToHistory(rename);
        return;
    }
    if (x == "history") {
        HistoryCommand *history = new HistoryCommand(y, commandsHistory);
        history->execute(fs);
        addToHistory(history);
        return;
    }
    if (x == "verbose") {
        VerboseCommand *verbose = new VerboseCommand(y);
        verbose->execute(fs);
        addToHistory(verbose);
        return;
    }
    if (x == "exec") {
        ExecCommand *exec = new ExecCommand(y, commandsHistory);
        exec->execute(fs);
        addToHistory(exec);
        return;
    }
    ErrorCommand *error = new ErrorCommand(line);
    error->execute(fs);
    addToHistory(error);

}

FileSystem &Environment::getFileSystem() {
    return fs;
}

const vector<BaseCommand *> &Environment::getHistory() const {
    return commandsHistory;
}

void Environment::addToHistory(BaseCommand *command) {
    if (command) {
        commandsHistory.push_back(command);
    }
}

//rule of 5 methods
void Environment::clean() {
    for (auto command :commandsHistory) {
        delete command;
    }
}

void Environment::copy(const Environment &rhs) {
    this->fs = rhs.fs;
    for (auto command :rhs.commandsHistory) {
        this->commandsHistory.push_back(command->copy());
    }
}

void Environment::steal(Environment &rhs) {
    this->fs = rhs.fs;
    this->commandsHistory = rhs.commandsHistory;
    rhs.commandsHistory.clear();
}

Environment::~Environment() {
    if (verbose == 1 || verbose == 3) {
        cout << "Environment::~Environment()" << endl;
    }
    clean();

}

Environment::Environment(const Environment &rhs):commandsHistory() ,fs(){
    if (verbose == 1 || verbose == 3) {
        cout << "Environment::Environment(const Environment &rhs)" << endl;
    }
    copy(rhs);
}

Environment &Environment::operator=(const Environment &rhs) {
    if (verbose == 1 || verbose == 3) {
        cout << "Environment &Environment::operator=(const Environment &rhs)" << endl;
    }
    if (this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

Environment &Environment::operator=(Environment &&rhs) {
    if (verbose == 1 || verbose == 3) {
        cout << "Environment &Environment::operator=(Environment &&rhs)" << endl;
    }
    clean();
    steal(rhs);
    return *this;
}

Environment::Environment(Environment &&rhs):commandsHistory(),fs() {
    if (verbose == 1 || verbose == 3) {
        cout << "Environment::Environment(Environment &&rhs)" << endl;
    }
    steal(rhs);
}

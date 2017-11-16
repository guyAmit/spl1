//
// Created by Guy-Amit on 11/8/2017.
//

#include "Environment.h"

Environment::Environment() {
    vector<BaseCommand *> *commandsHistory=new vector<BaseCommand*>();
    FileSystem *fs = new FileSystem();
}

void Environment::start() {
    string line;
    vector<string> inputStrings;
    string string1;
    cout << fs.getWorkingDirectory().getName()<< '>';
    getline(cin, line);
    istringstream iss(line);
    while (iss >> string1) {
        inputStrings.push_back(string1);
    }
    while (inputStrings[0] != "exit") {
        createCommand(inputStrings);
        cout << fs.getWorkingDirectory().getName()<< '>';
        inputStrings.clear();
        getline(cin, line);
        istringstream iss(line);
        for(string string1; iss >>string1; inputStrings.push_back(string1));
    }


}


void Environment::createCommand(vector<string> inputStrings) {
    string x = inputStrings[0];
    string y = "";
    string z = "";
    if (inputStrings.size() > 1) {
        y = inputStrings[1];
    }
    if(inputStrings.size()>2) {
        z = inputStrings[2];
    }
    if ( x== "ls") {
        string args = y + ' ' + z;
        LsCommand* ls=new LsCommand(args);
        ls->execute(fs);
        addToHistory(ls);
        return;
    }
    if (x == "mkdir") {
        MkdirCommand* mkdir=new MkdirCommand(y);
        mkdir->execute(fs);
        addToHistory(mkdir);
        return;
    }
    if (x == "mkfile") {
        string args = y + ' ' + z;
        MkfileCommand *mkfile=new MkfileCommand(args);
        mkfile->execute(fs);
        addToHistory(mkfile);
        return;
    }
    if(x=="cd") {
        string args = y;
        CdCommand* cd=new CdCommand(args);
        cd->execute(fs);
        addToHistory(cd);
        return;
    }
    if (x == "rm") {
        string args = y;
        RmCommand* rm=new RmCommand(args);
        rm->execute(fs);
        addToHistory(rm);
        return;
    }
    if (x == "pwd") {
        PwdCommand* pwd = new PwdCommand("");
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
    if(x=="mv") {
        MvCommand *mv = new MvCommand(y + ' ' + z);
        mv->execute(fs);
        addToHistory(mv);
        return;
    }
    if(x=="rename") {
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
        VerboseCommand* verbose =new VerboseCommand(y);
        verbose->execute(fs);
        addToHistory(verbose);
        return;
    }
    if (x == "exec") {
        ExecCommand *exec = new ExecCommand("y", commandsHistory);
        exec->execute(fs);
        addToHistory(exec);
        return;
    }
        ErrorCommand* error = new ErrorCommand(x);
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

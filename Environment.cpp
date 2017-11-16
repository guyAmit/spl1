//
// Created by Guy-Amit on 11/8/2017.
//

#include "Environment.h"

Environment::Environment() {
    vector<BaseCommand *> *commandsHistory=new vector<BaseCommand*>();
    FileSystem *fs = new FileSystem();
}

void Environment::start() {
    string x, y, z;
    cout << fs.getWorkingDirectory().getName()<< '>';
    cin >> x >> y >> z;
    while (x != "exit") {
        createCommand(x, y,z);
        cout << fs.getWorkingDirectory().getName()<< '>';
        cin >> x >> y >> z;

    }

}


void Environment::createCommand(const string &x, const string &y,const string &z) {
    if (x == "ls") {
        string args = y + '$' + z;
        LsCommand ls(args);
        ls.execute(fs);
    }
    if (x == "mkdir") {
        MkdirCommand mkdir(y);
        mkdir.execute(fs);
    }
    if (x == "mkfile") {
        string args = y + '$' + z;
        MkfileCommand mkfile(args);
        mkfile.execute(fs);
    }
    if(x=="cd") {
        string args = y;
        CdCommand cd(args);
        cd.execute(fs);
    }
    if (x == "rm") {
        string args = y;
        RmCommand rm(args);
        rm.execute(fs);
    }
}

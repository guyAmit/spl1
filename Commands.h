#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include "FileSystem.h"
#include <iostream>


class BaseCommand {
private:
    string args;
protected:
    /**
 *
 * @param path - the path to split
 * @return the substring until the first '/'.
 */
    string getsplittedPath(string path);


public:

    BaseCommand(string args);

    string getArgs();

    virtual void execute(FileSystem &fs) = 0;

    virtual string toString() = 0;

    void cd(string path,Directory* current,FileSystem &fs);
};

class PwdCommand : public BaseCommand {
private:
public:
    PwdCommand(string args);

    void execute(FileSystem &fs); // Every derived class should implement this function according to the document (pdf)
    //print the working directory from the instance of file system
    virtual string toString();
};

//Todo:: implament a function get BaseFile by Path. the function will be used in a the commends
class CdCommand : public BaseCommand {
private:
public:
    CdCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};


//print the child vector
class LsCommand : public BaseCommand {
private:
public:
    LsCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};


class MkdirCommand : public BaseCommand {
private:
public:
    MkdirCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};

class MkfileCommand : public BaseCommand {
private:
public:
    MkfileCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};

//check currect defintion in office hours
class CpCommand : public BaseCommand {
private:
public:
    CpCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};


class MvCommand : public BaseCommand {
private:
public:
    MvCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};

//find and remove
class RenameCommand : public BaseCommand {
private:
public:
    RenameCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};

//find and delete
class RmCommand : public BaseCommand {
private:
public:
    RmCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};

class HistoryCommand : public BaseCommand {
private:
    const vector<BaseCommand *> &history;
public:
    HistoryCommand(string args, const vector<BaseCommand *> &history);

    void execute(FileSystem &fs);

    string toString();
};


class VerboseCommand : public BaseCommand {
private:
public:
    VerboseCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};

class ErrorCommand : public BaseCommand {
private:
public:
    ErrorCommand(string args);

    void execute(FileSystem &fs);

    string toString();
};

class ExecCommand : public BaseCommand {
private:
    const vector<BaseCommand *> &history;
public:
    ExecCommand(string args, const vector<BaseCommand *> &history);

    void execute(FileSystem &fs);

    string toString();
};


#endif

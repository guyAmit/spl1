#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include "FileSystem.h"
#include <iostream>
#include "GlobalVariables.h"

class BaseCommand {
private:
    string args;
public:
    /**
 *
 * @param path - the path to split
 * @return the substring until the first '/'.
 */
    pair<string,string> getsplittedPath(string path);

    BaseFile *getBaseFileByPath(string path,Directory* current,FileSystem &fs);
    /**
     * splits the args field (string) into two strings by ' '.
     *
     * @return  two strings- the first is the string before ' '. the second- the string after ' '.
     */
   pair <string, string> getTwoPaths();
    /**
     * splits the args (string) into two strings by '$'.
     *@param args -the string to split
     * @return  two strings- the first is the string before ' '. the second- the string after ' '.
     */
    pair<string, string> splitArgs(string args);
    /**
*
* @param path - the path to split
* @return the string before the last '/'
*/
    string removeLastPath(string path);
/**
 *
 * @return iff the basefile is not a child of the root directory or the working directory
 */
    bool checkParents(BaseFile * basefile,FileSystem &fs);




    BaseCommand(string args);

    string getArgs();

    virtual void execute(FileSystem &fs) = 0;

    virtual string toString() = 0;
    virtual ~BaseCommand()=0;

    virtual BaseCommand *copy()=0;

};

class PwdCommand : public BaseCommand {
private:
public:
    PwdCommand(string args);

    void execute(FileSystem &fs); // Every derived class should implement this function according to the document (pdf)
    //print the working directory from the instance of file system
    virtual string toString();
    virtual ~PwdCommand();

    BaseCommand *copy();
};

//Todo:: implement a function get BaseFile by Path. the function will be used in a the commands
class CdCommand : public BaseCommand {
private:
    void cd(string &path,Directory* current,FileSystem &fs);
public:
    CdCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~CdCommand();

    BaseCommand *copy();
};


//print the child vector
class LsCommand : public BaseCommand {
private:
    void ls(string path, Directory *current, FileSystem &fs, bool sortType);
    void print(BaseFile &pFile);
public:
    LsCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~LsCommand();

    BaseCommand *copy();
};


class MkdirCommand : public BaseCommand {
private:
    void mkdir(string path, Directory *current, FileSystem &fs);

public:
    MkdirCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~MkdirCommand();

    BaseCommand *copy();
};

class MkfileCommand : public BaseCommand {
private:
    void mkfile(string path, Directory *current, FileSystem &fs,int size,string &name);

public:
    MkfileCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~MkfileCommand();

    BaseCommand *copy();
};

class CpCommand : public BaseCommand {
private:
public:
    CpCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~CpCommand();

    void addcopyFile(BaseFile *sourceFile, BaseFile *destDirectory) ;

    BaseCommand *copy();
};


class MvCommand : public BaseCommand {
private:
public:
    MvCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~MvCommand();

    BaseCommand *copy();
};

//find and remove
class RenameCommand : public BaseCommand {
private:
public:
    RenameCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~RenameCommand();

    BaseCommand *copy();
};

//find and delete
class RmCommand : public BaseCommand {
private:
public:
    RmCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~RmCommand();

    BaseCommand *copy();
};

class HistoryCommand : public BaseCommand {
private:
    const vector<BaseCommand *> &history;
public:
    HistoryCommand(string args, const vector<BaseCommand *> &history);

    void execute(FileSystem &fs);

    string toString();

    virtual ~HistoryCommand();

    BaseCommand *copy();
};


class VerboseCommand : public BaseCommand {
private:
public:
    VerboseCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~VerboseCommand();

    BaseCommand *copy();
};

class ErrorCommand : public BaseCommand {
private:
public:
    ErrorCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    virtual ~ErrorCommand();

    BaseCommand *copy();
};

class ExecCommand : public BaseCommand {
private:
    const vector<BaseCommand *> &history;
public:
    ExecCommand(string args, const vector<BaseCommand *> &history);

    void execute(FileSystem &fs);

    string toString();

    virtual ~ExecCommand();

    BaseCommand *copy();
};


#endif

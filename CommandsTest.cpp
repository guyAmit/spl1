//
// Created by Guy-Amit on 11/12/2017.
//

#include <iostream>
#include "Files.h"
#include "FileSystem.h"
#include "Commands.h"
#include "vector"
#include "string"

using namespace std;

/***********************************************************
 *  tests on the root directory   *
 ************************************************************/

/**RootTest #1:: testing the path of root
 * @param sys
 * @invariant root should not change
 * @return 1->test field 0->good
 */
int pwdTest1(FileSystem &sys){
    PwdCommand pw("");
    pw.execute(sys);
    if("/"!=pw.toString()) {
        std::cout<<"path on working directory is wrong in pwdTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #2::simple addtion of a directory to root
 * @param sys
 * @pre root is empty
 * @post root contain <dir1>
 * @return 1->test field 0->good
 */
int makeDirTest1(FileSystem &sys){
    MkdirCommand mk("/dir1");
    mk.execute(sys);
    if(sys.getRootDirectory().getChildren()[0]->getName()!="dir1") {
        std::cout<<"making directory dir1 in root failed in makeDirTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #3::simple addtion of file to root
 * @param sys
 * @pre root contain just a directory
 * @post root contain <dir1,file1>
 * @return 1->test field 0->good
 */
int makeFileTest1(FileSystem &sys){
    MkfileCommand mk("/file1 1000");
    mk.execute(sys);
    if(sys.getRootDirectory().getChildren()[1]->getName()!="file1") {
        std::cout<<"making file file1 in root failed in makeFileTest1"<<std::endl;
        return 1;
    }
    return 0;
}
/**RootTest #4::adding a file to an illegal path
 * @param sys
 * @pre root contain two files: <dir1,file1>
 * @post root contain <dir1,file1>
 * @return 1->test field 0->good
 */
int makeFileTest2(FileSystem &sys){
    MkfileCommand mk("/hugabuga/huga 1000");
    try{
        mk.execute(sys);
    }catch(std::exception){
        std::cout<<"exception was thrown in makeFileTest2"<<std::endl;
        return 1;
    }
    if(mk.msg!="The system cannot find the path specified"){
        std::cout<<"incorrect massge in makeFileTest2"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #5::adding a file with the same name
 * @param sys
 * @pre root contain two files: <dir1,file1>
 * @post root contain <dir1,file1>
 * @return 1->test field 0->good
 */
int makeFileTest3(FileSystem &sys){
    MkfileCommand mk("/file1 1000");
    mk.execute(sys);
    if(sys.getRootDirectory().getChildren().size()!=2) {
        std::cout<<"can not add a file with the same name in makeFileTest3"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #6::simple ls test on root
 * @param sys
 * @invariant root contain two files: <dir1,file1>
 * @return 1->test field 0->good
 */
int lsTest1(FileSystem &sys){
    LsCommand ls("/");
    ls.execute(sys);
    if(ls.msg!="DIR    dir1    0\nFILE     file1   1000") {
        std::cout<<"ls is not correct lsTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #7::renaming of the file test
 * @param sys
 * @pre root contain two files: <dir1,file1>
 * @post name of file1 is now file
 * @return 1->test field 0->good
 */
int renameTest1(FileSystem &sys){
    RenameCommand rm("/file1 file");
    rm.execute(sys);
    if(sys.getRootDirectory().getChildren()[1]->getName()!="file") {
        std::cout<<"changing file name failed in renameTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #8::renaming of a file that does not existce
 * @param sys
 * @pre root contain two files: <dir1,file1>
 * @post name of file1 is now file
 * @return 1->test field 0->good
 */
int renameTest2(FileSystem &sys){
    RenameCommand rm("/elmo file");
    try {
        rm.execute(sys);
    } catch (std::exception){
        std::cout<<"exception was thrown in renameTest2"<<std::endl;
        return 1;
    }
    if(sys.getRootDirectory().getChildren()[1]->getName()!="file") {
        std::cout<<"changing file name failed in renameTest2"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #9::trying to rename root
 * @param sys
 * @pre root contain two files: <dir1,file1>
 * @post name of file1 is now file
 * @return 1->test field 0->good
 */
int renameTest3(FileSystem &sys){
    RenameCommand rm("/ root1");
    try {
        rm.execute(sys);
    } catch (std::exception){
        std::cout<<"exception was thrown in renameTest3"<<std::endl;
        return 1;
    }
    if(sys.getRootDirectory().getChildren()[1]->getName()!="/") {
        std::cout<<"can not change the name of root in renameTest3"<<std::endl;
        return 1;
    }
    return 0;
}int

/**RootTest #10:: trying to move a file to an illegal location
 * @param sys
 * @pre root contain two files: <dir1,file>
 * @post root is now empty
 * @return 1->test field 0->good
 */
int mvTest1(FileSystem &sys){
    MvCommand mv("/file /cookie/monster");
    try{
        mv.execute(sys);
    }catch (std::exception){
        std::cout<<"exception was thrown in makeFileTest2"<<std::end;
        return 1;
    }
    if(mv.msg!="No such file or directory"){
        std::cout<<"incorrect messege in mvTest1"<<std::endl;
    }
}


/**RootTest #11::removale of the directory and file created in root
 * @param sys
 * @pre root contain two files: <dir1,file>
 * @post root is now empty
 * @return 1->test field 0->good
 */
int rmTest1(FileSystem &sys){
    RmCommand rm1("/file");
    RmCommand rm2("/Dir1");
    rm1.execute(sys);
    rm2.execute(sys);
    if(sys.getRootDirectory().getChildren().size()!=0) {
        std::cout<<"delete failed->root should be empty"<<std::endl;
        return 1;
    }
    return 0;
}


/**RootTest #11::history check
 * @param sys
 * @pre root contain two files: <dir1,file1>
 * @post root is now empty
 * @return 1->test field 0->good
 */
int historyTest1(FileSystem &sys){
 //Todo:: find a way to implament
}

int rootTests(FileSystem &sys){
    int counter=0;
    counter+=pwdTest1(sys);
    counter+=makeDirTest1(sys);
    counter+=makeFileTest1(sys);
    counter+=makeFileTest2(sys);
    counter+=makeFileTest3(sys);
    counter+=lsTest1(sys);
    counter+=mvTest1(sys);
    counter+=renameTest1(sys);
    counter+=renameTest2(sys);
    counter+=renameTest3(sys);
    counter+=rmTest1(sys);
    counter+=historyTest1(sys);
    return counter;
}

/***********************************************************
 *  tests on level #2   *
 *  assuiming tests on root succseeded
 ************************************************************/

/** #constuctor for test
 * @pre root is empty
 * @post root is now <f1,dir2,dir2,dir3>
 */
void construct(FileSystem &sys){
    MkfileCommand mkf1("/file1 100");
    mkf1.execute(sys);
    MkdirCommand mkdir1("/dir1");
    mkdir1.execute(sys);
    MkdirCommand mkdir2("/dir2");
    mkdir1.execute(sys);
    MkdirCommand mkdir3("/dir3");
    mkdir1.execute(sys);
}

/**Lvel2Test #1:: cdTest
 * @param sys
 * @pre root is <f1,dir1,dir2,dir3>
 * @return 1->test field 0->good
 */
int lvl2CdTest1(FileSystem &sys){
    CdCommand cd("/dir1");
    try {
        cd.execute(sys);
        if (sys.getWorkingDirectory().getName() != "dir1") {
            std::cout << "working directory did not change on lvl2CdTest1" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2CdTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #2:: making a new directory inside dir1 from inside the folder dir1
 * @param sys
 * @pre root is <f1,dir1,dir2,dir3>, working directory is "/dir1"
 * @post dir1 has changed to <file2>
 * @return 1->test field 0->good
 */
int lvl2MkFileTest1(FileSystem &sys){
    MkfileCommand mk("/dir1/file2 100");
    try {
        mk.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=1) {
            std::cout << "file2 was not created inside /dir1 on lvl2MkFileTest1" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2MkFileTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #3:: making a new directory inside dir1 from inside the folder dir1
 * @param sys
 * @pre root is <f1,dir1,dir2,dir3>, working directory is "/dir1, dir1 is now <file2>"
 * @post dir1 has changed to <file2>
 * @return 1->test field 0->good
 */
int lvl2MkFileTest2(FileSystem &sys){
    MkfileCommand mk("/dir1/file3 150");
    try {
        mk.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=2) {
            std::cout << "file3 was not created inside /dir1 on lvl2MkFileTest2" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2MkFileTest2"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #4:: going from dir1 upwards to root
 * @param sys
 * @pre root is <f1,dir1,dir2,dir3>, working directory is "/dir1"
 * @post dir1 has changed to <file2>
 * @return 1->test field 0->good
 */
int lvl2CdTest2(FileSystem &sys){
    CdCommand cd("..");
    try {
        cd.execute(sys);
        if (sys.getWorkingDirectory().getName()!="/") {
            std::cout << "working directory did not changed on lvl2CdTest2" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2CdTest2"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #5:: making a new file inside dir1
 * @param sys
 * @pre root is <f1,dir1,dir2,dir3>, working directory is "/", dir1 is now <file2>"
 * @post dir1 has changed to <file2,file3>
 * @return 1->test field 0->good
 */
int lvl2MkFileTest3(FileSystem &sys){
    MkfileCommand mk("/dir2/file4 200");
    try {
        mk.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=1) {
            std::cout << "file4 was not created inside /dir2 on lvl2MkFileTest3" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2MkFileTest3"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #6:: copying file1 from "/" to "/dir3"
 * @param sys
 * @pre root is <f1,dir1,dir2,dir3>, working directory is "/", dir1 is now <file2,file3>"
 * @post dir3 has changed to <file1>
 * @return 1->test field 0->good
 */
int lvl2CpTest1(FileSystem &sys){
    CpCommand cp("/file1 /dir3");
    CdCommand cd("/dir3");
    CdCommand cd1("..");
    try {
        cp.execute(sys);
        cd.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=1) {
            std::cout << "file1 was not copied from root to dir3 on lvl2CpTest1" << std::endl;
            return 1;
        }
        cd1.execute(sys);
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2CpTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #6:: copying file1 from "/dir1" to "/dir2
 * @param sys
 * @pre root is <f1,dir1,dir2,dir3>, working directory is "/", dir1 is now <file2,file3>"
 * @post dir3 has changed to <file1>
 * @return 1->test field 0->good
 */
int lvl2CpTest2(FileSystem &sys){
    CpCommand cp("/dir1/file2 /dir2");
    CdCommand cd("/dir2");
    CdCommand cd1("..");
    try {
        cp.execute(sys);
        cd.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=2 ) {
            std::cout << "file1 was not copied from root to dir3 on lvl2CpTest2" << std::endl;
            return 1;
        }
        cd1.execute(sys);
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2CpTest2"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #7:: removing file1 from "/" to
 * @param sys
 * @pre root is <file1,dir1,dir2,dir3>, working directory is "/", dir1 is now <file2,file3>, dir3 is now <file1>"
 * @post root is now <dir1,dir2,dir3>
 * @return 1->test field 0->good
 */
int lvl2RmTest1(FileSystem &sys){
    RmCommand rm("/file1");
    try {
        rm.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=3 ) {
            std::cout << "file1 was not deleted from root on lvl2RmTest1" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2RmTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #8:: removing dir3 from "/"
 * @param sys
 * @pre root is <dir1,dir2,dir3>, working directory is "/", dir1 is now <file2,file3>
 * @post root is now <dir1,dir2>
 * @return 1->test field 0->good
 */
int lvl2RmTest2(FileSystem &sys){
    RmCommand rm("/dir3");
    try {
        rm.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=2 ) {
            std::cout << "dir3 was not deleted from root on lvl2RmTest2" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2RmTest2"<<std::endl;
        return 1;
    }
    return 0;
}


/**Lvel2Test #9:: creating two folders at the same time
 * @param sys
 * @pre root is <dir1,dir2>, working directory is "/", dir1 is now <file2,file3>
 * @post root is now <dir1,dir2,dir4> and dir4 is <dir5>
 * @return 1->test field 0->good
 */
int lvl2MkDIrTest1(FileSystem &sys){
    MkdirCommand mk("/dir4/dir5");
    CdCommand cd("dir4");
    CdCommand cd1("..");
    try {
        mk.execute(sys);
        cd.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=1 ) {
            std::cout << "dir3 was not deleted from root on lvl2MkDIrTest1" << std::endl;
            return 1;
        }
        cd1.execute(sys);
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2MkDIrTest1"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #10:: trying to go inside dir3 whitch we have just deleted
 * @param sys
 * @pre root is <dir1,dir2,dir4>, working directory is "/", dir1 is now <file2,file3>
 * @post root is now <dir1,dir2,dir4> and dir4 is <dir5>
 * @return 1->test field 0->good
 */
int lvl2CdTest3(FileSystem &sys){
    CdCommand cd("/dir3");
    try {
        cd.execute(sys);
        if (cd.msg!="The system cannot find the path specified" || sys.getWorkingDirectory().getName()!="/" ) {
            std::cout << "something went wrong in on lvl2CdTest3" << std::endl;
            return 1;
        }
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2CdTest3"<<std::endl;
        return 1;
    }
    return 0;
}

/**Lvel2Test #11:: moving dir2 to dir1
 * @param sys
 * @pre root is <dir1,dir2,dir4>, working directory is "/", dir1 is now <file2,file3>
 * @post root is now <dir1,dir4> and dir4 is <dir5> and dir1 is <file2,file3,dir2>, working directory is root
 * @return 1->test field 0->good
 */
int lvl2MvTest1(FileSystem &sys){
    MvCommand mv("/dir2 /dir1");
    CdCommand cd("/dir1");
    CdCommand cd1("/dir1/dir2");
    CdCommand cd2("..")
    try {
        mv.execute(sys);
        cd.execute(sys);
        if (sys.getWorkingDirectory().getChildren().size()!=3) {
            std::cout << "dir2 was not moved inside dir2 on lvl2MvTest1" << std::endl;
            return 1;
        }
        cd1.execute(sys);
        if(sys.getWorkingDirectory().getChildren().size()!=2){
            std::cout<< "the files from dir2 was not moved with the folder on lvl2MvTest1"<<std::endl;
            return 1;
        }
        cd2.execute(sys);
        cd2.execute(sys);
    }
    catch(std::exception) {
        std::cout<<"exception was thrown in lvl2MvTest1"<<std::endl;
        return 1;
    }
    return 0;
}
/***************************************************************************/
int levelTwoTests(FileSystem &sys){
    int counter=0;
    construct(sys);
    counter+=lvl2CdTest1(sys);
    counter+=lvl2MkFileTest1(sys);
    counter+=lvl2MkFileTest2(sys);
    counter+=lvl2CdTest2(sys);
    counter+=lvl2MkFileTest3(sys);
    counter+=lvl2CpTest1(sys);
    counter+=lvl2RmTest1(sys);
    counter+=lvl2RmTest2(sys);
    counter+=lvl2MkDIrTest1(sys);
    counter+=lvl2CdTest3(sys);
    counter+=lvl2MvTest1(sys);
    return counter;
}
/***********************************************************
 * main tests on level #2   *
 ************************************************************/

int main(int main(int , char **)){
    int red1;
    FileSystem *sys1 = new FileSystem();
    red1+=rootTests(*sys1);
    std::cout<<"root level: red:"<<red1<<"green:"<<11-red1<<std::endl;
       if(red1>0){
        throw std::exception();
    }
    delete sys1;
    int red2=0;
    FileSystem *sys2 = new FileSystem();
    red2+=levelTwoTests(*sys2);
    std::cout<<"level 2: red:"<<red1<<"green:"<<11-red1<<std::endl;
    if(red2>0){
        throw std::exception();
    }


}



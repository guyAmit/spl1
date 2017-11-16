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
    if(mk.toString()!="The system cannot find the path specified"){
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
    if(ls.toString()!="DIR    dir1    0\nFILE     file1   1000") {
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
    if(mv.toString()!="No such file or directory"){
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
 ************************************************************/



//int main(int main(int , char **)){
//    int red;
//    FileSystem *sys = new FileSystem();
//    red+=rootTests(*sys);
//    if(red>0) throw std::exception();
//
//}


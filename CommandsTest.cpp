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
int pwdTest(FileSystem &sys){
    PwdCommand pw("");
    pw.execute(sys);
    if("/"!=pw.toString()) {
        std::cout<<"path on working directory is wrong"<<std::endl;
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
        std::cout<<"making directory dir1 in root failed"<<std::endl;
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
    MkfileCommand mk("/ 1000");
    mk.execute(sys);
    if(sys.getRootDirectory().getChildren()[1]->getName()!="file1") {
        std::cout<<"making file file1 in root failed"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #4::simple ls test on root
 * @param sys
 * @invariant root contain two files: <dir1,file1>
 * @return 1->test field 0->good
 */
int lsTest1(FileSystem &sys){
    LsCommand ls("/");
    ls.execute(sys);
    if(ls.toString()!="DIR    dir1    0\nFILE     file1   1000") {
        std::cout<<"ls is not correct"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #5::renaming of the file test
 * @param sys
 * @pre root contain two files: <dir1,file1>
 * @post name of file1 is now file
 * @return 1->test field 0->good
 */
int renameTest1(FileSystem &sys){
    RenameCommand rm("/file1 file");
    rm.execute(sys);
    if(sys.getRootDirectory().getChildren()[1]->getName()!="file") {
        std::cout<<"changing file name failed"<<std::endl;
        return 1;
    }
    return 0;
}

/**RootTest #6::removale of the directory and file created in root
 * @param sys
 * @pre root contain two files: <dir1,file1>
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

/**RootTest #7::history check
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
    counter+=pwdTest(sys);
    counter+=makeDirTest1(sys);
    counter+=makeFileTest1(sys);
    counter+=lsTest1(sys);
    counter+=renameTest1(sys);
    counter+=rmTest1(sys);
    counter+=historyTest1(sys);
    return counter;
}

/***********************************************************
 *  tests on level #2   *
 ************************************************************/



int main(int main(int , char **)){
    int red;
    FileSystem *sys = new FileSystem();
    red+=rootTests(*sys);
    if(red>0) throw std::exception();

}


//
// Created by Guy-Amit on 11/8/2017.
//
#include "Files.h"
#include "vector"
#include <string>
#include <iostream>

using namespace std;

int red=0;

vector<string> test = {"0","1","2","3","4","5","6","7","8","9"};
vector<int> testInt;
vector<string> temp;
vector<int> tempInt;

void extractVals(vector<BaseFile*> children){
    temp.clear();
    for (int i = 0; i <children.size() ; ++i) {
        temp.push_back(children[i]->getName());
    }
}

void extractValsInt(vector<BaseFile*> children){
    tempInt.clear();
    for (int i = 0; i <children.size() ; ++i) {
        tempInt.push_back(children[i]->getSize());
    }
}
template <typename T>
bool comperVec(vector<T> v1, vector<T> v2){
    for (int i = 0; i <v1.size() ; ++i) {
        if(v1[i]!=v2[i]) return false;
    }
    return true;
}



void null_check_parent(Directory root){
    if(root.getParent()!= nullptr) red++;
}


int main(int , char **) {
     string name="root";
     Directory root(name , nullptr);


    /*****************************/
    /* Testing the root Directory*/
    /*****************************/

     null_check_parent(root);
     try {
         root.removeFile(&root);
         red++;
         std::cout <<"can't delete root"<< std::endl;
     }
    catch (std::exception) {}

     File * f =new File("hugabuga",5);
     root.addFile(f);
     root.removeFile(f->getName()); //test remove by name-root should by empty after deletion
     if(root.getChildren().size()>0) {red++; std::cout<<"the file hugabuga was not removed"<<std::endl; }
     File * g =new File("hugabuga",5);
     root.addFile(g);
     root.removeFile(g); //test remove by pointer-root should be empty after deletion
     if(root.getChildren().size()>0) {red++; std::cout<<"the file hugabuga was not removed"<<std::endl;}
    root.removeFile("guy");
    //should print "file does not exists"

    std::cout<<"END of Root checks, please do not continue if there where errors"<<std::endl;

    /*********************************************/
    /* Testing files and directories from level 1*/
    /*********************************************/

    //adding files to root
    for (int i = 0; i <10 ; ++i) {
        root.addFile(new File(std::to_string(i),i));
    }

    // /addtion check
    extractVals(root.getChildren());
    if(!comperVec(test,temp)){
        red++;
        std::cout << "files addition filed" << std::endl;
    }

    //add same file check
    root.addFile(new File("0",3));
    root.addFile(new File("1",4));
    extractVals(root.getChildren());
    if(!comperVec(test,temp)){
        red++;
        std::cout<<"you cant add the same file twice in the same directory"<<std::endl;
    }

    //creating two directories under root
    Directory emptyDir("emptyDir",&root);
    Directory dir1("dir",&root);
    root.addFile(&dir1);
    root.addFile(&emptyDir);

    //adding files to dir1
    for (int i = 0; i <10 ; ++i) {
        dir1.addFile(new File(std::to_string(i),i));
    }
    dir1.addFile(new File(std::to_string(10),10));

    root.removeFile("1"); //should remove from root and not from dir1
    test={"0","2","3","4","5","6","7","8","9","emptyDir","dir"};
    extractVals(root.getChildren());
    if(!comperVec(test,temp)) {
        red++;
        std::cout<<"the file '1' was not removed"<<std::endl;
    }


    //sort test
    dir1.addFile(new File("01",2));
    dir1.addFile(new File("02",5));
    dir1.addFile(new File("00",4));
    dir1.sortByName();
    test={"00","01","02","2","3","4","5","6","7","8","9","10"};
    extractVals(dir1.getChildren());
    if(!comperVec(test,temp)) {
        red++;
        std::cout<<"sort by name does not work"<<std::endl;
    }

    dir1.sortBySize();
    testInt ={0,2,2,3,4,4,5,5,6,7,8,9,10};
    extractVals(dir1.getChildren());
    if(!comperVec(test,temp)) {
        red++;
        std::cout<<"sort by size does not work"<<std::endl;
    }


    std::cout<<"END of level 1 checks, please do not continue if there where errors"<<std::endl;

    /*********************************************/
    /* Testing files and directories from level 2*/
    /*********************************************/

    Directory innerDir("innerDir",&dir1);
    dir1.addFile(&innerDir);
    std::string path_inner="/root/dir/innerDir";
    //comper innerDir.GetAbsolutePath to path_inner
    if(innerDir.getAbsolutePath()!=path_inner){
        red++;
        std::cout<<"absolute path is not correct"<<std::endl;
    }

    //adding new files for remove tests
    for (int i = 1; i <11 ; ++i) {
        innerDir.addFile(new File(std::to_string(i),i*20));
    }

    //remove from dapth 2
    root.removeFile("20");
    test={"10","30","40","50","60","70","80","90","100"};
    extractVals(innerDir.getChildren());
    if(!comperVec(test,temp)){
        red++;
        std::cout<<"remove at depth 2 did not soccseed";
    }

    //remove from deph 1
    dir1.removeFile("30");
    test={"10","40","50","60","70","80","90","100"};
    extractVals(dir1.getChildren());
    if(!comperVec(test,temp)){
        red++;
        std::cout<<"remove at depth 1 did not soccseed";
    }


    std::cout<<"END of level 2 checks, please do not continue if there where errors"<<std::endl;

    std::cout << "the number of red test is:"<<red<<std::endl;

}
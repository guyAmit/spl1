//
// Created by Guy-Amit on 11/8/2017.
//

#include <iostream>
#include "include/Files.h"
#include <string>
#include "vector"

using namespace std;

class Pair{
public:
    int size;
    string name;
    Pair(string name,int size):size(size),name(name){};
    string toString(){
        return "<"+name+","+to_string(size)+">";
    }
};


int counter=0;
int green=0;
int red=0;
const int Expected_red_names=21; //names 1-21
const int Expected_red_sizes=21; //sizes 22-42
std::vector<Pair*> mistakes;




void run( std::vector<File*> & f,const std::vector<int> & sizes,  vector<string> &fileNames){
    for (int i = 0; i <100 ; ++i) {
        try {
            f[i]= new File(fileNames[i],sizes[i]);
        }
        catch(std::exception){
            Pair *m= new Pair(fileNames[i],sizes[i]);
            mistakes.push_back(m);
            red++;
        }

    }
}

//int main(int , char **) {
//    std::vector<File*> f(100);
//    std::vector<int> sizes = {1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,-41,-42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99};
//    std::vector<string> filesNames ={"Aar%34en",
//                                     "Aar#34ika",
//                                     "45sf&gds",
//                                     "Aba43#gail",
//                                     "Ab343b#e,",
//                                     "Abb34ey>,",
//                                     "Abbi<",
//                                     "Abb,ie",
//                                     "Abb$y",
//                                     "Abby(e",
//                                     "Abiga'el",
//                                     "Ab3iga'il",
//                                     "Abig@ale",
//                                     "Abr&a",
//                                     "Ad!a",
//                                     "Ada(h",
//                                     "Ada3&*4line",
//                                     "Adan*",
//                                     "",
//                                     "Adda ",
//                                     "Ad di",
//                                     "Ad56dia",
//                                     "Addie",
//                                     "Addy",
//                                     "Adel",
//                                     "Adela",
//                                     "Adela34ida",
//                                     "Adelaide",
//                                     "Adele",
//                                     "Adelheid",
//                                     "Adelice",
//                                     "Adelina",
//                                     "Adelind",
//                                     "Adeline",
//                                     "Ade45lla",
//                                     "Adelle",
//                                     "Adena",
//                                     "Adey",
//                                     "Adi",
//                                     "45",
//                                     "Adina",
//                                     "444",
//                                     "Adore",
//                                     "Adoree",
//                                     "Ado44rne",
//                                     "Adrea",
//                                     "Ad90ria",
//                                     "Adriaens",
//                                     "Adrian",
//                                     "Adriana",
//                                     "Adriane",
//                                     "Adrianna",
//                                     "Adri7anne",
//                                     "Adriena",
//                                     "Adrienne",
//                                     "Aeriel",
//                                     "Aeriela",
//                                     "Aeriell",
//                                     "Afton",
//                                     "Ag",
//                                     "Aga4534ce",
//                                     "Agata",
//                                     "Agatha",
//                                     "Agathe",
//                                     "Aggi",
//                                     "Aggie",
//                                     "Aggy",
//                                     "Agna",
//                                     "Agnella",
//                                     "Agnes",
//                                     "Agnese",
//                                     "Agnesse",
//                                     "Agneta",
//                                     "Agn345ola",
//                                     "Agretha",
//                                     "Aida",
//                                     "Ai345dan",
//                                     "Aigneis",
//                                     "Aila",
//                                     "Aile",
//                                     "Ailee",
//                                     "Aileen",
//                                     "Ailene",
//                                     "Ailey",
//                                     "Aili",
//                                     "Ailina",
//                                     "Ailis",
//                                     "Ailsun",
//                                     "Ailyn",
//                                     "Aime",
//                                     "Aimee",
//                                     "Aimil",
//                                     "Aind345rea",
//                                     "Ainslee",
//                                     "Ain345sley",
//                                     "Ainslie",
//                                     "Ajay",
//                                     "Alaine",
//                                     "456576",
//                                     "Alana"};
//    run(f,sizes,filesNames);
//    std::cout<<"green:"<<100-red<<" red:"<<red<<std::endl;
//    for (int i = 0; i < mistakes.size(); ++i) {
//        std::cout<<mistakes[i]->toString()<<std::endl;
//    }
//
//}
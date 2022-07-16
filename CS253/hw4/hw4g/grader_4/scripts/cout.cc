#include "PGM.h"
#include "Alpha.h"
#include <string>
#include <ostream>
#include <iostream>
using namespace std;

int main(int, char* argv[]){
    try{
			string pub = "/s/bach/a/class/cs253/pub/input_images/";
			if (string(argv[1]) == "alpha"){ 
    		Alpha myalpha(pub+"easy.alpha");
    		myalpha.write(cout);
			}else{
				PGM mypgm(pub+"easy.pgm");
				mypgm.write(cout);
    	}
		}
    catch(string s){
        cerr<<s<<endl;
    }
    catch(char const* c){
        cerr<<c<<endl;
    }
}

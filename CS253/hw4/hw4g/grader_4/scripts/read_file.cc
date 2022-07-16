#include "PGM.h"
#include "Alpha.h"
#include <string>
#include <ostream>
#include <iostream>
using namespace std;
void read_file(string filename,string ftype){
	string pub = "/s/bach/a/class/cs253/pub/input_images/";
	if (ftype == "alpha"){
		Alpha a(pub+"hi.alpha");
		a.read(pub+filename);
		a.write(cout);
	}
	else{
		PGM p(pub+"hi.pgm");
		p.read(pub+filename);
		p.write(cout);
	}
}
int main(int, char*argv[]){
		string filename=string(argv[1]);
		string ftype=string(argv[2]);
    try{
    	read_file(filename,ftype);
    }
    catch(string s){
        cerr<< filename<<"-> ERROR: "<<s<<endl;
    }
    catch(char const* c){
        cerr<<filename <<"-> C-Style ERROR: "<<c<<endl;
    }
}

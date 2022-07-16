#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void resizeAlpha( string filename, double factor) {
  try {
		Alpha a1(filename);
		a1.resize(factor);
		//cout << filename.substr(39,filename.length()-1)<<":factor="<<factor<<": "<<'\n';
		a1.write(cout);
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void resizePGM( string filename, double factor) {
  try {
    PGM p1(filename);
		p1.resize(factor);
    
		//cout << filename.substr(39,filename.length()-1)<<":factor="<<factor<<": "<<'\n';
		p1.write(cout);
  }
  catch (string &err) {
    cerr << "ERROR: " << err << '\n';
  }
  catch (char* &err){
    cerr << "C-Style ERROR: " << err << '\n';
  }
}

int main(int, char *argv[]){
	string pub = "/s/bach/a/class/cs253/pub/input_images/";
	string filename = string(argv[1]);
	double factor = atof(argv[2]);
	if (string(argv[3]) == "alpha"){
		resizeAlpha(pub+filename, factor);
	}else{	
		resizePGM(pub+filename,factor);
	}
	return 0;
}

#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void widthAlpha( string filename) {
  try {
		Alpha a1(filename);
		cout << filename.substr(39,filename.length()-1)<<":: " << a1.width() << '\n';
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void widthPGM( string filename) {
  try {
    PGM p1(filename);
    cout << filename.substr(39,filename.length()-1)<<":: " << p1.width() << '\n';
  }
  catch (string &err) {
    cerr << "ERROR: " << err << '\n';
  }
  catch (char* &err){
    cerr << "C-Style ERROR: " << err << '\n';
  }
}

int main(int, char* argv[]){
	 string pub = "/s/bach/a/class/cs253/pub/input_images/";
	if (string(argv[2]) == "alpha"){
		widthAlpha(pub+string(argv[1]));
	//widthAlpha(pub+"simple.alpha");
	}else{
		widthPGM(pub+string(argv[1]));
	}
	//widthPGM(pub+"simple.pgm");
  //widthPGM(pub+"empty_bad.pgm");
	return 0;
}

#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void heightAlpha(string filename) {
  try {
		Alpha a1(filename);
		cout << filename.substr(39,filename.length()-1)<<":: " << a1.height() << '\n';
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void heightPGM(string filename) {
  try {
    PGM p1(filename);
    cout << filename.substr(39,filename.length()-1)<<":: " << p1.height() << '\n';
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
		heightAlpha(pub+string(argv[1]));
	}else{
		heightPGM(pub+string(argv[1]));
	}
	//	heightAlpha(pub+"simple.alpha");
	//heightPGM(pub+"simple.pgm");
  //heightPGM(pub+"empty_bad.pgm");
	return 0;
}

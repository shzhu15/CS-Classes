#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void emptyAlpha(string filename) {
  try {
		Alpha a1(filename);
		cout << filename.substr(39,filename.length()-1)<<":: " << a1.empty() << '\n';
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void emptyPGM(string filename) {
  try {
    PGM p1(filename);
    cout << filename.substr(39,filename.length()-1)<<":: " << p1.empty() << '\n';
  }
  catch (string &err) {
    cerr << "ERROR: " << err << '\n';
  }
  catch (char* &err){
    cerr << "C-Style ERROR: " << err << '\n';
  }
}

int main(int, char*argv[]){
	string pub = "/s/bach/a/class/cs253/pub/input_images/";
	if (string(argv[2]) == "alpha"){
		emptyAlpha(pub+string(argv[1]));
	//emptyAlpha(pub+"empty_comment.alpha");
	//emptyAlpha(pub+"simple.alpha");
	// PGM tests
	}else{
	emptyPGM(pub+string(argv[1]));
	//emptyPGM(pub+"simple.pgm");
	//emptyPGM(pub+"empty_bad.pgm");
	}
	return 0;
}

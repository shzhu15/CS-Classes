#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void rangeAlpha( string filename) {
  try {
		Alpha a1(filename);
		int range = a1.range();
		//cout << filename.substr(39,filename.length()-1)<<":: " << a1.range() << endl;
		cout << filename.substr(39,filename.length()-1)<<":: " << range << endl;
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void rangePGM( string filename) {
  try {
    PGM p1(filename);
		int range = p1.range();
    cout << filename.substr(39,filename.length()-1)<<":: " << range << '\n';
    //cout << filename.substr(39,filename.length()-1)<<":: " << p1.range() << '\n';
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
		rangeAlpha(pub+string(argv[1]));
	}else{
		rangePGM(pub+string(argv[1]));
	}
	//rangePGM(pub+"range1.pgm");
  //rangePGM(pub+"empty_bad.pgm");
	return 0;
}

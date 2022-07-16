#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void getpixelAlpha(string filename, int row, int col) {
  try {
		Alpha a1(filename);
		cout << filename.substr(39,filename.length()-1)<<":("<<row<<","<<col<<"): "<< a1.get(row, col) << '\n';
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void getpixelPGM(string filename, int row, int col) {
  try {
    PGM p1(filename);
    cout << filename.substr(39,filename.length()-1)<<":("<<row<<","<<col<<"): " << p1.get(row, col) << '\n';
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
		getpixelAlpha(pub+string(argv[1]),stoi(argv[3]),stoi(argv[4]));
	}else{
		getpixelPGM(pub+string(argv[1]),stoi(argv[3]),stoi(argv[4]));
	}
	//getpixelAlpha(pub+"simple.alpha", 0,0);
	//getpixelAlpha(pub+"simple.alpha",-1,-2);
	//getpixelAlpha(pub+"simple.alpha",1,2);
	//getpixelAlpha(pub+"empty.alpha",1,2);
	//getpixelAlpha(pub+"simple.alpha",100,200);
	//getpixelPGM(pub+"simple.pgm",0,0);
	//getpixelPGM(pub+"simple.pgm",3,5);
	//getpixelPGM(pub+"empty.pgm",3,5);
	//getpixelPGM(pub+"simple.pgm",-3,-5);
  //getpixelPGM(pub+"empty_bad.pgm");
	return 0;
}

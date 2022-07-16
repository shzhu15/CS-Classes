#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void rotateAlpha( string filename, int degree) {
  try {
		Alpha a1(filename);
		//for (int i=0;i<loop;++i)
		a1.rotate(degree);
		
		//cout << filename.substr(39,filename.length()-1)<<":: ";
		a1.write(cout);
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void rotatePGM( string filename, int degree) {
  try {
    PGM p1(filename);
		//for (int i=0;i<loop;++i)
		p1.rotate(degree);
    
		//cout << filename.substr(39,filename.length()-1)<<":: ";
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
	int degree = atoi(argv[2]);
	if (string(argv[3]) == "alpha"){
		rotateAlpha(pub+filename, degree);
		//mirrorAlpha(pub+"unequal.alpha",2);
		//mirrorPGM(pub+"empty1.pgm",1);
	}else{	
		rotatePGM(pub+filename,degree);
	}
	return 0;
}

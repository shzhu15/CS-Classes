#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void mirrorAlpha( string filename, int loop) {
  try {
		Alpha a1(filename);
		for (int i=0;i<loop;++i)
			a1.mirror();
		
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

void mirrorPGM( string filename, int loop) {
  try {
    PGM p1(filename);
		for (int i=0;i<loop;++i)
			p1.mirror();
    
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
	int loop = atoi(argv[2]);
	if (string(argv[3]) == "alpha"){
		mirrorAlpha(pub+filename, loop);
		//mirrorAlpha(pub+"unequal.alpha",2);
		//mirrorPGM(pub+"empty1.pgm",1);
	}else{	
		mirrorPGM(pub+filename,loop);
	}
	return 0;
}

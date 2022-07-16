#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

void writeAlpha( string filename, string outfile) {
  try {
		Alpha a1(filename);
		
		cout << filename.substr(39,filename.length()-1)<<":: " << outfile << '\n';
		a1.write(outfile);
  }
  catch (string &err) {
		cerr << "ERROR: " << err << '\n';
  }
	catch (char* &err){
		cerr << "C-Style ERROR: " << err << '\n';
	}
}

void writePGM( string filename, string outfile) {
  try {
    PGM p1(filename);
		cout << filename.substr(39,filename.length()-1)<<":: " << outfile << '\n';
		p1.write(outfile);
    
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
	string outfile ="out_"s+filename;
	if (string(argv[2]) == "alpha"){
		writeAlpha(pub+filename, outfile);
	}else{	
		writePGM(pub+filename,outfile);
	}
	return 0;
}

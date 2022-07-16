#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;
void assignment_operator(string ftype){
	string pub ="/s/bach/a/class/cs253/pub/input_images/";
	if (ftype == "alpha"){
		const Alpha a(pub+"simple.alpha");
  	Alpha a1(pub+"hi.alpha");
  	a1=a;
  	a1.write("assign.alpha");
	}else{
  	const PGM p(pub+"simple.pgm");
  	PGM p1(pub+"hi.pgm");
 		p1=p;
  	p1.write("assign.pgm"); //p1 should have simple.pgm instead of feep.pgm
	}
}

int main(int, char* argv[]) {
  try {
		assignment_operator(string(argv[1]));	
  }
  catch (string err) {
		cerr << "ERROR: " << err << '\n';
 	}
	catch (char* err){
		cerr << "C-Style Error: " << err << '\n';
	}
}

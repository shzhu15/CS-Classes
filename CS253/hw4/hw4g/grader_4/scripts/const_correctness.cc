#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  try {
		const string pub ="/s/bach/a/class/cs253/pub/input_images/";
		const string pgm_outfile="const.pgm";
		const string alpha_outfile="const.alpha";
	
	const Alpha a(pub+"simple.alpha");
	const PGM p(pub+"simple.pgm");
	p.mirror(); //p1 should have simple.pgm instead of feep.pgm
	a.mirror();
	a.write(alpha_outfile);
	p.write(pgm_outfile);	
  }
  catch (string err) {
		cerr << "ERROR: " << err << '\n';
 	}
	catch (char* err){
		cerr << "C-Style Error: " << err << '\n';
	}
}

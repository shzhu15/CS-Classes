#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

int main(int, char* argv[]) {
  try {
	string pub ="/s/bach/a/class/cs253/pub/input_images/";
	string pgm_outfile="copy_cons.pgm";
	string orig_pgm_outfile="orig_cons.pgm";
	string alpha_outfile="copy_cons.alpha";
	string orig_alpha_outfile="orig_cons.alpha";
	if (string(argv[2]) == "alpha"){
	const Alpha a(pub+string(argv[1]));
	Alpha a1(a);
	a1.mirror();
	a1.rotate(90);
	a1.resize(2);
	a1.write(alpha_outfile);
	a.write(orig_alpha_outfile);
	}else{
	const PGM p(pub+string(argv[1]));
	PGM p1(p);
	p1.mirror();
	p1.rotate(90);
	p1.resize(2);
	p1.write(pgm_outfile);
	p.write(orig_pgm_outfile);
	
	}  
	}
  catch (string err) {
		cerr << "ERROR: " << err << '\n';
 	}
	catch (char* err){
		cerr << "C-Style Error: " << err << '\n';
	}
}

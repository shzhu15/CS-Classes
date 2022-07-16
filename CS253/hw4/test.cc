#include "Alpha.h"
#include "PGM.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // try {
    //     const string pub = "/s/bach/a/class/cs253/pub/";
    //     Alpha a("beta");
    //     cout << "hi is " << a.width() << "×" << a.height() << '\n';
    //     cout << "Full-size hi\n";
    //     a.write(cout);
    //     cout << "double and rotated 90 hi\n";
    //     a.resize(2);
    //     a.rotate(90);
    //     a.write(cout);
    //     a.write("beta");
    //     PGM p1(pub+"hi.pgm");
    //     const auto p2(p1);
    //     p1.resize(.5);
    //     cout << "Full-size hi\n";
    //     p2.write(cout);
    //     cout << "Half-size hi\n";
    //     p1.write(cout);
    //     // cout << "double-size hi\n";
    //     // p1.write(cout);
    //     p1.rotate(90);
    //     cout << "rotated hi\n";
    //     p1.write(cout);
    //     cout << "mirror hi\n";
    //     p1.mirror();
    //     p1.write(cout);
    //
    //     // cout << "double-size hi\n";
    //     // p3.write(cout);
    // }
    // catch (string err) {
    //     cerr << "ERROR: " << err << '\n';
    // }
    try {
            const string pub = "/s/bach/a/class/cs253/pub/";
            Alpha a(pub+"luna.alpha");
            cout << "Luna is " << a.width() << "×" << a.height() << '\n';
            PGM p1(pub+"hi.pgm");
            const auto p2(p1);
            p1.resize(0.5);
            cout << "Full-size hi\n";
            p2.write(cout);
            cout << "Half-size hi\n";
            p1.write(cout);
        }
        catch (string err) {
            cerr << "ERROR: " << err << '\n';
        }
}

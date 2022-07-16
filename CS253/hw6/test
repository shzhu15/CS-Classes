#include "Image.h"
#include "Alpha.h"
#include "PGM.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// int main() {
//     try {
//         const string pub = "/s/bach/a/class/cs253/pub/";
//         Image *im = Image::create(pub+"luna.pgm");
//         cout << "Luna is " << im->width() << "×" << im->height() << '\n';
//         im->resize(0.5);
//         cout << "Now, Luna is " << im->width() << "×" << im->height() << '\n';
//         assert(dynamic_cast<Alpha *>(im) == nullptr);
//         assert(dynamic_cast<PGM *>(im) != nullptr);
//         delete im;
//     }
//     catch (string err) {
//         cerr << "ERROR: " << err << '\n';
//     }
// }
int main() {
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
        cout << "Half-size rotated 90 hi\n";
        p1.rotate(90);
        p1.write(cout);
        cout << "Half-size rotated 180 hi\n";
        p1.rotate(18);
        p1.write(cout);

    }
    catch (string err) {
        cerr << "ERROR: " << err << '\n';
    }
}

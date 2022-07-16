#include <iostream>

using namespace std;

// a is passed by value
// b & c are passed by reference
// d is passed by const reference

void foo(int a, int *b, int &c, const string &d) {
    a = 111;
    *b = 222;
    c = 333;
    // d = "Richard Nixon";
}

int main() {
    int alpha=1, bravo=2, charlie=3;
    string delta = "Mary Poppins";
    foo(alpha, &bravo, charlie, delta);
    cout << "alpha=" << alpha << " bravo=" << bravo
	 << " charlie=" << charlie << " delta=" << delta << '\n';
    return 0;
}

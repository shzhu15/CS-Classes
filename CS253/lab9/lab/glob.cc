#include <iostream>
#include <cstdlib>

using namespace std;

void *operator new(size_t size) {
    void *p = malloc(size);
    cout << "new(" << size << ") returns " << p << '\n';
    return p;
}

// The size_t argument for global delete is a C++14 feature.
void operator delete(void *p, size_t size) {
    cout << "delete(" << p << ", " << size << ")\n";
    free(p);
}

class Foo {
    char zot[4000];
};

int main() {
    double *p = new double;
    Foo *q = new Foo;
    delete p;
    delete q;
    return 0;
}

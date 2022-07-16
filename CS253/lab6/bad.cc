#include <fstream>
#include <iostream> 
#include <string>
#include <cassert>

using namespace std;

int main() {
    string filename = "/etc/resolv.conf";
    // A stupid line just to introduce an error:
    cout << "The 3rd character is " << filename[3] << '\n';

    ifstream in(filename);
    assert(in.is_open());

    string s;
    while (getline(in, s)) {
        string prefix = s.substr(0,6);
        if (prefix == "search")
            cout << s << '\n';
    }

    return 0;
}

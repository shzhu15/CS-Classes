#include <iostream>
#include <sstream>

using namespace std;

class Number {
  public:
    Number() = default;
    Number(const Number &) = default;
    Number(int v) : value(v) {}
    Number &operator=(int n) { value = n; return *this; }
    operator int() const { return value; }
  private:
    int value = 0;			// default value unless otherwise given
};

istream &operator>>(istream &is, Number &rhs) {
    int n;
    if(is >> n) {
        rhs = n;
        return is;  
    }
    is.clear();
    string str;
    is >> str;
    if(str ==  "three") {
        n = 3;
        rhs = n;
        return is;
    }
    if(str == "five") {
        n = 5;
        rhs = n;
        return is;
    }
    return is;
}


int main() {
    Number n = 666;
    istringstream ss("12 34 three 789 five");

    while (ss >> n)
	cout << n << ' ';
    cout << '\n';
}

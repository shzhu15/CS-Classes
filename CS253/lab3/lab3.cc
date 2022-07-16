#include <vector>
#include <string>
#include <set>
#include <iostream>
using namespace std;

int main() {

    //Read integers into vector
    vector<int> array;
    int check;
    while(cin >> check) {
        if(check == 0) {
            break;
        }
        else if(check != 0) {
            array.push_back(check);
        }
    }

    //Write integers
    for(size_t i = 0; i < array.size(); i++) {
        cout << array[i] << '\n';
    }


    //reading all char
    string read = "";
    char current = ' ';
    while(cin >> current) {
        read = read + current;
    }

    //copy into multiset
    multiset<char> ms;
    for(unsigned int i = 0; i < read.size(); i++) {
        ms.insert(read[i]);
    }

    //copy into set
    set<char> s;
    for (auto val : ms)
        s.insert(val);

    //displaying
    cout << "String size: " << read.size() << " : " << read << '\n';
    cout << "multiset size: " << ms.size() << " : ";
    for (auto val : ms)
        cout << val;
    cout << '\n';
    cout << "set size: " << s.size() << " : ";
    for (auto val : s)
        cout << val << ' ';
    cout << '\n';

}

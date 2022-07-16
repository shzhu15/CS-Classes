#include <iostream>
#include "ll.h"

using namespace std;

int main() {

    LinkedList list;
    bool done = false;

    list.initialize();

    while (!done) {
    	unsigned int i;
    	int option;

    	cout << "Choose your operation:\n"
    	     << "1. insert\t2. remove\t3. list\t   4. exit\n";

    	cin >> option;

    	switch (option) {
    	    case 1:
                cout << "Enter the number to insert\n";
                cin >> i;
                list.insert(i);
                break;
    	    case 2:
                if (list.remove(i))
                    cout << "removed " << i << '\n';
                else
                    cout << "No numbers in the list\n";
                break;
            case 3:
                // list.print();
                cout << list << '\n';
                break;
    	    case 4:
                done = true;
                break;
    	}
    }
    unsigned int a;
    while(list.remove(a));
    return 0;
}

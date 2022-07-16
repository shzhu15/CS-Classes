#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string line;
    string everything;
    string array;
    string start = "Alpha\n";
    char reading;
    int countX = 0;
    int countY = 0;
    int x = 0;

    if(argc < 1) {
      cout << "not enough arguments\n";
    }

//Reading by char
    // cin >> line ;                                                   //read in first line
    // if(line.compare(start)) {                                               //if first line equals Alpha continue
    //     while(cin >> reading) {
    //       if(reading <= 'Z' && reading >= 'A') {
    //           reading = tolower(reading);
    //       }
    //       if(reading <= 'z' && reading >= 'a') {
    //           everything += reading;
    //           x = x + 1;
    //       }
    //       if(reading == '\n') {
    //         if(countX == 0) {
    //           cout << "setting x" << x << '\n';
    //           countX = x;
    //         }
    //         if(countX != x) {
    //           cerr << "invaild input, different pixel lengths" << argv[1] << '\n';
    //         }
    //         x = 0;
    //         countY++;
    //       }
    //       if(reading != '#' && reading >= 'z' && reading <= 'a') {
    //         cerr << "invaild input" << argv[1] << '\n';
    //       }
    //     }
    //   }


    getline(cin, line);                                                               //read in first line
    if(line.length() != start.length()) {
      if(line.compare(start) != 768 || line.compare(start) != -768) {
        cerr << "invaild input in " << argv[0] << '\n';
        return -1;
      }
    }
    if(line.length() == start.length()) {
      if(line.compare(start) == 768 || line.compare(start) == -768) {                                             //if first line equals Alpha continue
        while(getline(cin, line)) {
          if(line.length() != 0) {
            countY++;
          }
          if(line.length() == 0 || line.compare("\n")) {
            countX = 0;
          }
          for(unsigned int i = 0; i < line.length()-1; i++) {
            reading = line[i];

            if(reading == '#') {
              break;
            }
            if(reading == '\n') {
              break;
            }

            if(reading <= 'Z' && reading >= 'A') {
                reading = tolower(reading);
            }
            if(reading <= 'z' && reading >= 'a') {
                everything += reading;
                x = x + 1;
            }
            if (!(isalpha(reading)) && reading != ' ' && reading != '	') {
              cerr << "invaild input in " << argv[0] << '\n';
              return -1;
            }
            // if (reading >= 'z' && reading <= 'a') {
            //   cerr << "invaild input in " << argv[0] << '\n';
            //   return -1;
            // }

          }
          if(countX == 0) {
            countX = x;
          }
          if(countX != x) {
            cerr << "invaild input, differnt pixel lengths " << argv[0] << '\n';
            return -1;
          }
          x = 0;
        }
      }
    }
    //check if string length is 0, if so print and return
    if(everything.length() == 0) {
      cout << "Alpha\n";
      return 0;
    }

    //rearranging string
    while(everything.length() > 0) {
      for(unsigned int i = everything.length() - countX; i < everything.length(); i++) {
        array += everything[i];
      }
      everything = everything.substr(0, everything.length() - countX);
    }


    //print array
    cout << "Alpha\n";
    int track = 0;
    int counter = 0;
    int place = 0;
    while(track < countX) {
      for(unsigned int i = 0; i < array.length(); i++) {
        place = i % countX;
        if(place == counter) {
          cout << array[i];
        }
      }
      counter++;
      track++;
      cout << '\n';
    }

    return 0;
}

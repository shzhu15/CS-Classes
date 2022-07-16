#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "Alpha.h"
#include "Image.h"


using namespace std;

Alpha::~Alpha() {

}

void Alpha::read(string filename) {
  string line;
  string check;
  char reading;
  string everything;
  int x = 0;
  countX = 0;
  countY = 0;
  vector<int> add;


  ifstream in(filename);                                                                    //reading file
  if(!in) {
    throw "invaild file: " + filename;
  }
  if(in) {
          // in >> line;                                               //throwaway line
          while(getline(in, line)) {
              if(line.length() == 0 || line.empty()) {
                  continue;
              }
              for(unsigned int i = 0; i < line.length(); i++) {
                reading = line[i];
                int lineLength = line.length();
                if(reading == '*' && lineLength <= countX) {
                  if(line[i+1] == '\0' || isspace(line[i+1]) || line[i+1] == '#') {
                    for(int j = i; j <= countX-1; j++) {
                        add.push_back(convertbefore(line[i-1]));
                        x = x + 1;
                    }
                    break;
                  }
                }
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
                    add.push_back(convertbefore(reading));
                    x = x + 1;
                }
                if (!(isalpha(reading)) && !isspace(reading)) {
                    throw string("invaild character in file: ") + reading;
                }
              }
              if(countX == 0) {
                countX = x;
              }
              if(countX != x) {
                throw string("invaild file, differnt pixel lengths: %d, and %d", countX, x);
              }
              if(x != 0) {
                  countY = countY + 1;
              }
              x = 0;
              // array.push_back(add);
          }
      }

  vector<vector<int>> newArray;

  int counter = 0;
  newArray.resize(countX, vector<int>( countY , 0));
  for(int i = 0; i < countY; i++) {
      for(int j = 0; j < countX; j++) {
          newArray[j][i] = add[counter];
          counter++;
      }
  }
  array = newArray;

  // for(int i = 0; i < countY; i++) {
  //     for(int j = 0; j < countX; j++) {
  //         cout << array[j][i];
  //     }
  //     cout << '\n';
  // }
}

int Alpha::convertbefore(char letter) const{
    int convertINT = 0;
    switch(letter) {
        case 'a': convertINT = 26; break;
        case 'g': convertINT = 20; break;
        case 'h': convertINT = 19; break;
        case 'i': convertINT = 18; break;
        case 'b': convertINT = 25; break;
        case 'c': convertINT = 24; break;
        case 'd': convertINT = 23; break;
        case 'e': convertINT = 22; break;
        case 'f': convertINT = 21; break;
        case 'j': convertINT = 17; break;
        case 'k': convertINT = 16; break;
        case 'l': convertINT = 15; break;
        case 'm': convertINT = 14; break;
        case 'n': convertINT = 13; break;
        case 'o': convertINT = 12; break;
        case 'p': convertINT = 11; break;
        case 'q': convertINT = 10; break;
        case 'r': convertINT = 9; break;
        case 's': convertINT = 8; break;
        case 't': convertINT = 7; break;
        case 'u': convertINT = 6; break;
        case 'v': convertINT = 5; break;
        case 'w': convertINT = 4; break;
        case 'x': convertINT = 3; break;
        case 'y': convertINT = 2; break;
        case 'z': convertINT = 1; break;
    }
    return convertINT;
}

char Alpha::convertafter(int letter) const{
    char convertCHAR = ' ';
    switch(letter) {
        case 26: convertCHAR = 'a'; break;
        case 25: convertCHAR = 'b'; break;
        case 24: convertCHAR = 'c'; break;
        case 23: convertCHAR = 'd'; break;
        case 22: convertCHAR = 'e'; break;
        case 21: convertCHAR = 'f'; break;
        case 20: convertCHAR = 'g'; break;
        case 19: convertCHAR = 'h'; break;
        case 18: convertCHAR = 'i'; break;
        case 17: convertCHAR = 'j'; break;
        case 16: convertCHAR = 'k'; break;
        case 15: convertCHAR = 'l'; break;
        case 14: convertCHAR = 'm'; break;
        case 13: convertCHAR = 'n'; break;
        case 12: convertCHAR = 'o'; break;
        case 11: convertCHAR = 'p'; break;
        case 10: convertCHAR = 'q'; break;
        case 9: convertCHAR = 'r'; break;
        case 8: convertCHAR = 's'; break;
        case 7: convertCHAR = 't'; break;
        case 6: convertCHAR = 'u'; break;
        case 5: convertCHAR = 'v'; break;
        case 4: convertCHAR = 'w'; break;
        case 3: convertCHAR = 'x'; break;
        case 2: convertCHAR = 'y'; break;
        case 1: convertCHAR = 'z'; break;
    }
    return convertCHAR;
}

bool Alpha::empty() {
    return array.empty();
}

int Alpha::height(){
    return countY;
}

int Alpha::width(){
    return countX;
}

int Alpha::range(){
    return 26;
}

int Alpha::get(int column, int row) {
    int pixel = array[column][row];
    if(pixel < 0) {
        throw string("pixel value: %d is out of range of possible pixel values", pixel);
    }
    if(pixel == 0) {
        return 0;
    }
    return pixel-1;
}

void Alpha::mirror() {
    vector<vector<int>> mirror;
    int oldi = 0;
    int oldj = 0;

    mirror.resize(countX, vector<int>( countY , 0));

    for(int i = 0; i < countY; i++) {
        for(int j = 0; j < countX; j++) {
          oldi = i;
          oldj = countX - 1 - j;
          mirror[j][i] = array[oldj][oldi];
        }
    }
    array = mirror;
}

void Alpha::rotate(int degrees) {
    vector<vector<int>> newArray;
    newArray.resize(countY, vector<int>( countX , 0));

    if(degrees % 90 != 0) {
        throw string("invaild rotation: %d\n", degrees);
    }

    for(int i = 0; i < countX; i++ ) {
        for(int j = 0; j < countY; j++ ) {
            newArray[newArray.size()-j-1][i] = array[i][j];
        }
    }
    int temp = countY;
    countY = countX;
    countX = temp;
    array = newArray;
    if(degrees / 90 != 1) {
        rotate(degrees-90);
    }
}

void Alpha::write(string filename) {
    remove(filename.c_str());
    ofstream out;
    out.open(filename, ofstream::out);
    if(!out) {
        throw string("Can't read to file\n") + filename;
    }
    out << "Alpha\n";
    for(int i = 0; i < countY; i++) {
        for(int j = 0; j < countX; j++) {
            out << convertafter(array[j][i]);
        }
        out << '\n';
    }
    out.close();
}

void Alpha::write(ostream& os) const{
        os << "Alpha\n";
        for(int i = 0; i < countY; i++) {
            for(int j = 0; j < countX; j++) {
                char add = convertafter(array[j][i]);
                os << add;
            }
            os << '\n';
        }
}

void Alpha::resize(double factor) {
    int counterX = 0;
    int counterY = 0;
    vector<vector<int>> newArray;
    if(factor == 2) {
        newArray.resize(countX*2, vector<int>( countY*2 , 0));
        for(int i = 0; i < countY; i++) {
            for(int j = 0; j < countX; j++) {
                newArray[counterX][counterY] = array[j][i];
                newArray[counterX+1][counterY] = array[j][i];
                newArray[counterX][counterY+1] = array[j][i];
                newArray[counterX+1][counterY+1] = array[j][i];
                counterX = counterX + 2;
            }
            counterY = counterY + 2;
            counterX = 0;
        }
        countX = countX*2;
        countY = countY*2;
        array = newArray;
        return;
    }
    if(factor == 0.5) {
        halve();
        return;
    }
    if(factor != 2.0 || factor != 0.5){
        throw string("invaild resize factor of %d\n", factor);
    }
}

void Alpha::halve() {
    vector<vector<int>> newArray;
    vector<int> p;
    int top = 0;
    int repX = 0;
    int repY = 0;
    int counterX = 0;
    // int counterY = 0;
    if(countX % 2 != 0) {
        repX = countX - 1;
    }
    if(countX % 2 == 0) {
        repX = countX;
    }
    if(countY % 2 != 0) {
        repY = countY - 1;
    }
    if(countY % 2 == 0) {
        repY = countY;
    }
    newArray.resize(countX/2, vector<int>( countY/2 , 0));
    for(int i = 0; i < repY; i = i + 2) {
        for(int j = 0; j < repX; j = j + 2) {
            top = array[j][i] + array[j][i+1] + array[j+1][i] + array[j+1][i+1];
            counterX++;
            p.push_back(top/4);
        }

    }
    countX = countX / 2;
    countY = countY / 2;
    int counter = 0;
    for(int i = 0; i < counterX; i++) {
        cout << p[i] << ' ';
        counter++;
        if(counter == countX) {
            cout << '\n';
            counter = 0;
        }
    }
    cout << '\n';
    for(int i = 0; i < countY; i++) {
        for(int j = 0; j < countX; j++) {
             newArray[j][i] = p[counter];
             counter++;
        }
    }


    array = newArray;
}

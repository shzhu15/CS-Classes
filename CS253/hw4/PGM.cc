#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "PGM.h"

using namespace std;

 void PGM::read(string filename) {
    string line;
    string read;
    string notgetting;
    int length = 0;
    int ylength = 0;
    int scale = 0;
    int check = 0;

    int counter = 1;

    ifstream in(filename);                                                                    //reading file
    if(!in) {
      throw "invaild file: " + filename;
    }
    if(in) {

        getline(in, line);
        while(getline(in, line)) {
            istringstream iss(line);
            if(line[0] == '#') {
                continue;
            }
            while(iss >> read) {
                if(read.compare("#") == 0) {
                    break;
                }
                if(counter == 1) {
                    counter++;
                    length = stoi(read);
                    continue;
                }
                if(counter == 2) {
                    counter++;
                    ylength = stoi(read);
                    continue;
                }
                if(counter == 3) {
                    counter++;
                    size = stoi(read);
                    break;
                }
            }
            if(counter == 4) {
                break;
            }
        }
        array.resize(length, vector<int>( ylength , 0));
        countX = length;
        countY = ylength;
        for(int i = 0; i < ylength; i++) {
            getline(in, line);
            istringstream ins(line);
            for(int j = 0; j < length; j++) {
                ins >> read;
                if(read.compare("#") == 0) {
                    break;
                }
                if(isdigit(read[0])) {
                    check = stoi(read);
                    if(check >= 0 || check <= scale) {
                        array[j][i] = check;
                        }
                    }
                }
            }
        }
}

bool PGM::empty() {
    return array.empty();
}

int PGM::height() {
    return countY;
}

int PGM::width() {
    return countX;
}

int PGM::range() {
    return size;
}

int PGM::get(int column, int row) {
    int pixel = array[column][row];
    if(pixel < 0) {
        throw string("pixel value: %d is out of range of possible pixel values", pixel);
    }
    return pixel;
}

void PGM::mirror() {
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

void PGM::rotate(int degrees) {
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

void PGM::write(string filename) {
    remove(filename.c_str());
    ofstream out;
    out.open(filename, ofstream::out);
    if(!out) {
        throw string("Can't read to file\n") + filename;

    }
    out << "P2\n";
    out << countX << " " << countY << '\n';
    out << size << '\n';
    for(int i = 0; i < countY; i++) {
        for(int j = 0; j < countX; j++) {
            if(array[j][i] > 9 && j != 0) {
                out << array[j][i] << " ";
            }
            else if(j == 0) {
                out << array[j][i] << " ";
            }
            else {
                out << " " << array[j][i] << " ";
            }
        }
        out << '\n';
    }
    out.close();
}

// void PGM::write(ostream& os) {
//         os << "P2\n";
//         os << countX << " " << countY << '\n';
//         os << range() << '\n';
//         for(int i = 0; i < countY; i++) {
//             for(int j = 0; j < countX; j++) {
//                 if(array[j][i] > 9 && j != 0) {
//                     os << array[j][i] << " ";
//                 }
//                 else if(j == 0) {
//                     os << array[j][i] << " ";
//                 }
//                 else {
//                     os << " " << array[j][i] << " ";
//                 }
//             }
//             os << '\n';
//         }
// }

void PGM::write(ostream& os) const{
        os << "P2\n";
        os << countX << " " << countY << '\n';
        os << size << '\n';
        for(int i = 0; i < countY; i++) {
            for(int j = 0; j < countX; j++) {
                if(array[j][i] > 9 && j != 0) {
                    os << array[j][i] << " ";
                }
                else if(j == 0) {
                    os << array[j][i] << " ";
                }
                else {
                    os << " " << array[j][i] << " ";
                }
            }
            os << '\n';
        }
}


void PGM::resize(double factor) {
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

void PGM::halve() {
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
    // for(int i = 0; i < counterX; i++) {
    //     cout << p[i] << ' ';
    //     counter++;
    //     if(counter == countX) {
    //         cout << '\n';
    //         counter = 0;
    //     }
    // }
    // cout << '\n';
    for(int i = 0; i < countY; i++) {
        for(int j = 0; j < countX; j++) {
             newArray[j][i] = p[counter];
             counter++;
        }
    }


    array = newArray;
}

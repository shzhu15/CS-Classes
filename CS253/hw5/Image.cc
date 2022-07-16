#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "Image.h"
#include "Alpha.h"
#include "PGM.h"


using namespace std;

Image* Image::create(string filename) {
    string cat1 = filename.substr(filename.length()-5, filename.length());
    string cat2 = filename.substr(filename.length()-3, filename.length());
    // cout << cat1 << ", " << cat2 << '\n';
    if(cat1 == "alpha") {
        Image *pointer = new Alpha(filename);
        return pointer;
    }
    if(cat2 == "pgm") {
        Image *pointer = new PGM(filename);
        // cout << "created pointer\n";
        return pointer;
    }
    else {
        throw "could not create image using file: " + filename;
    }
    return NULL;
}

Image::~Image() {

}

bool Image::empty() {
    return array.empty();
}

int Image::height(){
    return 1;
}

int Image::width(){
    return 1;
}

void Image::mirror() {
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

void Image::rotate(int degrees) {
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
void Image::resize(double factor) {
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

void Image::halve() {
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

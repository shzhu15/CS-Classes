#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readArg(string file, int* countXpointer, int* countYpointer) {
  string line;
  string start = "Alpha";
  char reading;
  string everything;
  int x = 0;

  ifstream in(file);
  if(!in) {
    cerr << "invaild file: " << file << '\n';
  }
  if(in) {
    in >> line;
    if(line.compare(start) != 0 || line != start) {
        cerr << "invaild input in " << file << '\n';
        exit(-1);
    }
  if(line.compare(start) || line == start) {                                             //if first line equals Alpha continue
  while(getline(in, line)) {
      if(line.length() != 0) {
        *countYpointer = *countYpointer + 1;
      }
      if(line.length() == 0 || line.empty() || isspace(line[0])) {
        *countXpointer = 0;
      }
      for(unsigned int i = 0; i < line.length(); i++) {
        reading = line[i];
        int lineLength = line.length();
        if(reading == '*' && lineLength <= *countXpointer) {
          if(line[i+1] == '\0' || isspace(line[i+1]) || line[i+1] == '#') {
            for(int j = i; j <= *countXpointer-1; j++) {
              everything += everything[everything.length()-1];
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
            everything += reading;
            x = x + 1;
        }
        if (!(isalpha(reading)) && !isspace(reading)) {
            cerr << "invaild character in " << file << '\n';
            exit(-1);
        }
      }
      if(*countXpointer == 0) {
        *countXpointer = x;
      }
      if(*countXpointer != x) {
        cerr << "invaild input, differnt pixel lengths " << file << '\n';
        exit(-1);
      }
      x = 0;
    }
  }
  }
  return everything;
}

string read(int* countXpointer, int* countYpointer) {
  string start = "Alpha";
  string line;
  string everything;
  char reading;
  int x = 0;

  cin >> line;
  if(line.compare(start) != 0 || line != start) {
      cerr << "invaild input in file" << '\n';
      exit(-1);
  }

  if(line.compare(start) || line == start) {                                             //if first line equals Alpha continue
    while(getline(cin, line)) {
        if(line.length() != 0) {
          *countYpointer = *countYpointer + 1;
        }
        if(line.length() == 0 || line.empty() || isspace(line[0])) {
          *countXpointer = 0;
        }
        for(unsigned int i = 0; i < line.length(); i++) {
          reading = line[i];
          int lineLength = line.length();
          if(reading == '*' && lineLength <= *countXpointer) {
            if(line[i+1] == '\0' || isspace(line[i+1]) || line[i+1] == '#') {
              for(int j = i; j <= *countXpointer-1; j++) {
                everything += everything[everything.length()-1];
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
              everything += reading;
              x = x + 1;
          }
          if (!(isalpha(reading)) && !isspace(reading)) {
              cerr << "invaild character in file" << '\n';
              exit(-1);
          }
        }
        if(*countXpointer == 0) {
          *countXpointer = x;
        }
        if(*countXpointer != x) {
          cerr << "invaild input, differnt pixel lengths " << '\n';
          exit(-1);
        }
        x = 0;
    }
  }
  return everything;
}

string mirror(string everything, int countX) {
  string mirror;
  int manage = countX - 1;
  while(everything.length() > 0) {
    for(int i = 0; i < countX; i++) {
      mirror += everything[manage-i];
    }
    // mirror += "|";
    everything = everything.substr(countX, everything.length());
  }
  everything = "";
  everything = mirror;
  return everything;
}



void rotate0(bool flag, int countX, string everything, string file) {
    if(flag == false) {
    cout << "Alpha\n";
    int track0 = 0;
    for(unsigned int i = 0; i < everything.length(); i++) {
      cout << everything[i];
      track0++;
      if(track0 == countX) {
          cout << '\n';
        track0 = 0;
      }
    }
  }
  if(flag == true) {
    ofstream out;
    out.open(file, ofstream::out);
    out << "Alpha\n";
    int track0 = 0;
    for(unsigned int i = 0; i < everything.length(); i++) {
      out << everything[i];
      track0++;
      if(track0 == countX) {
          out << '\n';
        track0 = 0;
      }
    }
    out.close();
  }
}

void rotate90(bool flag, int countX, string everything, string file) {
  string array;
  while(everything.length() > 0) {
    for(unsigned int i = everything.length() - countX; i < everything.length(); i++) {
      array += everything[i];
    }
    everything = everything.substr(0, everything.length() - countX);
  }


  //print array
  if(flag == false) {
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
  }
  if(flag == true) {
    ofstream out;
    out.open(file, ofstream::out);
    out << "Alpha\n";
    int track = 0;
    int counter = 0;
    int place = 0;
    while(track < countX) {
      for(unsigned int i = 0; i < array.length(); i++) {
        place = i % countX;
        if(place == counter) {
          out << array[i];
        }
      }
      counter++;
      track++;
      out << '\n';
    }
    out.close();
  }
}

void rotate180(bool flag, int countX, int countY, string everything, string file) {
  string array;
  string change2;
  while(everything.length() > 0) {
        for(unsigned int i = everything.length() - countX; i < everything.length(); i++) {
          array += everything[i];
        }
        everything = everything.substr(0, everything.length() - countX);
      }

      int track = 0;
      int counter = 0;
      int place = 0;
      while(track < countX) {
        for(unsigned int i = 0; i < array.length(); i++) {
          place = i % countX;
          if(place == counter) {
            change2 += array[i];
          }
        }
        counter++;
        track++;
      }
      array = "";
      while(change2.length() > 0) {
          for(unsigned int i = change2.length() - countY; i < change2.length(); i++) {
            array += change2[i];
          }
          change2 = change2.substr(0, change2.length() - countY);
      }

      //print array
      if(flag == false) {
        cout << "Alpha\n";
        track = 0;
        counter = 0;
        place = 0;
        while(track < countY) {
          for(unsigned int i = 0; i < array.length(); i++) {
            place = i % countY;
            if(place == counter) {
              cout << array[i];
            }
          }
          counter++;
          track++;
          cout << '\n';
        }
      }
      if(flag == true) {
        ofstream out;
        out.open(file, ofstream::out);
        out << "Alpha\n";
        track = 0;
        counter = 0;
        place = 0;
        while(track < countY) {
          for(unsigned int i = 0; i < array.length(); i++) {
            place = i % countY;
            if(place == counter) {
              out << array[i];
            }
          }
          counter++;
          track++;
          out << '\n';
        }
        out.close();
      }
}

void rotate270(bool flag, int countX, int countY, string everything, string file) {
  string array;
  string change2;
  string change3;
  while(everything.length() > 0) {
        for(unsigned int i = everything.length() - countX; i < everything.length(); i++) {
          array += everything[i];
        }
        everything = everything.substr(0, everything.length() - countX);
      }

      int track = 0;
      int counter = 0;
      int place = 0;
      while(track < countX) {
        for(unsigned int i = 0; i < array.length(); i++) {
          place = i % countX;
          if(place == counter) {
            change2 += array[i];
          }
        }
        counter++;
        track++;
      }
      array = "";
      while(change2.length() > 0) {
          for(unsigned int i = change2.length() - countY; i < change2.length(); i++) {
            array += change2[i];
          }
          change2 = change2.substr(0, change2.length() - countY);
      }

      track = 0;
      counter = 0;
      place = 0;
      while(track < countY) {
        for(unsigned int i = 0; i < array.length(); i++) {
          place = i % countY;
          if(place == counter) {
            change3 += array[i];
          }
        }
        counter++;
        track++;
      }
      array = "";
      while(change3.length() > 0) {
          for(unsigned int i = change3.length() - countX; i < change3.length(); i++) {
            array += change3[i];
          }
          change3 = change3.substr(0, change3.length() - countX);
      }

      //print array
      if(flag == false) {
        cout << "Alpha\n";
        track = 0;
        counter = 0;
        place = 0;
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
      }
      if(flag == true) {
        ofstream out;
        out.open(file, ofstream::out);
        out << "Alpha\n";
        track = 0;
        counter = 0;
        place = 0;
        while(track < countX) {
          for(unsigned int i = 0; i < array.length(); i++) {
            place = i % countX;
            if(place == counter) {
              out << array[i];
            }
          }
          counter++;
          track++;
          out << '\n';
        }
        out.close();
      }
    }


int main(int argc, char *argv[]) {
    string everything;
    string array;
    string rotate;
    string mirrorCheck;
    int countXpointer = 0;
    int countYpointer = 0;
    int countX = 0;
    int countY = 0;
    int rotation = 0;
    bool flag = false;

    //check if enough arguments
    if(argc < 1) {
      cerr << "not enough arguments\n";
      exit(-1);
    }


    //getting rotation
    rotate = argv[1];
    for(unsigned int i = 0; i < rotate.length(); i++) {

      rotation = stoi(rotate);
      if(rotate[i] == 'm') {
        mirrorCheck = 'm';
      }
    }
    //rotation check if valid
    switch(rotation) {
      case 0:
        break;
      case 90:
        break;
      case 180:
        break;
      case 270:
        break;
      default:
        cerr << "invaild transformation: " << argv[1] << '\n';
        exit(-1);
    }
    if(mirrorCheck != "m" && mirrorCheck.length() > 1) {
      cerr << "invaild mirror: " << argv[1] << '\n';
      exit(-1);
    }

    if(argc > 2) {
      flag = true;
      for(int arg = 2; arg < argc; arg++) {
          countXpointer = 0;
          countYpointer = 0;
          everything = readArg(argv[arg], &countXpointer, &countYpointer);
          countX = countXpointer;
          countY = countYpointer;
          if(mirrorCheck == "m" || mirrorCheck.length() > 0) {
            everything = mirror(everything, countX);
          }
          switch(rotation) {
            case 0:
              remove(argv[arg]);
              rotate0(flag, countX, everything, argv[arg]);
              break;
            case 90:
              remove(argv[arg]);
              rotate90(flag, countX, everything, argv[arg]);
              break;
            case 180:
              remove(argv[arg]);
              rotate180(flag, countX, countY, everything, argv[arg]);
              break;
            case 270:
              remove(argv[arg]);
              rotate270(flag, countX, countY, everything, argv[arg]);
              break;
            default:
              cerr << "invaild transformation: " << argv[1] << '\n';
              exit(-1);
          }
        }
        return 0;
      }
    else {
      countXpointer = 0;
      countYpointer = 0;
      everything = read(&countXpointer, &countYpointer);
      countX = countXpointer;
      countY = countYpointer;
      if(mirrorCheck == "m" || mirrorCheck.length() > 0) {
        everything = mirror(everything, countX);
      }
      switch(rotation) {
        case 0:
          rotate0(flag, countX, everything, "");
          break;
        case 90:
          rotate90(flag, countX, everything, "");
          break;
        case 180:
          rotate180(flag, countX, countY, everything, "");
          break;
        case 270:
          rotate270(flag, countX, countY, everything, "");
          break;
        default:
          cerr << "invaild transformation: " << argv[1] << '\n';
          exit(-1);
      }
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream>


bool debug = false;

using namespace std;

string readArg(string file, int* countXpointer, int* countYpointer, bool doub) {
    if(debug == true) {
        cout << "in readArg\n";
    }
  string line;
  char reading;
  string everything;
  int x = 0;

  ifstream in(file);                                                                    //reading file
  if(!in) {
    cerr << "invaild file: " << file << '\n';
  }
  if(in) {
      in >> line;                                               //throwaway line
      while(getline(in, line)) {
          if(line.length() == 0 || line.empty()) {
              continue;
          }
          for(unsigned int i = 0; i < line.length(); i++) {
            reading = line[i];
            int lineLength = line.length();
            if(reading == '*' && lineLength <= *countXpointer) {
              if(line[i+1] == '\0' || isspace(line[i+1]) || line[i+1] == '#') {
                for(int j = i; j <= *countXpointer-1; j++) {
                  everything += line[i-1];
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
                if(doub == true) {
                    everything += reading;
                    x = x + 1;
                }
            }
            if (!(isalpha(reading)) && !isspace(reading)) {
                cerr << "invaild character in file" << '\n';
                exit(-1);
            }
          }
          if(doub == true) {
              everything += everything.substr(everything.length() - x, everything.length());
              *countYpointer = *countYpointer + 1;
          }
          if(*countXpointer == 0) {
            *countXpointer = x;
          }
          if(debug == true) {
              cout << "row " << *countYpointer << " -> x is: " << x << ", countX is: " << *countXpointer << '\n';
          }
          if(*countXpointer != x) {
            cerr << "invaild input, differnt pixel lengths " << '\n';
            exit(-1);
          }
          if(x != 0) {
              *countYpointer = *countYpointer + 1;
          }
          x = 0;

      }

  }
  return everything;
}

string read(int* countXpointer, int* countYpointer, bool doub) {
  string line;
  string everything;
  char reading;
  int x = 0;

    while(getline(cin, line)) {
        if(line.length() == 0 || line.empty()) {
            continue;
        }
        for(unsigned int i = 0; i < line.length(); i++) {
          reading = line[i];
          int lineLength = line.length();
          if(reading == '*' && lineLength <= *countXpointer) {
              if(debug == true) {
                  cout << "found a *"<< '\n';
              }
            if(line[i+1] == '\0' || isspace(line[i+1]) || line[i+1] == '#') {
              for(int j = i; j <= *countXpointer-1; j++) {
                everything += line[i-1];
                x = x + 1;
              }
              if(debug == true) {
                  cout << "everything string: " << everything << '\n';
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
              if(doub == true) {
                  everything += reading;
                  x = x + 1;
              }
          }
          if (!(isalpha(reading)) && !isspace(reading)) {
              cerr << "invaild character in file" << '\n';
              exit(1);
          }
        }
        if(doub == true) {
            everything += everything.substr(everything.length() - x, everything.length());
            *countYpointer = *countYpointer + 1;
        }
        if(*countXpointer == 0) {
          *countXpointer = x;
        }
        if(debug == true) {
            cout << "row " << *countYpointer << " -> x is: " << x << ", countX is: " << *countXpointer << '\n';
        }
        if(*countXpointer != x) {
          cerr << "invaild input, differnt pixel lengths " << '\n';
          exit(1);
        }
        if(x != 0) {
            *countYpointer = *countYpointer + 1;
        }
        x = 0;

    }

  return everything;
}

vector<vector<int>> readargPGM(string file, int *countXpointer, int *countYpointer, int *size, bool doub) {
    string line;
    string read;
    int length = 0;
    int ylength = 0;
    int scale = 0;
    int check = 0;
    vector<vector<int>> array;

    ifstream in(file);                                                                    //reading file
    if(!in) {
      cerr << "invaild file: " << file << '\n';
      exit(0);
    }

    int counter = 1;
    getline(in, line);
    while(getline(in, line)) {
        istringstream iss(line);
        if(line[0] == '#') {
            continue;
        }
        if(debug == true) {
                cout << "line1: " << line << '\n';
        }
        while(iss >> read) {
            if(read.compare("#") == 0) {
                break;
            }
            if(counter == 1) {
                counter++;
                if(debug == true) {
                        cout << "first: " << read << '\n';
                }
                length = stoi(read);
                continue;
            }
            if(counter == 2) {
                counter++;
                if(debug == true) {
                        cout << "second: " << read << '\n';
                }
                ylength = stoi(read);
                continue;
            }
            if(counter == 3) {
                counter++;
                if(debug == true) {
                        cout << "size: " << read << '\n';
                }
                scale = stoi(read);
                break;
            }
        }
        if(counter == 4) {
            break;
        }
    }
    if(doub == true) {
        length = length * 2;
        ylength = ylength * 2;
        array.resize(length, vector<int>( ylength , 0));
        *countXpointer = length;
        *countYpointer = ylength;
        *size = scale;
    }
    if(doub == false) {
        array.resize(length, vector<int>( ylength , 0));
        *countXpointer = length;
        *countYpointer = ylength;
        *size = scale;
    }
    for(int i = 0; i < ylength; i++) {
        getline(in, line);
        istringstream ins(line);
        if(debug == true) {
                cout << "line: " << line << '\n';
        }
        for(int j = 0; j < length; j++) {
            ins >> read;
            if(read.compare("#") == 0) {
                break;
            }
            if(isdigit(read[0])) {
                check = stoi(read);
                if(check >= 0 || check <= scale) {
                    array[j][i] = check;
                    if(doub == true) {
                        array[j+1][i] = check;
                        j++;
                    }
                }
            }
        }
        if(doub == true) {
            for(int k = 0; k < length; k++) {
                array[k][i+1] = array[k][i];
            }
            i++;
        }
    }
    return array;
}

vector<vector<int>> readPGM(int *countXpointer, int *countYpointer, int *size, bool doub) {
    string line;
    string read;
    string notgetting;
    int length = 0;
    int ylength = 0;
    int scale = 0;
    int check = 0;
    vector<vector<int>> array;

    int counter = 1;
    getline(cin, line);
    while(getline(cin, line)) {
        istringstream iss(line);
        if(line[0] == '#') {
            continue;
        }
        if(debug == true) {
                cout << "line1: " << line << '\n';
        }
        while(iss >> read) {
            if(read.compare("#") == 0) {
                break;
            }
            if(counter == 1) {
                counter++;
                if(debug == true) {
                        cout << "first: " << read << " counter: " << counter << '\n';
                }
                length = stoi(read);
                continue;
            }
            if(counter == 2) {
                counter++;
                if(debug == true) {
                        cout << "second: " << read << " counter: " << counter << '\n';
                }
                ylength = stoi(read);
                continue;
            }
            if(counter == 3) {
                counter++;
                if(debug == true) {
                        cout << "size: " << read << " counter: " << counter<< '\n';
                }
                scale = stoi(read);
                break;
            }
        }
        if(counter == 4) {
            break;
        }
    }
    if(doub == true) {
        length = length * 2;
        ylength = ylength * 2;
        array.resize(length, vector<int>( ylength , 0));
        *countXpointer = length;
        *countYpointer = ylength;
        *size = scale;
    }
    if(doub == false) {
        array.resize(length, vector<int>( ylength , 0));
        *countXpointer = length;
        *countYpointer = ylength;
        *size = scale;
    }
    for(int i = 0; i < ylength; i++) {
        getline(cin, line);
        istringstream ins(line);
        if(debug == true) {
                cout << "line: " << line << '\n';
        }
        for(int j = 0; j < length; j++) {
            ins >> read;
            if(read.compare("#") == 0) {
                break;
            }
            if(isdigit(read[0])) {
                check = stoi(read);
                if(check >= 0 || check <= scale) {
                    array[j][i] = check;
                    if(doub == true) {
                        array[j+1][i] = check;
                        j++;
                    }
                }
            }
        }
        if(doub == true) {
            for(int k = 0; k < length; k++) {
                array[k][i+1] = array[k][i];
            }
            i++;
        }
    }
    return array;
}

string mirroring(string everything, int countX) {
  string mirror;
  int manage = countX - 1;
  while(everything.length() > 0) {
    for(int i = 0; i < countX; i++) {
      mirror += everything[manage-i];
    }
    everything = everything.substr(countX, everything.length());
  }
  everything = mirror;
  return everything;
}

vector<vector<int>> mirrorPGM(int countX, int countY, vector<vector<int>> array) {
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
    return mirror;
}

void rotate0(bool flag, int countX, string everything, string file) {
    if(flag == false) {
    cout << "Alpha\n";
    int track0 = 0;
    if(debug == true) {
        cout << "everything string: " << everything << '\n';
    }
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

string rotate90(int countX, string everything) {
  string array;
  string result;
  while(everything.length() > 0) {
    for(unsigned int i = everything.length() - countX; i < everything.length(); i++) {
      array += everything[i];
    }
    everything = everything.substr(0, everything.length() - countX);
  }
  //new string
    int track = 0;
    int counter = 0;
    int place = 0;
    while(track < countX) {
      for(unsigned int i = 0; i < array.length(); i++) {
        place = i % countX;
        if(place == counter) {
          result += array[i];
        }
      }
      if(debug == true) {
          cout << "result string: " << result << '\n';
      }
      counter++;
      track++;
    }
    return result;
}

vector<vector<int>> rotatePGM(int countX, int countY, vector<vector<int>> array) {
    vector<vector<int>> newArray;

    newArray.resize(countY, vector<int>( countX , 0));
    for (int i = 0; i < countX; i++) {
        for (int j = 0; j < countY; j++) {
            newArray[j][countX-1-i] = array[i][j];
        }
    }
    return newArray;
}

string halve(int *countX, int *countY, string everything) {
    int x = *countX / 2;
    int y = *countY / 2;
    int mean = 0;
    int top = 0;
    string result;

    while(everything.length() > 0) {
        top = everything[0] + everything[1] + everything[*countX] + everything[*countX+1];
        mean = top / 4;
        result += mean;
        everything = everything.substr(*countX, everything.length());
        if(debug == true) {
            cout << "result string: " << result << "| everything string: " << everything << '\n';
        }
    }
    if(debug == true) {
        cout << "countX: " << x << " countY: " << y << '\n';
    }
    *countX = x;
    *countY = y;
    return result;
}

vector<vector<int>> halvePGM(int *countX, int *countY, vector<vector<int>> array) {
    vector<vector<int>> result;
    int top = 0;
    int mean = 0;
    int trackX = 0;
    int trackY = 0;

    result.resize(*countX / 2, vector<int>( *countY / 2 , 0));
    for(int i = 0; i < *countY; i = i + 2) {
        for(int j = 0; j < *countX; j = j + 2) {
            top = array[j][i] + array[j][i+1] + array[j+1][i] + array[j+1][i+1];
            mean = top / 4;
            result[trackY][trackX] = mean;
            trackX++;
        }
        trackY++;
    }
    *countX = *countX / 2;
    *countY = *countY / 2;
    return result;
}

int main(int argc, char *argv[]) {
    string everything;
    string array;
    string check;

    int opt;                              //variable for option
    int countXpointer = 0;
    int countYpointer = 0;
    int countX = 0;
    int countY = 0;
    int rotation = 0;
    int size = 0;

    int countR = 0;
    int countC = 0;
    bool flag = false;
    bool mirror = false;
    bool half = false;
    bool doub = false;
    bool rotate = false;
    vector<vector<int>> vec;
    vector<vector<int>> vecR;


    //check if enough arguments
    if(argc < 1) {
      cerr << "not enough arguments\n";
      exit(-1);
    }

    //getting options
    while ((opt = getopt(argc, argv, "mhdr:")) != -1) {
        switch (opt) {
            case 'r':
                countR++;
                countC++;
                rotate = true;
                rotation = stoi(optarg);
                if(countR > 1) {
                  cerr << "invaild rotation: " << opt << '\n';
                  exit(-1);
                }
                break;
            case 'm':
                countC++;
                mirror = true;
                break;
            case 'h':
                countC++;
                half = true;
                break;
            case 'd':
                countC++;
                doub = true;
                break;
            default: /* '?' */
              cerr << "invaild option: " << opt << '\n';
              exit(-1);
            }
      }
      if(doub == true && half == true) {
        cerr << "invaild option: -d and -h " << '\n';
        exit(-1);
      }
      if(doub == false && half == false && rotate == false && mirror == false) {
        rotate = true;
        rotation = 0;
      }
    //rotation check if valid
    if(rotate == true) {
        if(rotation % 90 != 0) {
          cerr << "invaild rotation: "<< rotate << '\n';
          exit(-1);
        }
    }
    if(debug == true) {
        cout << "after options and check\n";
    }

    if(argc - countC > 1) {                                              // for changing files
        if(debug == true) {
            cout << "changing files method\n";
        }
      flag = true;
      if(debug == true) {
          cout << "argc: " << argc << " argc - countC: "<< argc - countC << '\n';
      }
      for(int arg = countC+1; arg < argc; arg++) {
          if(debug == true) {
              cout << "in loop for files\n";
          }
          ifstream in(argv[arg]);
          if(!in) {
              cout << "bad file: << argv[arg]" << '\n';
          }
          in >> check;
          in.close();
          if(debug == true) {
              cout << "check: " << check << '\n';
          }
          if(check.compare("P2") != 0 && check.compare("Alpha") != 0 ) {
              cerr << "invaild file header: \"" << check << "\" in file " << argv[arg] << '\n';
              continue;
          }
          if(check.compare("P2") == 0) {
              if(debug == true) {
                  cout << "is a pgm file\n";
              }
             vec = readargPGM(argv[arg], &countXpointer, &countYpointer, &size, doub);
             countX = countXpointer;
             countY = countYpointer;
             if(half == true) {
                 vec = halvePGM(&countX, &countY, vec);
             }
             if(mirror == true) {
                 vec = mirrorPGM(countX, countY, vec);
             }
             // vector<vector<int>> vecP;
             if(rotation != 0) {
               // for(int r = 0; r < (rotation / 90); r++) {
               //     if(r % 2 == 0) {
               //         vecR = rotatePGM(countX, countY, vec);
               //         vecP = vecR;
               //     }
               //     else if(r % 2 != 0) {
               //         vec = rotatePGM(countX, countY, vec);
               //         vecP = vec;
               //     }
               // }
               cout << "P2\n";
               cout << countX << " " << countY << '\n';
               cout << size << '\n';
               for (unsigned int x = 0; x < vec[0].size(); x++) {
                   for (int y = vec.size() - 1; y >= 0; --y) {
                       const auto& row = vec[y];
                       int value = row.at(x);
                       if(value > 9) {
                           cout << value << " ";
                       }
                       if(value < 10) {
                           cout << value << "  ";
                       }
                   }
                   cout << '\n';
               }
               continue;
            }
             cout << "P2\n";
             cout << countX << " " << countY << '\n';
             cout << size << '\n';
             for(int i = 0; i < countY; i++) {
                 for(int j = 0; j < countX; j++) {
                     if(vec[j][i] > 9 && j != 0) {
                         cout << vec[j][i] << " ";
                     }
                     else if(j == 0) {
                         cout << vec[j][i] << " ";
                     }
                     else {
                         cout << " " << vec[j][i] << " ";
                     }
                 }
                 cout << '\n';
             }
            }
          if(check.compare("Alpha") == 0) {
                  if(debug == true) {
                      cout << "is a alpha file\n";
                  }
                  countXpointer = 0;
                  countYpointer = 0;
                  everything = readArg(argv[arg], &countXpointer, &countYpointer, doub);
                  countX = countXpointer;
                  countY = countYpointer;
                  if(half == true) {
                      everything = halve(&countX, &countY, everything);
                  }
                  if(mirror == true) {
                    everything = mirroring(everything, countX);
                  }
                  if(rotation == 0) {
                    rotate0(flag, countX, everything, argv[arg]);
                  }
                  if(rotation != 0) {

                    for(int r = 0; r < rotation / 90 ; r++) {
                        int way = 0;
                        if(debug == true) {
                            cout << "way: " << way << '\n';
                        }
                        if(r % 2 == 0) {
                            way = countX;
                        }
                        else if(r % 2 != 0) {
                            way = countY;
                        }
                      everything = rotate90(way, everything);
                      if(debug == true) {
                          cout << "everything string: " << everything << '\n';
                      }
                    }
                  }
                  if(flag == true && rotation != 0) {
                      remove(argv[arg]);

                    ofstream out;
                    out.open(argv[arg], ofstream::out);
                    if(debug == true) {
                        cout << "everything string: " << everything << '\n';
                    }
                    int direction = rotation / 90;
                    if(direction % 2 == 0) {
                        direction = countX;
                    }
                    else if(direction % 2 != 0) {
                        direction = countY;
                    }
                    if(debug == true) {
                        cout << "direction: " << direction << '\n';
                    }
                    out << "Alpha\n";
                    int track0 = 0;
                    for(unsigned int i = 0; i < everything.length(); i++) {
                      out << everything[i];
                      track0++;
                      if(track0 == direction) {
                          out << '\n';
                        track0 = 0;
                      }
                    }
                    out.close();
                  }
              }
      }
      return 0;
    }
    if(debug == true) {
            cout << "using stdin\n";
    }
      countXpointer = 0;
      countYpointer = 0;

      cin >> check;
      if(check.compare("P2") == 0) {
          if(debug == true) {
                  cout << "is pgm file\n";
          }
         vec = readPGM(&countXpointer, &countYpointer, &size, doub);
         countX = countXpointer;
         countY = countYpointer;
         if(half == true) {
             vec = halvePGM(&countX, &countY, vec);
         }
         if(mirror == true) {
             vec = mirrorPGM(countX, countY, vec);
         }
         // vector<vector<int>> vecP;
         if(rotation != 0) {
           // for(int r = 0; r < (rotation / 90); r++) {
           //     if(r % 2 == 0) {
           //         vec = rotatePGM(countX, countY, vec);
           //         // vecP = vecR;
           //     }
           //     else if(r % 2 != 0) {
           //         vec = rotatePGM(countX, countY, vec);
           //         // vecP = vec;
           //     }
           // }
           cout << "P2\n";
           cout << countX << " " << countY << '\n';
           cout << size << '\n';
           for (unsigned int x = 0; x < vec[0].size(); x++) {
               for (int y = vec.size() - 1; y >= 0; --y) {
                   const auto& row = vec[y];
                   int value = row.at(x);
                   if(value > 9) {
                       cout << value << " ";
                   }
                   if(value < 10) {
                       cout << value << "  ";
                   }
               }
               cout << '\n';
           }
           return 0;
       }
        cout << "P2\n";
        cout << countX << " " << countY << '\n';
        cout << size << '\n';
        for(int i = 0; i < countY; i++) {
            for(int j = 0; j < countX; j++) {
                if(vec[j][i] > 9 && j != 0) {
                    cout << vec[j][i] << " ";
                }
                else if(j == 0) {
                    cout << vec[j][i] << " ";
                }
                else {
                    cout << " " << vec[j][i] << " ";
                }
            }
            cout << '\n';
        }
      }
      if(check.compare("Alpha") == 0) {
          if(debug == true) {
                  cout << "before reading\n";
          }
          everything = read(&countXpointer, &countYpointer, doub);
          countX = countXpointer;
          countY = countYpointer;
          if(debug == true) {
                  cout << "finish reading\n";
                  cout << "countX: " << countX << ", countY: " << countY << '\n';
          }
          if(half == true) {
              everything = halve(&countX, &countY, everything);
          }
          if(mirror == true) {
            everything = mirroring(everything, countX);
          }
          if(rotation == 0) {
            rotate0(flag, countX, everything, "");
          }
          if(rotation != 0) {
            for(int r = 0; r < (rotation / 90); r++) {
                int way = 0;
                if(r % 2 == 0) {
                    way = countX;
                }
                else if(r % 2 != 0) {
                    way = countY;
                }
                everything = rotate90(way, everything);
                if(debug == true) {
                    cout << "everything string: " << everything << '\n';
                }
            }
            int direction = rotation / 90;
            if(direction % 2 == 0) {
                direction = countX;
            }
            else if(direction % 2 != 0) {
                direction = countY;
            }
            if(debug == true) {
                cout << "direction: " << direction << '\n';
            }
            cout << "Alpha\n";
            int track0 = 0;
            for(unsigned int i = 0; i < everything.length(); i++) {
              cout << everything[i];
              track0++;
              if(track0 == direction) {
                  cout << '\n';
                track0 = 0;
              }
            }
          }
      }

    return 0;
}

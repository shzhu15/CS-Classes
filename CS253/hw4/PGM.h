#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>




class PGM {
    public:
        PGM(std::string filename) {
            read(filename);
        }
        PGM(const PGM &P2) {
            countX = P2.countX;
            countY = P2.countY;
            array = P2.array;
            size = P2.size;
        }
        // PGM& operator =(const PGM &p);
        // ~PGM();
        void read(std::string file);
        bool empty();
        int height();
        int width();
        int range();
        int get(int column, int row);
        void mirror();
        void rotate(int degrees);
        void write(std::string filename);
        void resize(double factor);
        // void write(std::ostream&);
        void write(std::ostream&) const;
        void halve();
        // friend std::ostream & operator<<(std::ostream & out);
    private:
        int countX;
        int countY;
        int size;
        std::vector<std::vector<int>> array;

};

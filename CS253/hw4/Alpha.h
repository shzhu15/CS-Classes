#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>




class Alpha {
    public:
        Alpha(std::string filename) {
            read(filename);
        }
        Alpha(const Alpha &A2) {
            countX = A2.countX;
            countY = A2.countY;
            array = A2.array;
        }
        // ~Alpha();
        void read(std::string file);
        int convertbefore(char letter) const;
        char convertafter(int letter) const;
        bool empty();
        int height();
        int width();
        int range();
        int get(int column, int row);
        void mirror();
        void rotate(int degrees);
        void write(std::string filename);
        void write(std::ostream&) const;
        void resize(double factor);
        void halve();

        // friend std::ostream & operator<<(std::ostream & out);
    private:
        int countX;
        int countY;
        std::vector<std::vector<int>> array;
};

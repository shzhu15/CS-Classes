#ifndef Included_Image_H
#define Included_Image_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


class Image {
    public:
        virtual ~Image();
        static Image* create(std::string filename);
        virtual void read(std::string file)=0;
        virtual bool empty();
        virtual int height();
        virtual int width();
        virtual int range()=0;
        virtual int get(int column, int row)=0;
        virtual void mirror();
        virtual void rotate(int degrees);
        virtual void write(std::string filename)=0;
        virtual void write(std::ostream&) const = 0;
        virtual void resize(double factor)=0;
        virtual void halve()=0;

        // friend std::ostream & operator<<(std::ostream & out);
    private:
        int countX;
        int countY;
        std::vector<std::vector<int>> array;
};

#endif

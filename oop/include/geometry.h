#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>

using namespace std;

 class Point
 {
    private :
       int x , y ;
    public :        
        Point ( int u=0, int v=0 );
        int get_x ();
        int get_y ();
        void set_x(const int x);
        void set_y(const int y);
        string as_string();
 };


 class PointArray {

    private:
        int size;
        Point* points;

    protected:
        void resize(int n);

    public:

        PointArray();

        PointArray(const Point points[], const int size);

        PointArray(const PointArray& pv);

        ~PointArray();

        void push_back(Point &p);

        void insert(int pos, Point &p);

        void remove(int pos);

        int get_size();

        void clear();

        string as_string();

        Point * get(const int pos);
 };


#endif  // GEOMETRY_H 

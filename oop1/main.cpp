#include <iostream>
#include <stdexcept>

#include "geometry.h"

using namespace std;

 

int main () {

    Point p1 (11 , 3);
    cout << "p1: " << p1.as_string() << endl;

    Point p2 (12 , 7);    
    cout << "p2: " << p2.as_string() << endl;

    Point p3 (13 , 2);
    cout << "p3: " << p3.as_string() << endl;

    Point p4 (14 , 5);
    cout << "p4: " << p4.as_string() << endl;

    Point p5 (15 , 5);
    cout << "p5: " << p5.as_string() << endl;
    
    PointArray pa;

    cout << pa.as_string() << endl;

    pa.push_back(p1);    
    cout << pa.as_string() << endl;

    pa.push_back(p2);    
    cout << pa.as_string() << endl;

    pa.push_back(p3); 
    cout << pa.as_string() << endl;

    pa.insert(0, p4); 
    cout << pa.as_string() << endl;

    pa.insert(4, p5); 
    cout << pa.as_string() << endl;

    try {
        pa.insert(-1, p5);
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    try {
        pa.insert(6, p5);
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    pa.remove(0);
    cout << pa.as_string() << endl;

    pa.remove(3);
    cout << pa.as_string() << endl;

    try {
        pa.remove(3);
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };


    Point p6 (16 , 8);
    PointArray pa2 = pa;

    pa2.push_back(p6);

    cout << "pa: " << pa.as_string() << endl;
    cout << "pa2: " << pa2.as_string() << endl;

    return 0;
};

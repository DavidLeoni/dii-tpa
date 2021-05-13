
#include <geometry.h>
#include <cmath>
 
Point::Point (const int u, const int v ) : x ( u ) , y ( v ) {};

int Point::get_x () const  { return x ; }

int Point::get_y () const { return y ; }

void Point::set_x(const int x){
    this->x = x;
}
void Point::set_y(const int y){
    this->y = y;
}

string Point::as_string() const {
    return std::to_string(this->x) + string(",") + std::to_string(this->y);
}


PointArray::PointArray(){
    this->points = NULL;
    this->size = 0;
}


PointArray::PointArray(const Point points[], const int size){
    cout << "DEBUG: PointArray points[], size constructor" << endl;
    if (size < 0){
        throw std::invalid_argument("Negative size!");
    } else if (size == 0){
        this->points = NULL;
    } else {                
        this->points = new Point[size];
        this->size = size;
        for (int i=0; i<size;i++){
            this->points[i] = points[i];
        }
    }
}

PointArray::PointArray(const PointArray& pv) : PointArray(pv.points, pv.size){            
    cout << "DEBUG: PointArray copy constructor" << endl;
}

PointArray::~PointArray(){
    cout << "DEBUG: PointArray destructor" << endl;
    delete[] points;
}

void PointArray::resize(int n){
    cout << "DEBUG: resizing from " << this->size << " to " << n << endl;
    if (n < 0){
        throw std::invalid_argument("Negative size!");
    } else if (n == 0){
        delete[] this->points;
        this->points = NULL;
    } else if (n < this->size || n > this->size) {                
        Point* old_points = this->points;
        this->points = new Point[n];
        for (int i=0; i < std::min(n, this->size); i++){
            this->points[i] = old_points[i];
        }
        this->size = n;
        delete[] old_points;
    }
}



void PointArray::push_back(const Point &p){
    cout << "DEBUG: pushing back " << p.as_string() << endl;
    resize(this->size+1);
    this->points[this->size-1] = p;            
}

void PointArray::insert(const int pos, const Point &p){
    cout << "DEBUG: inserting " << p.as_string() << " into pos " << pos << endl;
    if (pos < 0){
        throw std::invalid_argument(string("pos is negative!") + std::to_string(pos));
    }
    if (pos > this->size){
        throw std::invalid_argument(string("pos exceeds array limits: ") + std::to_string(pos));
    }
    resize(this->size+1);
    for (int i=this->size-1; i > pos ; i--){
        this->points[i] = this->points[i-1];
    }
    this->points[pos] = p;
}

void PointArray::remove(const int pos){
    cout << "DEBUG: removing pos " << pos << endl;
    if (pos < 0){
        throw std::invalid_argument(string("pos is negative!") + std::to_string(pos));
    }
    if (pos >= this->size){
        throw std::invalid_argument(string("pos exceeds array limits: ") + std::to_string(pos));
    }
    for (int i=pos; i < this->size; i++){
        this->points[i] = this->points[i+1];
    }
    resize(this->size-1);
}

int PointArray::get_size() const {
    return this->size;
}

void PointArray::clear() {
    resize(0);
}

string PointArray::as_string() const {
    string s = string("size: ") + std::to_string(this->size) + string(" points:");
    for (int i=0; i < this->size; i++){
        s += string("  ") + this->points[i].as_string();
    }
    return s;
}

Point * PointArray::get(const int pos){
    if (pos < 0){
        throw std::invalid_argument(string("pos is negative!") + std::to_string(pos));
    }
    if (pos >= this->size){
        throw std::invalid_argument(string("pos exceeds array limits: ") + std::to_string(pos));
    }
    return &(this->points[pos]);
}


const Point * PointArray::get(const int pos) const {
    if (pos < 0){
        throw std::invalid_argument(string("pos is negative!") + std::to_string(pos));
    }
    if (pos >= this->size){
        throw std::invalid_argument(string("pos exceeds array limits: ") + std::to_string(pos));
    }
    return &(this->points[pos]);
}



/** A convex polygon
 */ 
        
int Polygon::npolygons = 0;
Point Polygon::constructorPoints [4];


Point * Polygon::updateConstructorPoints (  const Point & p1,
                                            const Point & p2, 
                                            const Point & p3,
                                            const Point & p4) {
    Polygon::constructorPoints [0] = p1;
    Polygon::constructorPoints [1] = p2;
    Polygon::constructorPoints [2] = p3;
    Polygon::constructorPoints [3] = p4;

    return Polygon::constructorPoints ;
}

    
    
Polygon::Polygon(const Point points[], const int size){
    cout << "DEBUG: Polygon points[], size constructor" << endl;
    if (size < 0){
        throw std::invalid_argument("Negative size!");
    }
    if (size < 3){
        throw std::invalid_argument(string("size must be >= 3, found instead ") + std::to_string(size));
    }
    this->arr = new PointArray(points, size); // we allocate only if there is no exception risk
    Polygon::npolygons += 1;
}
        
Polygon::Polygon(const PointArray* iarr) : arr{iarr}{
    cout << "DEBUG: Polygon PointArray constructor" << endl;
    if (iarr->get_size() < 3){
        throw std::invalid_argument(string("size must be >= 3, found instead ") + std::to_string(iarr->get_size()));
    }
    Polygon::npolygons += 1;
}

Polygon::Polygon(const Polygon& pol){
    cout << "DEBUG: Polygon copy constructor" << endl;
    this->arr = new PointArray(*pol.arr);
    Polygon::npolygons += 1;
}
             

Polygon::~Polygon(){
    cout << "DEBUG: destroying polygon" << endl;            
    delete this->arr;            
    Polygon::npolygons -= 1;            
}

        

int Polygon::getNumPolygons() {
    return Polygon::npolygons;
}
        
int Polygon::getNumSides() const {
    return this->arr->get_size();
}

const PointArray* Polygon::getPoints() const {
    return this->arr;
}
    






Rectangle::Rectangle(const Point low_left, const Point up_right) : Polygon{ Polygon::updateConstructorPoints(
                                                                    low_left, 
                                                                    Point(up_right.get_x(), low_left.get_y()), 
                                                                    up_right,
                                                                    Point(low_left.get_x(), up_right.get_y())
                                                                    ), 
                                                                    4  }  {
    cout << "Rectangle(low_left, up_right) constructor" << endl;
};
  

Rectangle::Rectangle(const int x1,const int y1,const  int x2, const int y2) : Polygon{ Polygon::updateConstructorPoints(
                                                                    Point(x1,y1), 
                                                                    Point(x2,y1), 
                                                                    Point(x2,y2), 
                                                                    Point(x1,y2)
                                                                    ), 
                                                                    4  }  {
    cout << "Rectangle(x1,y1,x2,y2) constructor" << endl;
}

double Rectangle::area() const {

    int width =  abs(this->arr->get(0)->get_x() - this->arr->get(1)->get_x());
    int height = abs(this->arr->get(2)->get_y() - this->arr->get(0)->get_y());
    //cout << "width " << width << endl;
    //cout << "height " << height << endl;
    return width*height;
            
}



Triangle::Triangle(const Point p1, const Point p2, const Point p3) : Polygon{ updateConstructorPoints(
                                                                    p1, 
                                                                    p2, 
                                                                    p3            
                                                                    ), 
                                                                    3  }  {
    cout << "DEBUG: Triangle(p1, p2, p3) constructor" << endl;
};

double dist(const Point& p1, const Point& p2){
    double deltax = p1.get_x() - p2.get_x();
    double deltay = p1.get_y() - p2.get_y();

    return sqrt(pow(deltax,2) + pow(deltay,2));
}

double Triangle::area() const {
    double a = dist(*this->arr->get(0), *this->arr->get(1));    
    double b = dist(*this->arr->get(1), *this->arr->get(2));    
    double c = dist(*this->arr->get(2), *this->arr->get(0));    
    double s =  (a+b+c)/2;
    double K = sqrt( s*(s - a)*(s - b)*(s - c));

}
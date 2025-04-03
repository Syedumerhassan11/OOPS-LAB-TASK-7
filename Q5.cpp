#include <iostream>
using namespace std;

class Shape {
private:
    double area;

public:
    Shape(double a = 0) : area(a) {}

    double Area() const {
        return area;
    }

    Shape operator+(const Shape& other) const {
        return Shape(this->area + other.area);
    }

    void display() const {
        cout << "Area: " << area << endl;
    }
};

int main() {
    Shape shape1(20.5), shape2(30.2);

    cout << "Shape1 ";
    shape1.display();
    cout << "Shape2 ";
    shape2.display();

    Shape totalArea = shape1 + shape2;  // Adding areas using overloaded +
    
    cout << "Total Area after addition: ";
    totalArea.display();

    return 0;
}


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <typeinfo>
#include "geometry.h"


int main() {
  // Point a1 = {1, 1};
  // Point a2 = {1, 3};
  // Point a3 = {3, 3};
  // Point a4 = {2, 2};
  // Point a5 = {3, 1};
  // Polygon t(a1, a2, a3, a4, a5);


  // Point a1 = {1, 1};
  // Point a2 = {1, 2};
  // Point a3 = {2, 2};
  // Point a4 = {2, 1};
  // Polygon t(a1, a2, a3, a4);

  // std::cout << t.isConvex() << '\n';

  // to test Ellips with some 
  // non-trivial rotations!!!

  // double c = 0.7071;

  // Ellipse a({c, c}, {-c, -c}, 4);
  // Line d1 = a.directrices().first;
  // Line d2 = a.directrices().second;

  // std::cout << d1.A << '\n';
  // std::cout << d1.B << '\n';
  // std::cout << d1.C << '\n';
  // std::cout << d2.A << '\n';
  // std::cout << d2.B << '\n';
  // std::cout << d2.C << '\n';

  // Circle a({2, 2}, 5);

  // std::cout << a.radius() << '\n';

  // Point a = {4, 2};

  // a = Rotate(a, 30);

  // std::cout << a.x << '\n';
  // std::cout << a.y << '\n';

  // double a = 2;
  // std::cout << atan2(a, 1) << '\n';

  // Rectangle a({0, 0}, {5, 3}, 1.6666666);

  // std::cout << a.getVertices()[0] << '\n';
  // std::cout << a.getVertices()[1] << '\n';
  // std::cout << a.getVertices()[2] << '\n';
  // std::cout << a.getVertices()[3] << '\n';
  // std::cout << a.diagonals().first.A << " " << a.diagonals().first.B << " " << a.diagonals().first.C << '\n';
  // std::cout << a.diagonals().second.A << " " << a.diagonals().second.B << " " << a.diagonals().second.C << '\n';
  // Rectangle a({2, 2}, {5, 6}, 2);

  // std::cout << a.getVertices()[0].x << " " << a.getVertices()[0].y << '\n';
  // std::cout << a.getVertices()[1].x << " " << a.getVertices()[1].y << '\n';
  // std::cout << a.getVertices()[2].x << " " << a.getVertices()[2].y << '\n';
  // std::cout << a.getVertices()[3].x << " " << a.getVertices()[3].y << '\n';
  // std::cout << a.center().x << " " << a.center().y << '\n';

  // Square a({3, 2}, {7, 6});

  // std::cout << a.getVertices()[0] << '\n';
  // std::cout << a.getVertices()[1] << '\n';
  // std::cout << a.getVertices()[2] << '\n';
  // std::cout << a.getVertices()[3] << '\n';
  // std::cout << a.center() << '\n';
  // std::cout << a.inscribedCircle().center() << '\n';
  // std::cout << a.inscribedCircle().radius() << '\n';

  // Triangle t1({0, 0}, {3, 0}, {3, 4});
  // std::cout << t1.centroid() << '\n';
  // std::cout << t1.orthocenter() << '\n';
  // std::cout << t1.inscribedCircleCenter() << '\n';
  // std::cout << t1.circumscribedCircleCenter() << '\n';
  // std::cout << t1.circumscribedCircle().center() << '\n';
  // std::cout << t1.circumscribedCircle().radius() << '\n';
  // std::cout << t1.inscribedCircle().center() << '\n';
  // std::cout << t1.inscribedCircle().radius() << '\n';

  // std::vector<Shape*> a;
  
  // a.push_back(new Polygon(Point(1, 1), Point(1, 3), Point(3, 3), Point(2, 2), Point(3, 1)));
  // a.push_back(new Ellipse({1, 0}, {-1, 0}, 4));
  // a.push_back(new Circle({1, 1}, 1));
  // a.push_back(new Rectangle({2, -2}, {5, -4}, 1.5));
  // a.push_back(new Square({-2, -2}, {-3, -3}));
  // a.push_back(new Triangle({-2, 2}, {-4, 2}, {-3, 3.732050808}));
  // a.push_back(new Polygon(Point(1, 1), Point(1, 3), Point(3, 3), Point(2, 2), Point(3, 1)));
  // a.push_back(new Polygon(Point(-2, -2), Point(-2, -3), Point(-3, -3), Point(-3, -2)));

  // // for (int i = 0; i < int(a.size()); ++i) {
  // //   std::cout << a[i]->area() << '\n';
  // // }

  // std::cout << (*a[0] == *a[3]) << '\n';
  // std::cout << (*a[1] == *a[2]) << '\n';
  // std::cout << (*a[1] == *a[3]) << '\n';
  // std::cout << (*a[0] == *a[6]) << '\n';
  // std::cout << (*a[4] == *a[7]) << '\n';


  // Polygon a(Point(1, 1), Point(1, 3), Point(3, 3), Point(2, 2), Point(3, 1));

  // a.rotate({1, 0}, 90);

  // std::cout << a.getVertices()[0] << '\n';
  // std::cout << a.getVertices()[1] << '\n';
  // std::cout << a.getVertices()[2] << '\n';
  // std::cout << a.getVertices()[3] << '\n';
  // std::cout << a.getVertices()[4] << '\n';

  

}

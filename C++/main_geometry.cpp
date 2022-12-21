#include "geometry.h"
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <type_traits>
 
double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y-b.y));
}
 
bool equals(double a, double b) {
    return a-b <= 1e-6 && b-a <= 1e-6;
}
 
int testGeometry() {
 
    static_assert(std::is_abstract_v<Shape>, "Shape must be an abstract type!");
 
    const int ax = -2, ay = 2, bx = 1, by = 2,
            cx = 3, cy = -1, dx = -1, dy = -2,
            ex = 1, ey = -1, fx = 6, fy = 1;
 
    Point a(ax, ay);
    Point b(bx, by);
    Point c(cx, cy);
    Point d(dx, dy);
    Point e(ex, ey);
    if (!equals(distance(a,b), 3)) {
        std::cerr << "Test 0 (distances between points) failed.\n";
        return 1;
    }
    if (!equals(distance(a,e), 3*sqrt(2))) {
        std::cerr << "Test 1 (distances between points) failed.\n";
        return 1;
    }
 
    Line ae(a, e);
    Line ea(e, a);
    Line line1(3, 5);
    Line line2(c, -1.5);
 
    // testing destructor
    for (size_t i = 0; i < 1000000; ++i) {
        Shape* square = new Square(a, e);
        delete square;
    }
 
    Point f(fx, fy);
    Polygon abfcd(a, b, f, c, d);
    std::vector<Point> vec = {c, f, b, a, d};
    Polygon cfbad(vec);
    if (abfcd != cfbad) {
        std::cerr << "Test 2 failed. (polygons operator ==)\n";
        return 1;
    }
 
    if (!abfcd.isConvex()) {
        std::cerr << "Test 3 failed. (convexity of polygons)\n";
        return 1;
    }
 
    Polygon bfced(b, f, c, e, d);
    if (bfced.isConvex()) {
        std::cerr << "Test 4 failed. (convexity of polygons)\n";
        return 1;
    }
    Triangle abd(a, b, d);
    Polygon abfced(a,b,f,c,e,d);
    if (!equals(abd.area() + bfced.area(), abfced.area())) {
        std::cerr << "Test 5 failed. (area of polygons)\n";
        return 1;
    }
    if (abd.isSimilarTo(abfced)) {
        std::cerr << "Test 6 failed. (similarity of polygons)\n";
        return 1;
    }
    if (abfced.isCongruentTo(abd)) {
        std::cerr << "Test 7 failed. (congruency of polygons)\n";
        return 1;
    }
 
    Polygon newAbfced = abfced;
    newAbfced.rotate(Point(0,0), 50);
    newAbfced.scale(Point(0,0), 3);
    if (!equals(9 * abfced.area(), newAbfced.area())) {
        std::cerr << "Test 8 failed. (after rotation and scaling by k, area must increase in k^2 times)\n";
        return 1;
    }
    if (!equals(3 * abfced.perimeter(), newAbfced.perimeter())) {
        std::cerr << "Test 9 failed. (after rotation and scaling by k, perimeter must increase also in k times)\n";
        return 1;
    }
    auto ve = newAbfced.getVertices();
    std::reverse(ve.begin(), ve.end());
    std::rotate(ve.begin(), ve.begin() + 3, ve.end());
    newAbfced = Polygon(ve);
 
    if (!abfced.isSimilarTo(newAbfced)) {
        std::cerr << "Test 10 failed. (similarity of polygons)\n";
        return 1;
    }
 
    newAbfced.scale(a, 1. / 3);
    newAbfced.reflect(line1);
    if (!abfced.isCongruentTo(newAbfced)) {
        std::cerr << "Test 11 failed. (transformations or congruency of polygons)\n";
        return 1;
    }
    if (newAbfced == abfced) {
        std::cerr << "Test 12 failed. (transformations or equality of polygons)\n";
        return 1;
    }
 
    Point k(3, 1);
    Polygon bfkce(c, k, f, b, e);
 
    Rectangle rec_ae1 = Rectangle(e, a, 1);
    Square sq_ae = Square(a, e);
    const Shape& rec_ae1_shape = rec_ae1;
    const Shape& sq_ae_shape = sq_ae;
    if (!(rec_ae1_shape == sq_ae_shape) || rec_ae1_shape != sq_ae_shape) {
        std::cerr << "Test 12.5 failed. (Square and rectangle may be equal, even if their static type is Shape)\n";
        return 1;
    }
    Circle b3(b, 3);
    Ellipse cf5(c, f, 5);
 
    std::vector<Shape*> shapes;
    shapes.push_back(&abfced);
    shapes.push_back(&abd);
    shapes.push_back(&sq_ae);
    shapes.push_back(&rec_ae1);
    shapes.push_back(&bfkce);
    shapes.push_back(&b3);
    shapes.push_back(&cf5);
 
    if (abfced.containsPoint(Point(1, -1.1))) {
        std::cerr << "Test 13 failed. (contains point)\n";
        return 1;
    }
    if (!abd.containsPoint(Point(0,1))) {
        std::cerr << "Test 14 failed. (contains point)\n";
        return 1;
    }
 
    std::ostringstream oss;
    for (size_t i = 0; i < shapes.size(); ++i) {
        oss << shapes[i]->containsPoint(Point(2,1));
    }
    if (oss.str() != "1000110") {
        std::cerr << "Test 15 failed. (contains point)\n";
        return 1;
    }
    std::cerr << "Tests Log: Test 15 completed, now just scale shapes (without any checks)\n";
 
    for (size_t i = 0; i < shapes.size(); ++i) {
        shapes[i]->scale(Point(5,5), 0.5);
    }
    std::cerr << "Tests Log: Now starting testing ellipse (tests 16.0 - 16.2)\n";
    // Ellipse testing
    cf5 = Ellipse(f, c, 5);
    //std::cerr << "Tests Log: Now there must be only one Ellipse, with focuses (3;-1),(6;1) and dist 5\n";
    {
        double c = sqrt(13)/2;
        double a = 5./2;
        double e = c/a;
        double per = 4*a*1.34050538; // comp_ellint_2 with k=sqrt(13)/5
        double b =  a*sqrt(1-e*e);
        const double PI = 3.14159265;
        double ar = PI*a*b;
        //std::cerr << "XXXXXXXXX" << cf5.eccentricity() << ' ' << e << '\n';
        //std::cerr << "XXXXXXXXX" << cf5.perimeter() << ' ' << per << '\n';
        //std::cerr << "XXXXXXXXX" << cf5.area() << ' ' << ar << '\n';
 
        if (!equals(cf5.eccentricity(), e)) {
            std::cerr << "Test 16.0 failed. (ellipse eccentricity)\n";
            return 1;
        }
        if (!equals(cf5.perimeter(), per)) {
            std::cerr << "Test 16.1 failed. (ellipse perimeter)\n";
            return 1;
        }
        if (!equals(cf5.area(), ar)) {
            std::cerr << "Test 16.2 failed. (ellipse area)\n";
            return 1;
        }
    }
 
    // Triangle testing
    abd = Triangle(d, b, a);
    {
        bool ok = true;
        Circle incircle = abd.inscribedCircle();
        Circle circumcircle = abd.circumscribedCircle();
        Point inc = incircle.center();
        Point circ = circumcircle.center();
        double r = incircle.radius(), R = circumcircle.radius();
        // Euler theorem
        ok = equals(distance(inc, circ), sqrt(R*R - 2*R*r));
        if (!ok) {
            std::cerr << "Test 17.0 failed. (https://en.wikipedia.org/wiki/Euler's_theorem_in_geometry)\n";
            return 1;
        }
 
        Circle eulerCircle = abd.ninePointsCircle();
        Line eulerLine = abd.EulerLine();
        Point orc = abd.orthocenter();
 
        // euler circle center lies in the middle of segment between orthocenter and circumcenter
        ok = equals(distance(orc, eulerCircle.center()), distance(circ, eulerCircle.center()));
        if (!ok) {
            std::cerr << "Test 17.1 failed. (nine-point circle center)\n";
            return 1;
        }
        // Радиус окружности девяти точек равен половине радиуса описанной окружности
        ok = equals(circumcircle.radius() / 2, eulerCircle.radius());
        if (!ok) {
            std::cerr << "Test 17.2 failed. (radius of the nine-point circle is half of the circumcircle radius)\n";
            return 1;
        }
        // Описанная окружность есть образ окружности девяти точек
        // относительно гомотетии с центром в ортоцентре и коэффициентом 2
        Circle anotherCircle = eulerCircle;
        anotherCircle.scale(orc, 2);
        ok = circumcircle == anotherCircle;
        if (!ok) {
            std::cerr << "Test 17.3 failed. (homothety of nine-points circle wrt orthocenter with k=2 gives circumcircle)\n";
            return 1;
        }
 
        // прямая Эйлера проходит через центроид и центр окружности девяти точек
        ok = Line(eulerCircle.center(), abd.centroid()) == eulerLine;
 
        if (!ok) {
            std::cerr << "Test 17.4 failed. (centroid and nine-points circle center lie on Euler line)\n";
            return 1;
        }
    }
 
    return 0;
}
 
int main() {
    std::cout << testGeometry();
    return 0;
}
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

const double EPS = 1e-5;
const double PI = 3.14159265358979323846;

bool Less(const double& v1, const double& v2) {
  return v1 <= v2 - EPS;
}

bool Equal(const double& v1, const double& v2) {
  return abs(v1 - v2) < EPS;
}

struct Point {
  double x, y;
  Point(double x, double y) :
        x(x), y(y) {}
};

bool operator==(const Point& point1, const Point& point2) {
  return (point1.x == point2.x && point1.y == point2.y);
}

bool operator!=(const Point& point1, const Point& point2) {
  return !(point1 == point2);
}

Point operator+(Point point1, const Point& point2) {
  point1.x += point2.x;
  point1.y += point2.y;
  return point1;
}

Point operator-(Point point1, const Point& point2) {
  point1.x -= point2.x;
  point1.y -= point2.y;
  return point1;
}

Point operator*(Point point, double c) {
  point.x *= c;
  point.y *= c;
  return point;
}

Point operator/(Point point, double c) {
  point.x /= c;
  point.y /= c;
  return point;
}

// rotates vector clockwise on alpha radians
Point Rotate(Point vector, double alpha) {
  double x = vector.x;
  double y = vector.y;
  vector.x = x * cos(alpha) - y * sin(alpha);
  vector.y = x * sin(alpha) + y * cos(alpha);
  return vector;
}

double CrossProduct(const Point& vector1, const Point& vector2) {
  return (vector1.x * vector2.y - vector1.y * vector2.x);
}

double Length(const Point& point) {
  return sqrt(point.x * point.x + point.y * point.y);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << "(" << point.x << ", " << point.y << ")";
  return os;
}

class Line {
 private:
 public: // to delete after debug
  double A, B, C;

 public:
  Line(const Point& point1, const Point& point2) :
       A(point1.y - point2.y), B(point2.x - point1.x), C(-A * point1.x - B * point1.y) {}

  Line(const double& k, const double& b) :
       A(-k), B(1), C(-b) {};

  Line(const Point& point, const double& k) :
       A(-k), B(1), C(-A * point.x - B * point.y) {}

  friend bool operator==(const Line&, const Line&);

  double Distance(const Point& point) {
    double a = A * point.x + B * point.y + C;
    return abs(a) / sqrt(A * A + B * B);
  }

};


// be sure that lines are intersecting
// otherwise it is UB!
Point LineIntersection(const Line& line1, const Line& line2) {
  // A_1 * x + B_1 * y = -C_1
  // A_2 * x + B_2 * y = -C_2
  double delta = line1.A * line2.B - line2.A * line1.B;
  double delta_x = -line1.C * line2.B + line2.C * line1.B;
  double delta_y = -line1.A * line2.C + line2.A * line1.C;
  return {delta_x / delta, delta_y / delta};
}

bool operator==(const Line& line1, const Line& line2) {
  if (!Equal(line1.A * line2.B, line1.B * line2.A)) {
    return false;
  }
  if (!Equal(line1.B * line2.C, line1.C * line2.B)) {
    return false;
  }
  return true;
}

bool operator!=(const Line& line1, const Line& line2) {
  return !(line1 == line2);
}

class Shape {
 public:
  virtual double perimeter() const = 0;
  virtual double area() const = 0;
  virtual void rotate(const Point& center, double angle) = 0;
  // virtual bool operator!=(const Shape& another) const = 0;
};

class Polygon : public Shape {
 protected:
  std::vector<Point> vertices;
  void builder() {}
  void builder(const Point& point) { vertices.push_back(point); }

 public:
  template<typename Head, typename... Tail>
  void builder(const Head& head, const Tail&... tail) {
    vertices.push_back(head);
    builder(tail...);
  }

  template<typename... Points>
  Polygon(const Points... points) {
    builder(points...);
  }

  Polygon(std::vector<Point> points) :
          vertices(points) {}

  int verticesCount() const {
    return vertices.size();
  }

  std::vector<Point> getVertices() const {
    return vertices;
  }

  bool isConvex() {
    bool clockwise = false;
    bool counterclockwise = false;
    int n = verticesCount();
    for (int i = 0; i < n; ++i) {
      Point prev_point = vertices[(i - 1 + n) % n];
      Point cur_point = vertices[i];
      Point next_point = vertices[(i + 1) % n];
      if (CrossProduct(prev_point - cur_point, next_point - cur_point) > 0) {
        clockwise = true;
      } else {
        counterclockwise = true;
      }
      if (clockwise && counterclockwise) {
        return false;
      }
    }
    return true;
  }
  double perimeter() const final {
    double ans = 0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
      Point cur_point = vertices[i];
      Point next_point = vertices[(i + 1) % n];
      ans += Length(next_point - cur_point);
    }
    return ans;
  }

  double area() const final {
    double ans = 0;
    int n = vertices.size();
    for (int i = 1; i < n; ++i) {
      Point vector1 = vertices[i] - vertices[0];
      Point vector2 = vertices[(i + 1) % n] - vertices[0];
      ans += CrossProduct(vector1, vector2) / 2;
    }
    return abs(ans);
  }

  // rotates Polygon on angle DEGREES counterclockwise
  void rotate(const Point& center, double angle) final {
    for (int i = 0; i < int(vertices.size()); ++i) {
      Point vector = vertices[i] - center;
      vector = Rotate(vector, angle / 180 * PI);
      vertices[i] = vector + center;
    }
  }

};


class Ellipse : public Shape {
 protected:
  Point focus1, focus2;
  double a, b;

 public:
  Ellipse(const Point& focus1, const Point& focus2, double dist) :
    focus1(focus1), focus2(focus2), a(dist / 2) {
    double c = Length((focus1 - focus2) / 2);
    b = sqrt(a * a - c * c);
  }

  std::pair<Point, Point> focuses() {
    return {focus1, focus2};
  }

  Point center() {
    return (focus1 + focus2) / 2;
  }

  double c() {
    return Length((focus1 - focus2) / 2);
  }

  double eccentricity() {
    return c() / a;
  }

  std::pair<Line, Line> directrices() {
    Point d = (focus2 - focus1) / 2;
    d = d / c();
    d = d * a;
    d = d / eccentricity();
    Point normal = {(focus1 - focus2).y, (focus2 - focus1).x};
    return {Line(center() + d, center() + d + normal), Line(center() - d, center() - d + normal)};
  }

  double perimeter() const final {
    return PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
  }
  
  double area() const final {
    return PI * a * b;
  }

  // rotates Ellipse on angle DEGREES
  void rotate(const Point& center, double angle) final {
    focus1 = focus1 - center;
    focus1 = Rotate(focus1, angle / 180 * PI);
    focus1 = focus1 + center;
    focus2 = focus2 - center;
    focus2 = Rotate(focus2, angle / 180 * PI);
    focus2 = focus2 + center;
  }

  friend bool operator==(const Shape&, const Shape&);

};

class Circle : public Ellipse {
 public:
  Circle(const Point& center, double radius) :
    Ellipse(center, center, radius * 2) {}

  double radius() {
    return a;
  }
};

class Rectangle : public Polygon {
 public:
  Rectangle() = default;
  Rectangle(const Point& point1, const Point& point2, double tan) {
    if (tan < 1) {
      tan = 1 / tan;
    }
    Point d = point2 - point1;
    d = Rotate(d, atan2(tan, 1));
    d = d * cos(atan2(tan, 1 ));
    vertices = Polygon(point1, point1 + d, point2, point2 - d).getVertices();
  }

  Point center() {
    Point ans = vertices[0] + vertices[1] + vertices[2] + vertices[3];
    return ans / 4;
  }

  std::pair<Line, Line> diagonals() {
    return {Line(vertices[0], vertices[2]), Line(vertices[1], vertices[3])};
  }
};

class Square : public Rectangle {
 public:
  Square(const Point& point1, const Point& point2) {
    vertices = Rectangle(point1, point2, 1).getVertices();
  }

  Circle circumscribedCircle() {
    return Circle(center(), Length(vertices[0] - center()));
  }

  Circle inscribedCircle() {
    return Circle(center(), Length(vertices[0] - vertices[1]) / 2);
  }
};

class Triangle : public Polygon {
 public:

  Triangle(const Point& v1, const Point& v2, const Point& v3) {
    vertices = Polygon(v1, v2, v3).getVertices();
  };

  Point centroid() {
    return (vertices[0] + vertices[1] + vertices[2]) / 3;
  }

  Point orthocenter() {
    Point v1 = vertices[1] - vertices[0];
    Point normal1 = {-v1.y, v1.x};
    Line h1(vertices[2], vertices[2] + normal1);
    Point v2 = vertices[2] - vertices[1];
    Point normal2 = {-v2.y, v2.x};
    Line h2(vertices[0], vertices[0] + normal2);
    return LineIntersection(h1, h2);
  }

  Point inscribedCircleCenter() {
    Point v1 = vertices[0] - vertices[1];
    Point v2 = vertices[2] - vertices[1];
    v1 = v1 / Length(v1);
    v2 = v2 / Length(v2);
    Line b1(vertices[1], vertices[1] + v1 + v2);
    Point v3 = vertices[1] - vertices[2];
    Point v4 = vertices[0] - vertices[2];
    v3 = v3 / Length(v3);
    v4 = v4 / Length(v4);
    Line b2(vertices[2], vertices[2] + v3 + v4);
    return LineIntersection(b1, b2);
  }

  Point circumscribedCircleCenter() {
    Point m1 = (vertices[0] + vertices[1]) / 2;
    Point normal1 = {(vertices[0] - vertices[1]).y, (vertices[1] - vertices[0]).x};
    Line h1(m1, m1 + normal1);
    Point m2 = (vertices[1] + vertices[2]) / 2;
    Point normal2 = {(vertices[1] - vertices[2]).y, (vertices[2] - vertices[1]).x};
    Line h2(m2, m2 + normal2);
    return LineIntersection(h1, h2);
  }

  Circle circumscribedCircle() {
    Point cur_circle = circumscribedCircleCenter();
    return Circle(cur_circle, Length(cur_circle - vertices[0]));
  }

  Circle inscribedCircle() {
    Point cur_circle = inscribedCircleCenter();
    Line side(vertices[0], vertices[1]);
    return Circle(cur_circle, side.Distance(cur_circle));
  }

  Line EulerLine() {
    return Line(circumscribedCircleCenter(), orthocenter());
  }

  Circle ninePointsCircle() {
    Triangle temp = Triangle(
      (vertices[0] + vertices[1]) / 2,
      (vertices[1] + vertices[2]) / 2,
      (vertices[0] + vertices[2]) / 2);
    return temp.circumscribedCircle();
  }
};

bool operator==(const Shape& first, const Shape& second) {
  const Polygon* polygon1 = dynamic_cast<const Polygon*>(&first);
  const Polygon* polygon2 = dynamic_cast<const Polygon*>(&second);
  if (polygon1 != nullptr && polygon2 != nullptr) {
    if (polygon1->verticesCount() != polygon2->verticesCount()) {
      return false;
    }
    int n = polygon1->verticesCount();
    std::vector<Point> points1 = polygon1->getVertices();
    std::vector<Point> points2 = polygon2->getVertices();
    int start = -1;
    for (int i = 0; i < n; ++i) {
      if (points2[i] == points1[0]) {
        start = i;
        break;
      }
    }
    if (start == -1) {
      return false;
    }
    int cur_check = (start + 1) % n;
    int accord = 1;
    while (cur_check != start) {
      if (points1[accord] != points2[cur_check]) {
        return false;
      }
      accord = (accord + 1) % n;
      cur_check = (cur_check + 1) % n;
    }
    return true;
  }
  const Ellipse* ellipse1 = dynamic_cast<const Ellipse*>(&first);
  const Ellipse* ellipse2 = dynamic_cast<const Ellipse*>(&second);
  if (ellipse1 != nullptr && ellipse2 != nullptr) {
    std::vector<std::pair<double, double>> f1;
    std::vector<std::pair<double, double>> f2;
    f1.push_back({ellipse1->focus1.x, ellipse1->focus1.y});
    f1.push_back({ellipse1->focus2.x, ellipse1->focus2.y});
    f2.push_back({ellipse2->focus1.x, ellipse2->focus1.y});
    f2.push_back({ellipse2->focus2.x, ellipse2->focus2.y});
    std::sort(f1.begin(), f1.end());
    std::sort(f2.begin(), f2.end());
    if (f1 != f2) {
      return false;
    }
    if (ellipse1->a != ellipse2->a) {
      return false;
    }
    return true;
  }
  return false;
}

bool operator!=(const Shape& first, const Shape& second) {
  return !(first == second);
}
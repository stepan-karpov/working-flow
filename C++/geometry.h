#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

const double EPS = 1e-5;
const double kPi = acos(-1);

bool Less(const double& v1, const double& v2) {
  return v1 <= v2 - EPS;
}

bool Equal(const double& v1, const double& v2) {
  return abs(v1 - v2) < EPS;
}

bool LessOrEqual(const double& v1, const double& v2) {
  return v1 < v2 + EPS;
}

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  void rotation(const Point& center, double angle);
  void reflection(const Point& center);
};

bool operator==(const Point& point1, const Point& point2) {
  return Equal(point1.x, point2.x) && Equal(point1.y, point2.y);
}

bool operator<(const Point& point1, const Point& point2) {
  if (Equal(point1.x, point2.x)) {
    return Less(point1.y, point2.y);
  }
  return Less(point1.x, point2.x);
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

void Point::rotation(const Point& center, double angle) {
  *this = Rotate(*this, angle / 180 * kPi);
  *this = *this + center;
}

void Point::reflection(const Point& center) {
  *this = center + center - *this;
}

double CrossProduct(const Point& vector1, const Point& vector2) {
  return vector1.x * vector2.y - vector1.y * vector2.x;
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
  double A, B, C;

 public:
  Line(const Point& point1, const Point& point2)
    : A(point1.y - point2.y),
      B(point2.x - point1.x), C(-A * point1.x - B * point1.y) {}

  Line(double k, double b) : A(-k), B(1), C(-b) {};
  Line(const Point& point, const double& k) : A(-k), B(1), C(-A * point.x - B * point.y) {}

  Point normalVector() const { return {A, B}; }

  double distance(const Point& point)
    { return abs(A * point.x + B * point.y + C) / sqrt(A * A + B * B); }
  double coeffA() const { return A; }
  double coeffB() const { return B; }
  double coeffC() const { return C; }
  std::tuple<double, double, double> getCoefficients() const { return {A, B, C}; }
};


// be sure that lines are intersecting
// otherwise it is UB!
Point intersection(const Line& line1, const Line& line2) {
  // A_1 * x + B_1 * y = -C_1
  // A_2 * x + B_2 * y = -C_2
  auto [a_first, b_first, c_first] = line1.getCoefficients();
  auto [a_second, b_second, c_second] = line2.getCoefficients();
  double delta = a_first * b_second - a_second * b_first;
  double delta_x = -c_first * b_second + c_second * b_first;
  double delta_y = -a_first * c_second + a_second * c_first;
  return {delta_x / delta, delta_y / delta};
}

bool operator==(const Line& line1, const Line& line2) {
  auto [a_first, b_first, c_first] = line1.getCoefficients();
  auto [a_second, b_second, c_second] = line2.getCoefficients();
  if (!Equal(a_first * b_second, b_first * a_second)) {
    return false;
  }
  return Equal(b_first * c_second, c_first * b_second);
}

bool operator!=(const Line& line1, const Line& line2) { return !(line1 == line2); }

class Shape {
 public:
  virtual double perimeter() const = 0;
  virtual double area() const = 0;
  virtual void rotate(const Point& center, double angle) = 0;
  virtual void reflect(const Point& center) = 0;
  virtual void reflect(const Line& axis) = 0;
  virtual void scale(const Point& center, double coefficient) = 0;
  virtual ~Shape() {};
  virtual bool isSimilarTo(const Shape& another) = 0;
  virtual bool isCongruentTo(const Shape& another) = 0;
  virtual bool containsPoint(const Point& point) = 0;
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
  Polygon(const Points... points) { builder(points...); }
  Polygon(std::vector<Point> points) : vertices(points) {}

  int verticesCount() const { return vertices.size(); }
  std::vector<Point> getVertices() const { return vertices; }
  std::vector<Point> getDiagonals() const;

  bool isConvex();
  double perimeter() const final;
  double area() const final;
  // rotates Polygon on angle DEGREES counterclockwise
  void rotate(const Point& center, double angle) final;
  // reflects Polygon relatively to the point center
  void reflect(const Point& center) final;
  void reflect(const Line& axis) final;
  void scale(const Point& center, double coefficient) final;
  bool checkAccordance(const std::vector<Point>& points1, const std::vector<Point>& points2);
  bool isSimilarTo(const Shape& another) final;
  std::vector<double> GetLengths(std::vector<Point> points);
  bool isCongruentTo(const Shape& another) final;
  bool containsPoint(const Point& point) final;
  bool hasAccordance(const std::vector<Point>& points1,
                    const std::vector<Point>& points2, size_t n,
                    double rotation_angle, double coeff, size_t i, size_t j);
};

std::vector<Point> Polygon::getDiagonals() const {
  std::vector<Point> diagonals;
  size_t n = vertices.size();
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 2; j < n; ++j) {
      Point diagonal = vertices[i] - vertices[j];
      if (diagonal.x < 0) {
        diagonal = diagonal * (-1);
      }
      diagonals.push_back(diagonal);
    }
  }
  return diagonals;
}

bool Polygon::isConvex() {
  bool clockwise = false;
  bool counterclockwise = false;
  size_t n = verticesCount();
  for (size_t i = 0; i < n; ++i) {
    Point previous = vertices[(i - 1 + n) % n];
    Point current = vertices[i];
    Point next = vertices[(i + 1) % n];
    if (CrossProduct(previous - current, next - current) > 0) {
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

double Polygon::perimeter() const {
  double answer = 0;
  size_t n = vertices.size();
  for (size_t i = 0; i < n; ++i) {
    Point current = vertices[i];
    Point next = vertices[(i + 1) % n];
    answer += Length(next - current);
  }
  return answer;
}

double Polygon::area() const {
  double answer = 0;
  size_t n = vertices.size();
  for (size_t i = 1; i < n; ++i) {
    Point current = vertices[i] - vertices[0];
    Point next = vertices[(i + 1) % n] - vertices[0];
    answer += CrossProduct(current, next) / 2;
  }
  return abs(answer);
}

void Polygon::rotate(const Point& center, double angle) {
  for (size_t i = 0; i < vertices.size(); ++i) {
    vertices[i].rotation(center, angle);
  }
}

void Polygon::reflect(const Point& center) {
  for (size_t i = 0; i < vertices.size(); ++i) {
    vertices[i].reflection(center);
  }
}

void Polygon::reflect(const Line& axis) {
  for (size_t i = 0; i < vertices.size(); ++i) {
    double x = vertices[i].x;
    double y = vertices[i].y;
    auto [A, B, C] = axis.getCoefficients();
    double distance = A * x + B * y + C;
    distance = -distance / (A * A + B * B);
    distance *= 2;
    vertices[i] = vertices[i] + axis.normalVector() * distance;
  }
}

void Polygon::scale(const Point& center, double coefficient) {
  for (size_t i = 0; i < vertices.size(); ++i) {
    vertices[i] = ((vertices[i] - center) * coefficient) + center;
  }
}

bool Polygon::hasAccordance(const std::vector<Point>& points1,
                    const std::vector<Point>& points2, size_t n,
                    double rotation_angle,
                    double coeff,
                    size_t i, size_t j) {
  size_t pointer1 = (i + 1) % n;
  size_t pointer2 = (j + 1) % n;
  while (pointer1 != i) {
    Point vector = points1[pointer1];
    Point accordance = points2[pointer2];
    vector = Rotate(vector, rotation_angle);
    vector = vector / coeff;
    if (vector != accordance) {
      return false;
    }
    pointer1 = (pointer1 + 1) % n;
    pointer2 = (pointer2 + 1) % n;
  }
  return true;
}

bool Polygon::checkAccordance(const std::vector<Point>& points1, const std::vector<Point>& points2) {
  size_t n = points1.size();
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j < n; ++j) {
      double rotation_angle = atan2(points2[j].y, points2[j].x);
      rotation_angle -= atan2(points1[i].y, points1[i].x);
      double coeff = Length(points1[i]) / Length(points2[j]);
      if (hasAccordance(points1, points2, n, rotation_angle, coeff, i, j)) {
        return true;
      }
    }
  }
  return false;
}

bool Polygon::isSimilarTo(const Shape& another) {
  const Polygon* polygon2 = dynamic_cast<const Polygon*>(&another);
  if (polygon2 == nullptr) {
    return false;
  }
  if (verticesCount() != polygon2->verticesCount()) {
    return false;
  }
  const std::vector<Point>& diagonals1 = getVertices();
  std::vector<Point> diagonals2 = polygon2->getVertices();
  if (checkAccordance(diagonals1, diagonals2)) {
    return true;
  }
  std::reverse(diagonals2.begin(), diagonals2.end());
  return checkAccordance(diagonals1, diagonals2);
}

std::vector<double> Polygon::GetLengths(std::vector<Point> points) {
  std::vector<double> answer;
  for (size_t i = 0; i < points.size(); ++i) {
    for (size_t j = i + 1; j < points.size(); ++j) {
      answer.push_back(Length(points[i] - points[j]));
    }
  }
  return answer;
}

bool Polygon::isCongruentTo(const Shape& another) {
  const Polygon* polygon2 = dynamic_cast<const Polygon*>(&another);
  if (polygon2 == nullptr) {
    return false;
  }
  if (verticesCount() != polygon2->verticesCount()) {
    return false;
  }
  std::vector<double> key_points1 = GetLengths(getVertices());
  std::vector<double> key_points2 = GetLengths(polygon2->getVertices());
  std::sort(key_points1.begin(), key_points1.end());
  std::sort(key_points2.begin(), key_points2.end());
  for (size_t i = 0; i < key_points1.size(); ++i) {
    if (!Equal(key_points1[i], key_points2[i])) {
      return false;
    }
  }
  return true;
}

bool Polygon::containsPoint(const Point& point) {
  const Polygon* polygon = dynamic_cast<const Polygon*>(this);
  if (polygon == nullptr) {
    return false;
  }
  size_t intersections = 0;
  Line line(point, 0.2); // random line
  size_t n = polygon->verticesCount();
  std::vector<Point> vertices = polygon->getVertices();
  for (size_t i = 0; i < n; ++i) {
    Point current = vertices[i];
    Point next = vertices[(i + 1) % n];
    Line side(current, next);
    Point intersection_point = intersection(side, line);
    if (LessOrEqual(std::min(current.x, next.x), intersection_point.x) &&
        LessOrEqual(intersection_point.x, std::max(current.x, next.x)) &&
        Less(intersection_point.x, point.x)) {
          ++intersections;
    }
  }
  return intersections % 2 == 1;
}

class Ellipse : public Shape {
 protected:
  Point focus1, focus2;
  double a, b;

 public:
  Ellipse(const Point& focus1, const Point& focus2, double dist);

  std::pair<Point, Point> focuses() const { return {focus1, focus2}; }
  Point center() { return (focus1 + focus2) / 2; }
  double c() const { return Length((focus1 - focus2) / 2); }
  double getA() const { return a; }
  double eccentricity() const { return c() / a; }

  std::pair<Line, Line> directrices();
  double perimeter() const final
      { return kPi * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b))); }
  double area() const final { return kPi * a * b; }

  // rotates Ellipse on angle DEGREES
  void rotate(const Point& center, double angle) final;
  void reflect(const Point& center) final;
  void reflect(const Line& axis) final;
  void scale(const Point& center, double coefficient) final;
  bool isSimilarTo(const Shape& another) final;
  bool isCongruentTo(const Shape& another) final;
  bool containsPoint(const Point& point) final;
  friend bool operator==(const Shape&, const Shape&);
};

Ellipse::Ellipse(const Point& focus1, const Point& focus2, double dist)
  : focus1(focus1), focus2(focus2), a(dist / 2) {
  double c = Length((focus1 - focus2) / 2);
  b = sqrt(a * a - c * c);
}

std::pair<Line, Line> Ellipse::directrices() {
  Point d = (focus2 - focus1) / 2;
  d = d / c();
  d = d * a;
  d = d / eccentricity();
  Point normal = {(focus1 - focus2).y, (focus2 - focus1).x};
  return {Line(center() + d, center() + d + normal), Line(center() - d, center() - d + normal)};
}

void Ellipse::rotate(const Point& center, double angle) {
  focus1.rotation(center, angle / 180 * kPi);
  focus2.rotation(center, angle / 180 * kPi);
}

void Ellipse::reflect(const Point& center) {
  focus1.reflection(center);
  focus2.reflection(center);
}

Point ReflectRelativelyToLine(const Line& axis, Point to_reflect) {
  auto [A, B, C] = axis.getCoefficients();
  double distance = A * to_reflect.x + B * to_reflect.y + C;
  distance = -distance / (A * A + B * B);
  distance *= 2;
  return to_reflect + axis.normalVector() * distance;
}

Point ScaleVector(const Point& center, Point to_scale, double coefficient) {
  to_scale = to_scale - center;
  to_scale = to_scale * coefficient;
  to_scale = to_scale + center;
  return to_scale;
}

void Ellipse::reflect(const Line& axis) {
  focus1 = ReflectRelativelyToLine(axis, focus1);
  focus2 = ReflectRelativelyToLine(axis, focus2);
}

void Ellipse::scale(const Point& center, double coefficient) {
  focus1 = ScaleVector(center, focus1, coefficient);
  focus2 = ScaleVector(center, focus2, coefficient);
  a = a * coefficient;
  b = b * coefficient;
}

bool Ellipse::isSimilarTo(const Shape& another) {
  const Ellipse* ellipse2 = dynamic_cast<const Ellipse*>(&another);
  if (ellipse2 == nullptr) { return false; }
  return Equal(eccentricity(), ellipse2->eccentricity());
}

bool Ellipse::isCongruentTo(const Shape& another) {
  const Ellipse* ellipse2 = dynamic_cast<const Ellipse*>(&another);
  if (ellipse2 == nullptr) { return false; }
  auto [f1, f2] = focuses();
  auto [another_f1, another_f2] = ellipse2->focuses();
  if (!Equal(Length(f1 - f2), Length(another_f1 - another_f2))) {
    return false;
  }
  return Equal(eccentricity(), ellipse2->eccentricity());
}

bool Ellipse::containsPoint(const Point& point) {
  auto [f1, f2] = focuses();
  double dist = Length(point - f1);
  dist += Length(point - f2);
  return Less(dist, getA());
}

class Circle : public Ellipse {
 public:
  Circle(const Point& center, double radius) : Ellipse(center, center, radius * 2) {}
  double radius() { return a; }
};

class Polygon : public Polygon {
 public:
  Polygon() = default;
  Polygon(const Point& point1, const Point& point2, double tan);
  Point center() { return (vertices[0] + vertices[1] + vertices[2] + vertices[3]) / 4; }
  std::pair<Line, Line> diagonals()
    { return {Line(vertices[0], vertices[2]), Line(vertices[1], vertices[3])}; }
};

Polygon::Polygon(const Point& point1, const Point& point2, double tan) {
  if (tan < 1) { tan = 1 / tan; }
  Point d = point2 - point1;
  d = Rotate(d, atan2(tan, 1));
  d = d * cos(atan2(tan, 1 ));
  vertices = Polygon(point1, point1 + d, point2, point2 - d).getVertices();
}

class Square : public Polygon {
 public:
  Square(const Point& point1, const Point& point2)
    { vertices = Polygon(point1, point2, 1).getVertices(); }
  Circle circumscribedCircle() { return Circle(center(), Length(vertices[0] - center())); }
  Circle inscribedCircle() { return Circle(center(), Length(vertices[0] - vertices[1]) / 2); }
};

class Triangle : public Polygon {
 public:
  Triangle(const Point& v1, const Point& v2, const Point& v3)
    { vertices = Polygon(v1, v2, v3).getVertices(); }
  Point centroid() { return (vertices[0] + vertices[1] + vertices[2]) / 3; }
  Point orthocenter();
  Point inscribedCircleCenter();
  Point circumscribedCircleCenter();
  Circle circumscribedCircle();
  Circle inscribedCircle();
  Line EulerLine() { return Line(circumscribedCircleCenter(), orthocenter()); }
  Circle ninePointsCircle();
};

Line findHeight(const Point& a, const Point& b, const Point& c) {
  Point middle = a - b;
  Point normal1 = {-middle.y, middle.x};
  return Line(c, c + normal1);
}

Point Triangle::orthocenter() {
  Line h1 = findHeight(vertices[0], vertices[1], vertices[2]);
  Line h2 = findHeight(vertices[2], vertices[1], vertices[0]);
  return intersection(h1, h2);
}

Line findBisector(const Point& a, const Point& b, const Point& c) {
  Point v1 = a - b;
  Point v2 = c - b;
  v1 = v1 / Length(v1);
  v2 = v2 / Length(v2);
  return Line(b, b + v1 + v2);
}

Point Triangle::inscribedCircleCenter() {
  Line b1 = findBisector(vertices[0], vertices[1], vertices[2]);
  Line b2 = findBisector(vertices[1], vertices[2], vertices[0]);
  return intersection(b1, b2);
}

Line medianPerpendicular(const Point& a, const Point& b) {
  Point m1 = (a + b) / 2;
  Point normal1 = {(a - b).y, (b - a).x};
  return Line(m1, m1 + normal1);
}

Point Triangle::circumscribedCircleCenter() {
  Line h1 = medianPerpendicular(vertices[0], vertices[1]);
  Line h2 = medianPerpendicular(vertices[1], vertices[2]);
  return intersection(h1, h2);
}

Circle Triangle::circumscribedCircle() {
  Point circle = circumscribedCircleCenter();
  return Circle(circle, Length(circle - vertices[0]));
}

Circle Triangle::inscribedCircle() {
  Point circle = inscribedCircleCenter();
  Line side(vertices[0], vertices[1]);
  return Circle(circle, side.distance(circle));
}

Circle Triangle::ninePointsCircle() {
  Triangle temp = Triangle(
    (vertices[0] + vertices[1]) / 2,
    (vertices[1] + vertices[2]) / 2,
    (vertices[0] + vertices[2]) / 2);
  return temp.circumscribedCircle();
}

bool accordanceCheck(std::vector<Point>& points1, std::vector<Point>& points2, size_t n, int start) {
  int check = (start + 1) % n;
  int accordance = 1;
  while (check != start) {
    if (points1[accordance] != points2[check]) {
      return false;
    }
    accordance = (accordance + 1) % n;
    check = (check + 1) % n;
  }
  return true;
}

bool isShifted(std::vector<Point>& points1, std::vector<Point>& points2, size_t n, int start) {
  if (accordanceCheck(points1, points2, n, start)) { return true; }
  int check = (start - 1 + n) % n;
  int accordance = 1;
  while (check != start) {
    if (points1[accordance] != points2[check]) {
      return false;
    }
    accordance = (accordance + 1) % n;
    check = (check - 1 + n) % n;
  }
  return true;
}

bool areEqual(const Polygon* polygon1, const Polygon* polygon2) {
  if (polygon1 == nullptr) { return false; }
  if (polygon2 == nullptr) { return false; }
  if (polygon1->verticesCount() != polygon2->verticesCount()) {
    return false;
  }
  size_t n = polygon1->verticesCount();
  std::vector<Point> points1 = polygon1->getVertices();
  std::vector<Point> points2 = polygon2->getVertices();
  int start = -1;
  for (size_t i = 0; i < n; ++i) {
    if (points2[i] == points1[0]) {
      start = i;
      break;
    }
  }
  if (start == -1) { return false; }
  return isShifted(points1, points2, n, start);
}

bool areEqual(const Ellipse* ellipse1, const Ellipse* ellipse2) {
  if (ellipse1 == nullptr) { return false; }
  if (ellipse2 == nullptr) { return false; }
  auto [focus1_first, focus2_first] = ellipse1->focuses();
  auto [focus1_second, focus2_second] = ellipse2->focuses();
  std::vector<Point> f1 = {focus1_first, focus2_first};
  std::vector<Point> f2 = {focus1_second, focus2_second};
  
  auto comparator = [](auto& p1, auto& p2) {
    if (p1.x == p2.x) {
      return p1.y < p2.y;
    }
    return p1.x < p2.x;
  };

  std::sort(f1.begin(), f1.end(), comparator);
  std::sort(f2.begin(), f2.end(), comparator);
  if (f1 != f2) { return false; }
  return ellipse1->getA() == ellipse2->getA();
}

bool operator==(const Shape& first, const Shape& second) {
  const Polygon* polygon1 = dynamic_cast<const Polygon*>(&first);
  const Polygon* polygon2 = dynamic_cast<const Polygon*>(&second);
  const Ellipse* ellipse1 = dynamic_cast<const Ellipse*>(&first);
  const Ellipse* ellipse2 = dynamic_cast<const Ellipse*>(&second);
  if (areEqual(polygon1, polygon2)) {
    return true;
  }
  return areEqual(ellipse1, ellipse2);
}

bool operator!=(const Shape& first, const Shape& second) {
  return !(first == second);
}
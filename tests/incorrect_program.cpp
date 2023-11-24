#include <math.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using Ld = long double;

const int kPrecision = 10;
const Ld kEps = 1e-5;

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Vector {
  Ld x_projection = 0, y_projection = 0;
  Vector() = default;
  Vector(Ld xx, Ld yy) : x_projection(xx), y_projection(yy) {}

  Ld Length() const {
    return sqrt(x_projection * x_projection + y_projection * y_projection);
  }
};

Ld operator*(const Vector& first, const Vector& second) {
  return first.x_projection * second.x_projection +
         first.y_projection * second.y_projection;
}

Ld operator^(const Vector& first, const Vector& second) {
  return first.x_projection * second.y_projection -
         first.y_projection * second.x_projection;
}

Ld operator||(const Vector& first, const Vector& second) {
  Vector diff(first.x_projection - second.x_projection,
              first.y_projection - second.y_projection);
  return diff.Length();
}

Vector operator+(const Vector& first, const Vector& second) {
  return Vector(first.x_projection + second.x_projection,
                first.y_projection + second.y_projection);
}

Vector operator-(const Vector& first, const Vector& second) {
  return Vector(first.x_projection - second.x_projection,
                first.y_projection - second.y_projection);
}

std::ostream& operator<<(std::ostream& output, const Vector& vector) {
  output << vector.x_projection << " " << vector.y_projection;
  return output;
}

std::istream& operator>>(std::istream& input, Vector& vector) {
  input >> vector.x_projection >> vector.y_projection;
  return input;
}

struct Line {
  Ld a_coeff = 0, b_coeff = 0, c_coeff = 0;
  Line() = default;
  Line(Ld a_c, Ld b_c, Ld c_c) : a_coeff(a_c), b_coeff(b_c), c_coeff(c_c) {}
  Line(Vector point1, Vector point2) {
    a_coeff = point1.y_projection - point2.y_projection;
    b_coeff = point2.x_projection - point1.x_projection;
    c_coeff = point1.x_projection * point2.y_projection -
              point2.x_projection * point1.y_projection;
  }

  bool IsIntersect(const Line& other) const {
    Ld delta = a_coeff * other.b_coeff - b_coeff * other.a_coeff;
    return abs(delta) >= kEps;
  }
};

Ld operator||(const Line& line, const Vector& point) {
  return abs(line.a_coeff * point.x_projection +
             line.b_coeff * point.y_projection + line.c_coeff) /
         Vector(line.a_coeff, line.b_coeff).Length();
}

Vector operator%(const Line& line1, const Line& line2) {
  Ld delta = line1.a_coeff * line2.b_coeff - line1.b_coeff * line2.a_coeff;
  Ld delta1 = -line1.c_coeff * line2.b_coeff + line2.c_coeff * line1.b_coeff;
  Ld delta2 = -line1.a_coeff * line2.c_coeff + line2.a_coeff * line1.c_coeff;
  return Vector(delta1 / delta, delta2 / delta);
}

std::ostream& operator<<(std::ostream& output, const Line& line) {
  output << line.a_coeff << " " << line.b_coeff << " " << line.c_coeff;
  return output;
}

std::istream& operator>>(std::istream& input, Line& line) {
  input >> line.a_coeff >> line.b_coeff >> line.c_coeff;
  return input;
}

bool Between(Vector& p1, Vector& p2, Vector& point) {
  return std::min(p1.x_projection, p2.x_projection) <= point.x_projection &&
         point.x_projection <= std::max(p1.x_projection, p2.x_projection) &&
         std::min(p1.y_projection, p2.y_projection) <= point.y_projection &&
         point.y_projection <= std::max(p1.y_projection, p2.y_projection);
}

struct Segment {
  Vector point1, point2;
  Segment() = default;
  Segment(Vector point1, Vector point2) : point1(point1), point2(point2) {}
};

Ld operator||(const Segment& segment, const Vector& point) {
  Vector point_c = point;
  Vector point_a = segment.point1;
  Vector point_b = segment.point2;

  Ld line_distance = Line(point_a, point_b) || point_c;

  Ld dist_to_a = point_a || point_c;
  Ld dist_to_b = point_b || point_c;

  Ld cross_product_cab = (point_c - point_a) * (point_b - point_a);
  Ld cross_product_abc = (point_c - point_b) * (point_a - point_b);

  if (cross_product_abc >= kEps && cross_product_cab >= kEps) {
    return line_distance;
  }
  return std::min(dist_to_a, dist_to_b);
}

void Solve() {
  Vector p1;
  Vector p2;
  Vector t1;
  Vector t2;
  std::cin >> p1 >> p2 >> t1 >> t2;
  Line line1(p1, p2);
  Line line2(t1, t2);
  Segment segment1(p1, p2);
  Segment segment2(t1, t2);

  if (!line1.IsIntersect(line2)) {
    std::cout << (line1 || t1) << "\n";
    return;
  }
  Vector point = line1 % line2;

  if (Between(p1, p2, point) && Between(t1, t2, point)) {
    std::cout << "0.0000000000\n";
    return;
  }
  std::vector<Ld> cand;
  cand.push_back(p1 || t1);
  cand.push_back(p1 || t2);
  cand.push_back(p2 || t1);
  cand.push_back(p2 || t2);
  cand.push_back(segment2 || p2);
  cand.push_back(segment2 || p1);
  cand.push_back(segment1 || t1);
  cand.push_back(segment1 || t2);
  std::sort(cand.begin(), cand.end());
  std::cout << cand[0] << "\n";
}

int main() {
  std::cout << std::fixed << std::setprecision(kPrecision);
  Init();
  Solve();
  return 0;
}
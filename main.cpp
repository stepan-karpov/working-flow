#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

typedef double Db;
typedef long long Ll;

const Db PI = acos(-1);
const Ll kInf = 4e18;
const Ll KInfInf = -8e18;

void Fastios() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
}

struct Point {
  Ll x;
  Ll y;

  Point() = default;
  Point(long coord_x, Ll coord_y) : x(coord_x), y(coord_y) {}
  Point operator+(Point other) const { return Point(x + other.x, y + other.y); }
  Point operator-(Point other) const { return Point(x - other.x, y - other.y); }
  Ll operator*(Point other) const { return x * other.y - y * other.x; }
  Ll operator%(Point other) const { return x * other.x + y * other.y; }
  Point operator-() const { return Point(-x, -y); }
  bool operator==(Point other) const { return x == other.x && y == other.y; }
  bool operator<(const Point& p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
  Ll Len2() const { return (Ll)x * x + (Ll)y * y; }
  Db Ang() const { return atan2(static_cast<Db>(y), static_cast<Db>(x)); }
};

bool Cmp(const Point& lhs, const Point& rhs) {
  Ll temp = lhs * rhs;
  return temp != 0 ? temp < 0 : lhs.Len2() < rhs.Len2();
}

std::istream& operator>>(std::istream& in, Point& input_point) {
  in >> input_point.x >> input_point.y;
  return in;
}

std::ostream& operator<<(std::ostream& out, Point output_point) {
  out << output_point.x << ' ' << output_point.y;
  return out;
}

std::vector<Point> ConvexHull(std::vector<Point> points) {
  int len_points = points.size();
  int mi = 0;
  for (int i = 0; i < len_points; ++i) {
    if (points[mi] < points[i]) {
      mi = i;
    }
  }
  std::swap(points[0], points[mi]);
  for (int i = 1; i < len_points; i++)
    points[i] = points[i] - points[0];
  std::sort(points.begin() + 1, points.end(), Cmp);

  int id = 0;
  std::vector<Point> result(len_points);
  result[id] = points[0];
  id++;
  for (int i = 1; i < len_points; i++) {
    Point cur_vec = points[i] + points[0];
    while (id >= 2 &&
           (result[id - 1] - result[id - 2]) * (cur_vec - result[id - 2]) >= 0)
      id--;
    result[id] = cur_vec;
    id++;
  }
  result.resize(id);
  return result;
}

struct FastGetter {
  int len_points;
  Point st;
  std::vector<Point> points;
  std::vector<Db> Ang;

  FastGetter(const std::vector<Point>& values) : points(ConvexHull(values)) {
    len_points = points.size();
    std::reverse(points.begin(), points.end());
    Ang.resize(len_points);
    for (int i = 0; i < len_points; ++i) {
      Ang[i] = (points[(i + 1) % len_points] - points[i]).Ang();
    }
    for (int i = 0; i < len_points; ++i) {
      if (i && Ang[i] < Ang[i - 1]) {
        Ang[i] += 2 * PI;
      }
    }
  }

  Ll GetMax(Ll arg1, Ll arg2) {
    if (len_points < 3) {
      Ll mx = KInfInf;
      for (int i = 0; i < len_points; ++i) {
        mx = std::max(mx, static_cast<Ll>(arg1 * points[i].x) +
                              static_cast<Ll>(arg2 * points[i].y));
      }
      return mx;
    }
    int lb = 0;
    int rb = len_points - 1;
    Db angle = atan2(arg1, -arg2);
    while (angle < Ang[0]) {
      angle += 2 * PI;
    }
    while (lb != rb) {
      int mid = (lb + rb + 1) / 2;
      if (Ang[mid] < angle) {
        lb = mid;
      } else {
        rb = mid - 1;
      }
    }
    lb = (lb + 1) % len_points;
    return static_cast<Ll>(arg1 * points[lb].x) +
           static_cast<Ll>(arg2 * points[lb].y);
  }

  void SaveValues(std::vector<Point>& carry) {
    std::copy(points.begin(), points.end(), std::back_inserter(carry));
  }
};

class TaskSolver {
  int sz;
  int storage_sz;
  std::vector<char> empty;
  std::vector<FastGetter> storage;

  Ll GetMaximum(Ll arg1, Ll arg2) {
    Ll res = -kInf;
    for (int i = 0; i < storage_sz; ++i) {
      res = std::max(res, storage[i].GetMax(arg1, arg2));
    }
    return res;
  }

  void Add(Point extra) {
    std::vector<Point> carry;
    carry.push_back(extra);
    for (int i = 0; i < storage_sz; ++i) {
      if (empty[i]) {
        storage[i] = FastGetter(carry);
        carry.clear();
        empty[i] = false;
        break;
      } else {
        storage[i].SaveValues(carry);
        empty[i] = true;
      }
    }
    if (!carry.empty()) {
      storage.push_back(FastGetter(carry));
      empty.push_back(false);
      storage_sz++;
    }
    sz++;
  }

 public:
  TaskSolver() : sz(0), storage_sz(0) {}

  void Input() {
    Fastios();
    int n;
    std::cin >> n;
    Point pt;
    for (int i = 0; i < n; ++i) {
      std::cin >> pt;
      Add(pt);
    }
  }

  void ProcessQueries() {
    int queries;
    std::cin >> queries;
    std::string type;
    Point value;
    for (int i = 0; i < queries; ++i) {
      std::cin >> type >> value;
      if (type == "add") {
        Add(value);
      } else {
        std::cout << GetMaximum(value.x, value.y) << '\n';
      }
    }
  }
};

int main() {
  TaskSolver solver;
  solver.Input();
  solver.ProcessQueries();
}
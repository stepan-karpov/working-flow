
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using Ld = long double;
using ll = long long;

struct Vector {
  int x = 0, y = 0;

  Vector() = default;
  Vector(int x, int y) : x(x), y(y) {}

  inline Vector operator +( const Vector &p ) const { return Vector(x + p.x, y + p.y); }
  inline Vector operator -( const Vector &p ) const { return Vector(x - p.x, y - p.y); }
  inline ll operator *( const Vector &p ) const { return (ll)x * p.y - (ll)y * p.x; }
  inline bool operator <( const Vector &p ) const { return x < p.x || (x == p.x && y < p.y); }

  inline ll d2() const { return (ll)x * x + (ll)y * y; }
  inline Ld ang() const { return atan2((Ld)y, (Ld)x); }
};

inline bool pless( const Vector &a, const Vector &b ) {
  ll x = a * b;
  return x != 0 ? x < 0 : a.d2() < b.d2();
}

std::vector<Vector> ConvexHull(std::vector<Vector> points_set) {
  int initial_size = int(points_set.size());
  int initial_point = 0;
  for (int i = 0; i < initial_size; ++i) {
    if (points_set[initial_point] < points_set[i]) {
      initial_point = i;
    }
  }
  std::swap(points_set[0], points_set[initial_point]);
  for (int i = 1; i < initial_size; i++) {
    points_set[i] = points_set[i] - points_set[0];
  }
  std::sort(points_set.begin() + 1, points_set.end(), pless);

  int rn = 0;
  std::vector<Vector> convex(initial_size);
  convex[rn++] = points_set[0];
  for (int i = 1; i < initial_size; i++) {
    Vector current_direction = points_set[i] + points_set[0];
    while (rn >= 2 && (convex[rn - 1] - convex[rn - 2]) *
                      (current_direction - convex[rn - 2]) >= 0) {
      --rn;
    }
    convex[rn++] = current_direction;
  }
  convex.resize(rn);
  return convex;
}

struct MagicStructure {
  int convex_size;
  Vector st;
  std::vector<Vector> p;
  std::vector<Vector> pointset;
  std::vector<Ld> ang;

  MagicStructure(std::vector<Vector>& initial)
    : p(ConvexHull(initial)), pointset(initial) {
    convex_size = int(p.size());
    reverse(p.begin(), p.end());
 
    ang.resize(convex_size);

    for (int i = 0; i < convex_size; ++i) {
      ang[i] = (p[(i + 1) % convex_size] - p[i]).ang();
    }
    for (int i = 0; i < convex_size; ++i) {
      if (i && ang[i] < ang[i - 1]) {
        ang[i] += 2 * M_PI;
      }
    }
  }

  ll GetMax(int aa, int bb) {
    if (convex_size < 3) {
      ll ma = -(ll)8e18;
      for (int l = 0; l < convex_size; ++l) {
        ma = std::max(ma, (ll)aa * p[l].x + (ll)bb * p[l].y);
      }
      return ma;
    }

    int left_border = 0, right_border = convex_size - 1;
    Ld xx = atan2(aa, -bb);
    while (xx < ang[0]) {
      xx += 2 * M_PI;
    }
    while (left_border != right_border) {
      int m = (left_border + right_border + 1) / 2;
      if (ang[m] < xx) {
        left_border = m;
      } else {
        right_border = m - 1;
      }
    }
    left_border = (left_border + 1) % convex_size;
    return (ll)aa * p[left_border].x + (ll)bb * p[left_border].y;
  }
};

struct MegaMagic {
  int n_size = 1;
  std::vector<MagicStructure*> line;

  MegaMagic(int total) {
    int n_size = log(total) + 5;
    line.assign(n_size, nullptr);
  }

  void Add(Vector point) {
  }
};

int main() {
  int n_size;
  std::cin >> n_size;
  std::vector<Vector> initial(n_size);
  for (int i = 0; i < n_size; ++i) {
    std::cin >> initial[i].x >> initial[i].y;
  }

  MagicStructure tempo(initial);

  int query_number;
  std::cin >> query_number;

  for (int i = 0; i < query_number; ++i) {
    std::string query;
    std::cin >> query;
    if (query == "get") {
      int aa, bb;
      std::cin >> aa >> bb;
      std::cout << tempo.GetMax(aa, bb) << "\n";
    }
  }

}
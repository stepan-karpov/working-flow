#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using Ld = long double;
using Ll = long long;

const Ll kMagicConst = 8e18;
const int kMagic10 = 10;
const Ll kInf = 4e18;
const int kMaxSz = 1e5 + 100;

struct Vector {
  int xx = 0, yy = 0;

  Vector() = default;
  Vector(int xx, int yy) : xx(xx), yy(yy) {}

  inline Vector operator+(const Vector& pr) const {
    return Vector(xx + pr.xx, yy + pr.yy);
  }
  inline Vector operator-(const Vector& pr) const {
    return Vector(xx - pr.xx, yy - pr.yy);
  }
  inline Ll operator*(const Vector& pr) const {
    return (Ll)xx * pr.yy - (Ll)yy * pr.xx;
  }
  inline bool operator<(const Vector& pr) const {
    return xx < pr.xx || (xx == pr.xx && yy < pr.yy);
  }

  inline Ll D2() const { return (Ll)xx * xx + (Ll)yy * yy; }
  inline Ld Ang() const { return atan2((Ld)yy, (Ld)xx); }
};

inline bool Pless(const Vector& aa, const Vector& bb) {
  Ll xx = aa * bb;
  return xx != 0 ? xx < 0 : aa.D2() < bb.D2();
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
  std::sort(points_set.begin() + 1, points_set.end(), Pless);

  int rn = 0;
  std::vector<Vector> convex(initial_size);
  convex[rn++] = points_set[0];
  for (int i = 1; i < initial_size; i++) {
    Vector current_direction = points_set[i] + points_set[0];
    while (rn >= 2 && (convex[rn - 1] - convex[rn - 2]) *
                              (current_direction - convex[rn - 2]) >=
                          0) {
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

  void Build() {
    convex_size = int(p.size());
    reverse(p.begin(), p.end());
    ang.resize(convex_size);

    for (int i = 0; i < convex_size; ++i) {
      ang[i] = (p[(i + 1) % convex_size] - p[i]).Ang();
    }
    for (int i = 0; i < convex_size; ++i) {
      if (i != 0 && ang[i] < ang[i - 1]) {
        ang[i] += 2 * M_PI;
      }
    }
  }

  MagicStructure(Vector point) {
    std::vector<Vector> temp(1, point);
    p = ConvexHull(temp);
    pointset = temp;
    Build();
  }

  MagicStructure(std::vector<Vector>& initial)
      : p(ConvexHull(initial)), pointset(initial) {
    Build();
  }

  Ll GetMax(int aa, int bb) {
    if (convex_size < 3) {
      Ll ma = -kMagicConst;
      for (int i = 0; i < convex_size; ++i) {
        ma = std::max(ma, (Ll)aa * p[i].xx + (Ll)bb * p[i].yy);
      }
      return ma;
    }

    int left_border = 0;
    int right_border = convex_size - 1;
    Ld xx = atan2(aa, -bb);
    while (xx < ang[0]) {
      xx += 2 * M_PI;
    }
    while (left_border != right_border) {
      int mid = (left_border + right_border + 1) / 2;
      if (ang[mid] < xx) {
        left_border = mid;
      } else {
        right_border = mid - 1;
      }
    }
    left_border = (left_border + 1) % convex_size;
    return (Ll)aa * p[left_border].xx + (Ll)bb * p[left_border].yy;
  }
};

struct MegaMagic {
  int n_size = 1;
  std::vector<MagicStructure*> trie;

  MegaMagic(int total) {
    while ((1 << n_size) <= total) {
      ++n_size;
    }
    trie.assign(n_size + 5, nullptr);
  }

  void Add(Vector point) {
    MagicStructure* pointer = new MagicStructure(point);
    int position = 0;
    while (trie[position] != nullptr) {
      std::vector<Vector> total;
      std::vector<Vector>& part1 = trie[position]->pointset;
      std::vector<Vector>& part2 = pointer->pointset;
      total.reserve(part1.size() + part2.size() + kMagic10);
      for (size_t i = 0; i < part1.size(); ++i) {
        total.push_back(part1[i]);
      }
      for (size_t i = 0; i < part2.size(); ++i) {
        total.push_back(part2[i]);
      }
      delete pointer;
      delete trie[position];
      trie[position] = nullptr;
      pointer = new MagicStructure(total);
      ++position;
    }
    trie[position] = pointer;
  }

  Ll Result(Ll aa, Ll bb) {
    Ll ans = -kInf;
    for (size_t i = 0; i < trie.size(); ++i) {
      if (trie[i] != nullptr) {
        ans = std::max(ans, trie[i]->GetMax(aa, bb));
      }
    }
    return ans;
  }

  ~MegaMagic() {
    for (size_t i = 0; i < trie.size(); ++i) {
      if (trie[i] != nullptr) {
        delete trie[i];
      }
    }
  }
};

int main() {
  // int n_size;
  // std::cin >> n_size;
  // std::vector<Vector> initial(n_size);
  // for (int i = 0; i < n_size; ++i) {
  //   std::cin >> initial[i].xx >> initial[i].yy;
  // }

  // MagicStructure tempo(initial);

  // int query_number;
  // std::cin >> query_number;

  // for (int i = 0; i < query_number; ++i) {
  //   std::string query;
  //   std::cin >> query;
  //   if (query == "get") {
  //     int aa;
  //     int bb;
  //     std::cin >> aa >> bb;
  //     std::cout << tempo.GetMax(aa, bb) << "\n";
  //   } else if (query == "add") {
  //     int aa;
  //     int bb;
  //     std::cin >> aa >> bb;
  //     initial.push_back({aa, bb});
  //     tempo = MagicStructure(initial);
  //   }
  // }
  int n_size;
  std::cin >> n_size;
  MegaMagic hahalol(kMaxSz);

  for (int i = 0; i < n_size; ++i) {
    Vector temp;
    std::cin >> temp.xx >> temp.yy;
    hahalol.Add(temp);
  }

  int query_number;
  std::cin >> query_number;

  for (int i = 0; i < query_number; ++i) {
    std::string query;
    std::cin >> query;
    if (query == "get") {
      int aa;
      int bb;
      std::cin >> aa >> bb;
      std::cout << hahalol.Result(aa, bb) << "\n";
    } else if (query == "add") {
      int aa;
      int bb;
      std::cin >> aa >> bb;
      hahalol.Add({aa, bb});
    }
  }
}
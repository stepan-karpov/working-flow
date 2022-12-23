#include <iostream>
#include <vector>
#include <array>
#include "matrix.h"

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

using std::vector;

int main() {
  Init();

  // vector<vector<Rational>> a1 = {
  //   {1, 2, 3, 4},
  //   {5, 6, 7, 8},
  //   {9, 10, 11, 12}
  // };

  // vector<vector<Rational>> a2 = {
  //   {1, 2, 3, 4, 5},
  //   {6, 7, 8, 9, 10},
  //   {11, 12, 13, 14, 15},
  //   {16, 17, 18, 19, 20},
  // };

  // vector<vector<Rational>> a4 = {
  //   {1, 2, 3, 4},
  //   {6, 7, 8, 9},
  //   {11, 12, 13, 14},
  //   {16, 17, 18, 19},
  // };


  // Matrix<3u, 4u> m1(a1);
  // Matrix<4u, 5u> m2(a2);
  // Matrix<3u, 5u> m3 = m1 * m2;
  // Matrix<4u, 4u> m4(a4);

  // std::cout << m1;

  // std::cout << '\n';
  // std::cout << '\n';
  // std::cout << '\n';

  // m1 *= 2;
  // std::cout << m1 << '\n';

  // std::cout << m4 << '\n';
  // std::cout << trace(m4).asDecimal(5) << '\n';
  // std::cout << transposed(m4) << '\n';

  // std::array<Rational, 4> row = m1.getRow(0);
  // for (int i = 0; i < 4; ++i) {
  //   std::cout << row[i].asDecimal(5) << " ";
  // }
  // std::cout << '\n';

  // std::array<Rational, 3> col = m1.getColumn(0);
  // for (int i = 0; i < 3; ++i) {
  //   std::cout << col[i].asDecimal(5) << " ";
  // }
  // std::cout << '\n';


  // vector<vector<Rational>> a1 = {
  //   {1,  1,  124546,   245 },
  //   {0,  1,  5,   5 },
  //   {0,  0,  1,   1},
  //   {0,  0,  10,  11}
  // };

  // Matrix<4, 4, Rational> m(a1);
  // // Matrix<4, 4, Rational> m1 = m;

  // std::cout << m << '\n';


  // Rational cur_det = det<4, Rational>(m);
  // std::cout << cur_det.asDecimal(5) << '\n';
  
  // std::cout << m.triangulate() << '\n';
  // std::cout << m;
  // Residue<7> a(3);
  // Residue<7> b(4);
  // a /= b;

  // int t = static_cast<int>(a);

  // std::cout << a << '\n';
  // std::cout << t << '\n';
  // std::cout << -a << '\n';

  // vector<vector<Residue<5>>> a1 = {
  //   {1, 1},
  //   {2, 3},
  // };

  // vector<vector<Residue<5>>> a2 = {
  //   {1, 1},
  //   {2, 2},
  // };

  // Matrix<2, 2, Residue<5>> m1(a1);
  // Matrix<2, 2, Residue<5>> m2(a2);

  // // std::cout << m1 * m2 << '\n';

  // std::cout << det(m1) << '\n';
  // Residue<5> t = 3;

  // bool check = (t != 3);

  // std::cout << check << '\n';

  Matrix<3, 3, Rational> A = {
    {1, 2, 3},
    {5, 6, 7},
    {1, 4, 2}
  };

  std::cout << A << '\n';
  A.invert();
  std::cout << A << '\n';
  Matrix<3, 3, Rational> B = A.inverted();

  std::cout << B << '\n';

}
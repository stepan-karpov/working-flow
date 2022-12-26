#include <cassert>
#include <climits>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "matrix.h"

#undef throw

inline bool equals(double x, double y) { return x - y < 1e-6 && x - y > -1e-6; }

void testMatrix() {
  {
    Residue<99527> r1(350);
    Residue<99527> r2(524);
    assert(r1 * r2 == Residue<99527>(83873));
    assert(r1 / r2 == Residue<99527>(17095));
  }

  {
    const Matrix<2, 3, Residue<6>> a = {{1, 2, 3}, {0, 2, 4}};
    const Matrix<3, 2, Residue<6>> b = {{2, 0}, {1, 3}, {0, 4}};
    const Matrix<2, 2, Residue<6>> ab = a * b;
    assert(ab[0][0] == Residue<6>(4));
    assert(ab[0][1] == Residue<6>(0));
    assert(ab[1][0] == Residue<6>(2));
    assert(ab[1][1] == Residue<6>(4));
  }

  using std::vector;

  const Matrix<4, 5, Residue<17>> am = {{8, -4, -5, 5, 9},
                                        {1, -3, -5, 0, -7},
                                        {7, -5, 1, 4, 1},
                                        {3, -1, 3, 2, 5}};
  const Matrix<5, 4, Residue<17>> bm = {{4, 0, 3, 2},
                                        {1, -7, 4, 5},
                                        {7, 1, 5, 3},
                                        {-5, -3, -3, -1},
                                        {1, -5, 2, 3}};
  // const Matrix<4,5,Residue<17>> am = a;
  // const Matrix<5,4,Residue<17>> bm = b;

  assert(am.rank() == 4);
  assert(bm.rank() == 3);
  const SquareMatrix<4, Residue<17>> ab = {{-23, -37, -14, 3},
                                           {-41, 51, -48, -49},
                                           {11, 19, -4, -9},
                                           {27, -21, 24, 23}};

  const auto abm = am * bm;
  assert((abm == SquareMatrix<4, Residue<17>>(ab)));

  const auto aminusb = am - bm.transposed();
  const Matrix<4, 5, Residue<17>> diff = {{4, -5, -12, 10, 8},
                                          {1, 4, -6, 3, -2},
                                          {4, -9, -4, 7, -1},
                                          {1, -6, 0, 3, 2}};
  assert(aminusb == diff);

  auto newMatrix = Residue<17>(2) * aminusb * bm;
  newMatrix[2][2] = Residue<17>(1);

  assert(newMatrix.det() == Residue<17>(14420160));

  assert(newMatrix.trace() == Residue<17>(-345));

  Matrix<4, 4, Residue<17>> finiteUnity;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      finiteUnity[i][j] = Residue<17>(static_cast<long long>(i == j));
    }
  }
  assert(newMatrix.inverted() * newMatrix == finiteUnity);

  std::cerr << "Tests over the finite field passed!\n";

  {
    SquareMatrix<2> m = {{0, 1}, {1, 0}};
    assert(m.det() == Rational(-1));
  }

  std::ifstream in("matr.txt");
  SquareMatrix<20> bigMatrix;
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      in >> bigMatrix[i][j];
    }
  }

  vector<vector<double>> bigInvertedMatrix(20, vector<double>(20));
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      in >> bigInvertedMatrix[i][j];
    }
  }

  auto anotherMatrix = bigMatrix;
  // bigMatrix.inverted();
  bigMatrix.invert();
  std::cerr << "Big matrix inverted!\n";
  for (int i = 0; i < 20; ++i) {
    auto row = bigMatrix.getRow(i);
    auto anotherRow = bigInvertedMatrix[i];
    for (int j = 0; j < 20; ++j) {
      assert(equals(static_cast<double>(row[j]), anotherRow[j]));
    }
  }
  std::cerr << "Inverted matrix is correct!\n";
  bigMatrix *= anotherMatrix;
  std::cerr << "Matrix multiplied by its inverted matrix!\n";
  SquareMatrix<20> unity = SquareMatrix<20>();
  for (int j = 0; j < 20; ++j) {
    auto column = bigMatrix.getColumn(j);
    auto unityColumn = unity.getColumn(j);
    for (int i = 0; i < 20; ++i) {
      std::cout << i << ' ';
      std::cout << column[i].toString() << ' ';
      std::cout << unityColumn[i].toString() << '\n';
      assert(column[i] == unityColumn[i]);
    }
  }

  std::cerr << "Result of A*A^(-1) is correct!\n";

  auto det = anotherMatrix.det();
  std::cerr << "Determinant is computed!\n";
  for (int i = 0; i < 20; ++i) {
    anotherMatrix[0][i] /= det;
  }
  assert(anotherMatrix.det() == 1);

  auto transposedMatrix = anotherMatrix.transposed();
  assert((anotherMatrix *= transposedMatrix).det() == 1);
}

int main() {
  testMatrix();
}
using namespace std;
#include <vector>
#include "mbed.h"
#include "UnitTester.h"
#include <Matrix.h>


bool UnitTester::MatrixCreationTest(){
  printf("Starting Matrix Creation Test\n");
  printf("Testing M1\n");
  Matrix m1;
  printf("M1 shape: %d:%d\n", m1.shape.width, m1.shape.height);
  m1.print_matrix();

  printf("Testing M2\n");
  std::vector< std::vector<double> > m2Template(4, std::vector<double>(3));
  Matrix m2 = Matrix(m2Template);
  printf("M2 shape: %d:%d\n", m2.shape.width, m2.shape.height);
  m2.print_matrix();

  printf("Testing M3\n");
  Shape m3Shape = {3, 4};
  Matrix m3 = Matrix(m3Shape);
  printf("M3 shape: %d:%d\n", m3.shape.width, m3.shape.height);
  m3.print_matrix();

  printf("Testing M4\n");
  Matrix m4 = Matrix(1, 2);
  printf("M4 shape: %d:%d\n", m4.shape.width, m4.shape.height);
  m4.print_matrix();
  printf("Test completed\n");
  return true;
}

bool UnitTester::MatrixReadWriteTest(){
  printf("Starting Matrix Read-Write Test\n");
  double temp[4][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {9, 0, 1}
  };
  matrix_type tempM(3, vector<double>(4));
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 4; j++) {
      tempM[i][j] = temp[j][i];
    }
  }
  Matrix m1 = Matrix(tempM);
  m1.print_matrix();
  printf("Read value at (0, 0): %f\n", m1.get(0, 0));
  printf("Read value at (1, 1): %f\n", m1.get(1, 1));
  printf("Read value at (2, 3): %f\n", m1.get(2, 3));
  printf("Write value 10 to (0, 0)\n");
  printf("Write value 14 to (1, 3)\n");
  m1.set(0, 0, 10.0);
  m1.set(1, 3, 14.0);
  m1.print_matrix();

  printf("Test completed\n");
  return true;
}

bool UnitTester::MatrixOperationsTest(){
  printf("Starting Matrix Operations Test\n");
  double temp1[3][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8}
  };
  double temp2[3][3] = {
    {8, 7, 6},
    {5, 4, 3},
    {2, 1, 0}
  };
  matrix_type tempM1(3, vector<double>(3));
  matrix_type tempM2(3, vector<double>(3));
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++) {
      tempM1[i][j] = temp1[j][i];
      tempM2[i][j] = temp2[j][i];
    }
  }
  Matrix m1 = Matrix(tempM1);
  Matrix m2 = Matrix(tempM2);
  printf("M1:\n");
  m1.print_matrix();
  printf("M2:\n");
  m2.print_matrix();

  Matrix mp = m1 + m2;
  Matrix mpr = m2 + m1;
  printf("M1 + M2:\n");
  mp.print_matrix();
  printf("M2 + M1:\n");
  mpr.print_matrix();

  Matrix m1n = -m1;
  Matrix m2n = -m2;
  printf("-M1:\n");
  m1n.print_matrix();
  printf("-M2:\n");
  m2n.print_matrix();

  Matrix ms = m1 - m2;
  Matrix msr = m2 - m1;
  printf("M1 - M2:\n");
  ms.print_matrix();
  printf("M2 - M1:\n");
  msr.print_matrix();

  Matrix mm = m1 * m2;
  Matrix mmr = m2 * m1;
  printf("M1 * M2:\n");
  mm.print_matrix();
  printf("M2 * M1:\n");
  mmr.print_matrix();

  Matrix mcm = m1 * 10;
  Matrix mcd = m1 / 10;
  printf("M1 * 10:\n");
  mcm.print_matrix();
  printf("M2 / 10:\n");
  mcd.print_matrix();
  printf("Test completed\n");
  return true;
}

bool UnitTester::MatrixErrorTest(){
  printf("Starting Matrix Error Test\n");
  double temp1[3][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8}
  };
  double temp2[2][3] = {
    {8, 7, 6},
    {5, 4, 3}
  };
  matrix_type tempM1(3, vector<double>(3));
  matrix_type tempM2(3, vector<double>(2));
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++) {
      tempM1[i][j] = temp1[j][i];
    }
  }
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 2; j++) {
      tempM2[i][j] = temp2[j][i];
    }
  }

  Matrix m1 = Matrix(tempM1);
  Matrix m2 = Matrix(tempM2);
  printf("M1:\n");
  m1.print_matrix();
  printf("M2:\n");
  m2.print_matrix();

  Matrix mp = m1 + m2;
  Matrix mn = m1 - m2;
  Matrix mm = m1 * m2;
  printf("Test completed\n");

  return true;
}

#include "BaseMatrix.h"
#include <iostream>

void test() {

  /*ax+bx+cx <= C*/
  // std::vector<vector<double>> voter = {{-30, 2, -8, 5, -9},
  //                                      {-15, -5, -2, 2, 0},
  //                                      {-26, -3, 5, -10, 3},
  //                                      {500, 1, 1, 1, 1}};
  // std::vector<double> aim = {0, 8, 5, 3, 6};

  //  算法导论，29.3-6.ok
  // std::vector<vector<double>> voter = {{1, 1, -2}, {2, 2, 1}};
  // std::vector<double> aim = {0, 5, -3};

  //算法导论
  // vector<vector<double>> voter = {{30, 1, 1, 3}, {24, 2, 2, 5}, {36, 4, 1,
  // 2}}; vector<double> aim = {0, 3, 1, 2};

  // zxd的ppt例题
  vector<vector<double>> voter = {
      {7, 1, 3, -1, 0, 2, 0},  {-7, -1, -3, 1, 0, -2, 0},
      {12, 0, -2, 4, 1, 0},    {-12, 0, 2, -4, -1, 0},
      {10, 0, -4, 3, 0, 8, 1}, {-10, 0, 4, -3, 0, -8, -1}};
  vector<double> aim = {0, 0, -1, 3, 0, -2, 0};

  BaseMatrix x(voter, aim);
  x.show();

  // x.changeVar1(6, 1);
  // x.show();
  // x.changeVar2(6, 1);
  // x.show();
  // x.changeVar3(6, 1);
  // x.show();

  // x.potive(1);
  // x.show();

  while (x.canBeSolved()) {
    auto index = x.getNobaseVar();
    if (index == -1)
      break;
    auto flag = x.potive(index);
    if (!flag)
      break;
  }
  x.show();
  // std::cout << x.getNobaseVar() << '\n';

  // std::cout << x.getBaseVar(1) << '\n';
  // std::cout << x.getBaseVar(2) << '\n';
  // std::cout << x.getBaseVar(3) << '\n';
}

int main(int argc, char const *argv[]) {
  test();
  return 0;
}

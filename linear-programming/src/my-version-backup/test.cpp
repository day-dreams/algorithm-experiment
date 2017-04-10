#include "BaseMatrix.h"
#include <iostream>

void test_baseMatrix() {
  //来自我出的题目
  // std::vector<vector<double>> voter = {{-20, +2, -5, -3},
  //                                      {-20, -8, -2, +5},
  //                                      {-20, +5, +2, -10},
  //                                      {-20, -9, -2, +3}};
  // std::vector<double> aim = {0, 1, 1, 1};

  //来自算法导论
  std::vector<vector<double>> voter = {
      {-30, -1, -1, -3}, {-24, -2, -2, -5}, {-36, -4, -1, -2},
  };
  std::vector<double> aim = {0, 3, 1, 2};

  //  算法导论，29.3-6
  // std::vector<vector<double>> voter = {{-1, -1, -2}, {-2, -2, -1}};
  // std::vector<double> aim = {0, 5, -3};

  // http://www.cnblogs.com/jostree/p/4156685.html
  // std::vector<vector<double>> voter = {
  //     {-4, -1, -1, -1}, {-2, -1, 0, 0}, {-3, 0, 0, -1}, {-6, 0, -3, -1}};
  // std::vector<double> aim = {0, 1, 14, 6};

  //全0测试
  // std::vector<vector<double>> voter = {
  //     {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  // std::vector<double> aim = {0, 1, 14, 6};

  BaseMatrix x(voter, aim);
  x.show();

  //测试：最紧约束寻找
  // std::cout << x.findIndexOfMCC(1) << '\n';
  // std::cout << x.findIndexOfMCC(2) << '\n';
  // std::cout << x.findIndexOfMCC(3) << '\n';

  //测试：添加新变量
  // x.addNewVar(2, 0);
  // x.addNewVar(2, 1);
  // x.addNewVar(2, 2);
  // x.addNewVar(2, 3);
  // x.show();

  //测试：转动
  // x.exePotiv(1);
  // x.show();
  // x.exePotiv(3);
  // x.show();
  // x.exePotiv(2);
  // x.show();

  //实践：转化方法
  // x.setIntegerValue(false);
  auto flag = true;
  while (flag && x.canBePivot()) {
    auto index = x.getIndexOfPotiv();
    std::cout << "index to change :" << index << '\n';
    flag = x.exePotiv(index);
    x.show();
  }
  std::cout << "max value: " << x.aim[0] << '\n';
}

int main() { test_baseMatrix(); }

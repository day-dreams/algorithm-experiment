#pragma once

#include <map>
#include <vector>

using namespace std;

/*
  基本线性规划的复合矩阵，提供求解过程中的每个步骤

  默认求最大值

*/
class BaseMatrix {
public:
  bool NeedIntegerValue = true;
  vector<int> init_vars; /*初始变量集，记录他们的下标*/
  map<int, map<int, double>>
      constraints;      /*约束集，以对应基本变量下标作为索引,约束首变量为常数项*/
  map<int, double> aim; /*目标函数，aim[0]为常数项*/

  BaseMatrix(const vector<vector<double>> &matrix, const vector<double> _aim);

  void show();

  /*TODO: 检查是否可解*/
  bool canBeSolved();

  /*寻找可以替换的非基本变量;找不到返回-1*/
  int getNobaseVar();

  bool potive(int var_index);

private:
  /*在con_index中改写基本变量和非基本变量的地位*/
  void changeVar1(int basevar, int nobasebar);
  /*改写其他约束中的基本变量和非基本变量*/
  void changeVar2(int basevar, int nobasebar);
  /*改写目标函数中的基本变量和非基本变量*/
  void changeVar3(int basevar, int nobasebar);

  /*
    TODO: 测试正确性
   寻找对应的基本变量,所在约束最紧;找不到或者无界则返回-1
   */
  int getBaseVar(int nobasevar_index);
};

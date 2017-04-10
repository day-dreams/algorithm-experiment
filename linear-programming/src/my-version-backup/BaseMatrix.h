#pragma once

#include <iostream>
#include <vector>

using namespace std;

/*
    抽象出基本矩阵，表示线性规划的基本结构

    默认约束为标准型，不转化成松弛型

*/

class BaseMatrix {
public:
  const int m, n; /*m个变量，n个约束*/
  vector<vector<double>>
      constraints; /*约束，每个约束受元素为常量，其他为变量系数*/
  vector<double> aim; /*目标多项式,首元素为常量，其他为变量系数*/

  /*构造函数*/
  BaseMatrix(int m, int n);
  BaseMatrix(const vector<vector<double>> &matrix, const vector<double> _aim);

  /*设置解性质*/
  bool setMax(bool flag);
  bool setIntegerValue(bool flag);

  /*检查是否可以转动*/
  bool canBePivot();

  /*获取可以替换的变量下标*/
  int getIndexOfPotiv();

  /*TODO: 执行转动操作,替换第index个变量*/
  bool exePotiv(int index);

  /*输出矩阵*/
  void show();
  void show(int i);

private:
  bool NeedIntegerValue = true; /*是否要求整数解*/
  bool IsMax = true;            /*最大化目标多项式*/
  std::vector<bool> changedVar; /*记录初始变量是否已经被替换掉*/

public:
  /*变量替换，第一步,提换con中的var变量*/
  /*NOTE: 这个函数很关键，一定要反复测试！*/
  bool addNewVar(int var_index, int con_index);

  /*变量替换，第二步，替换每一个con中的var变量，排除con_index内*/
  bool changeVar(int var_index, int con_index);

  /*变量替换，第三部，替换目标里的变量*/
  bool changeVar3(int var_index, int con_index);

  /*寻找下标为index的变量的最紧约束(the Most Compact
   Constraint)，返回该最紧约束在约束组内的下标*/
  int findIndexOfMCC(int index);

  /*
    返回第var_index个变量在第con_index个约束内的最大值
    若无最大值，返回-1;否则返回之
  */
  double getMaxValue(int var_index, int con_index);
};

// /*多元线性多项式*/
// class BaseVector {
// public:
//   const int num_of_var;
//   double constant;
//   std::vector<double> variate;     /*变量下标*/
//   std::vector<double> coefficient; /*项的系数*/
//
//   /*构造函数，制定变量个数*/
//   BaseVector(int num);
//
//   /*输出多项式*/
//   void show();
// };
//
// /*线性规划问题的基本数据结构*/
// class LinearMatrix {
// public:
//   const int num_var, num_cons;         /*m个变量，n个约束*/
//   std::vector<int> varations;          /*变量下表集*/
//   BaseVector aim;                      /*目标多项式，使之最大\小化*/
//   std::vector<BaseVector> constraints; /*约束，不包括非负约束*/
//
//   LinearMatrix(int m, int n);
//
//   /*输出整个规划*/
//   void show();
// };
//
// /*输出多项式*/
// std::ostream &operator<<(std::ostream &out, BaseVector &x);
// std::ostream &operator<<(std::ostream &out, LinearMatrix &x);

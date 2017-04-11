#include "BaseMatrix.h"
#include <iostream>

BaseMatrix::BaseMatrix(const vector<vector<double>> &matrix,
                       const vector<double> _aim) {
  /*记录初始变量*/
  init_vars = vector<int>(_aim.size(), 0);
  for (int i = 0; i != init_vars.size(); ++i)
    init_vars[i] = i + 1;
  /*初始化约束*/
  for (int i = 0; i != matrix.size(); ++i) {
    constraints[i + 1 + matrix[0].size() - 1] = map<int, double>();
    for (int j = 0; j != matrix[i].size(); ++j)
      constraints[i + 1 + matrix[0].size() - 1][j] = matrix[i][j];
  }
  /*初始化目标函数*/
  for (int i = 0; i != _aim.size(); ++i)
    aim[i] = _aim[i];
}

void BaseMatrix::show() {
  std::cout << '\n';
  for (auto &entry : constraints) {
    std::cout << entry.first << '\t';
    std::cout << "| ";
    for (auto &a : entry.second)
      std::cout << a.second << "×(" << a.first << ')' << " + ";
    std::cout << '\n';
  }
  std::cout << ":\t: ";
  for (auto &a : aim)
    std::cout << a.second << "×(" << a.first << ')' << " + ";
  std::cout << '\n';
}

bool BaseMatrix::canBeSolved() {
  auto copy = *this;

  return true;
}

int BaseMatrix::getBaseVar(int basevar_index) {
  double max = -1;
  int nobasevar_index = -1;
  for (auto &entry : constraints) {
    if (entry.second[basevar_index] <= 0) /*一个无界的约束*/ {
      if (max < 0)
        max = 1000000;
    } else if (entry.second[0] < 0) { /*约束无法满足*/
      max = entry.second[0] / entry.second[basevar_index];
      // if (max < 0)
      //   max = 1000000;
    } else {
      // std::cout << entry.second[0] << " " << entry.second[basevar_index]
      // << '\n';
      auto temp = entry.second[0] / entry.second[basevar_index];
      // std::cout << basevar_index << "  " << entry.second.size() << '\n';
      if (max < 0 || temp < max) { /*NOTE: 取整判断*/
        // nobasevar_index = basevar_index + entry.second.size() - 1;
        nobasevar_index = entry.first;
        // std::cout << "temp:" << temp << "max:" << max
        //           << "nobase_index:" << nobasevar_index << '\n';
        if (NeedIntegerValue)
          max = int(temp);
        else
          max = temp;
      }
    }
  }
  return nobasevar_index;
  // return max;
}

int BaseMatrix::getNobaseVar() {
  for (auto &entry : aim) {
    if (entry.second > 0 && entry.first != 0)
      return entry.first;
  }
  return -1;
}

void BaseMatrix::changeVar1(int basevar, int nobasevar) {
  auto backup = constraints[basevar];
  auto to_delete = constraints.find(basevar);
  constraints.erase(to_delete);

  constraints[nobasevar] = map<int, double>();

  auto base = backup[nobasevar];
  // std::cout << "basevar:" << basevar << " nobasevar:" << nobasevar
  //           << " base:" << base << '\n';
  constraints[nobasevar][0] = backup[0] / base;
  for (auto &entry : backup) {
    if (entry.first == 0)
      continue;
    else if (entry.first == nobasevar)
      constraints[nobasevar][basevar] = 1 / base;
    // entry.second = 1 / base;
    else
      constraints[nobasevar][entry.first] = entry.second / base;
    // entry.second /= base;
  }
}

void BaseMatrix::changeVar2(int basevar, int nobasevar) {
  for (auto &entry : constraints) {
    if (entry.first == nobasevar)
      continue;
    else {
      auto base = entry.second[nobasevar];
      /*常数项*/
      entry.second[0] -= constraints[nobasevar][0] * base;
      int to_add_key = 0;
      double to_add_value = 0;
      auto to_delete = entry.second.find(nobasevar);
      for (auto &tiny : entry.second) {
        if (tiny.first == 0) {
          continue;
        } else {
          if (tiny.first == nobasevar) {
            to_add_key = basevar;
            to_add_value = -tiny.second * constraints[nobasevar][basevar];
          } else {
            tiny.second -= base * constraints[nobasevar][tiny.first];
          }
        }
      }
      entry.second.erase(to_delete);
      entry.second[to_add_key] = to_add_value;
    }
  }
}

void BaseMatrix::changeVar3(int basevar, int nobasevar) {
  /*常数*/
  aim[0] += aim[nobasevar] * constraints[nobasevar][0];
  int to_add_key = 0;
  double to_add_value = 0;
  auto to_delete = aim.find(nobasevar);
  for (auto &entry : aim) {
    if (entry.first == nobasevar) {
      to_add_key = basevar;
      to_add_value = -entry.second * constraints[nobasevar][basevar];
    } else if (entry.first == 0) {
      continue;
    } else {
      entry.second -= aim[nobasevar] * constraints[nobasevar][entry.first];
    }
  }
  aim.erase(to_delete);
  aim[to_add_key] = to_add_value;
}

bool BaseMatrix::potive(int var_index) {
  auto con_index = getBaseVar(var_index);
  if (con_index == -1 | con_index == -2)
    return false;
  changeVar1(con_index, var_index);
  changeVar2(con_index, var_index);
  changeVar3(con_index, var_index);
  return true;
}

#include "BaseMatrix.h"
#include <cassert>
#include <exception>
#include <iomanip>
#include <iostream>
#include <vector>

BaseMatrix::BaseMatrix(int m_num, int n_num)
    : m(m_num), n(n_num), changedVar(vector<bool>(m)) {
  this->constraints = vector<vector<double>>(n, vector<double>(m + 1));
  this->aim = vector<double>(m + 1);
}

BaseMatrix::BaseMatrix(const vector<vector<double>> &matrix,
                       const vector<double> _aim)
    : m(_aim.size() - 1), n(matrix.size()), constraints(matrix), aim(_aim),
      changedVar(vector<bool>(m)) {}

void BaseMatrix::show() {
  std::cout << '\n';
  for (auto &v : constraints) {
    std::cout << "| ";
    for (int i = 1; i < v.size(); ++i)
      std::cout << setw(5) << v[i] << ' ';
    std::cout << "  |" << v[0] << '\n';
  }
  std::cout << ": ";
  for (int i = 1; i < aim.size(); ++i) {
    std::cout << setw(5) << aim[i] << ' ';
  }
  std::cout << "  |" << aim[0] << '\n';
}

bool BaseMatrix::setMax(bool flag) {
  this->IsMax = flag;
  return this->IsMax;
}

bool BaseMatrix::setIntegerValue(bool flag) {
  this->NeedIntegerValue = flag;
  return this->NeedIntegerValue;
}

bool BaseMatrix::canBePivot() {
  for (auto ite = aim.begin() + 1; ite != aim.end(); ++ite) {
    if (*ite > 0)
      return true;
  }
  return false;
}

int BaseMatrix::getIndexOfPotiv() {
  for (auto ite = aim.begin() + 1; ite != aim.end(); ++ite) {
    if (*ite > 0)
      return ite - aim.begin();
  }
  return -1;
}

int BaseMatrix::findIndexOfMCC(int index) {
  /*NOTE:
   * 这里的返回值有转意，正常(正数)、值不存在(-2),-1(这个值不知道会什么时候返回)*/
  int to_return = -1;
  double min = 100000000;
  for (int i = 0; i != constraints.size(); ++i) {
    auto temp = getMaxValue(index, i);
    // std::cout << "index:" << index << " i:" << i << " max:" << temp << '\n';
    if (temp < 0)
      continue;
    if (temp < min) {
      min = temp;
      to_return = i;
    }
  }
  // std::cout << "min: " << min << " to_return: " << to_return << '\n';
  if (min == 0)
    return -2;
  return to_return;
}

bool BaseMatrix::exePotiv(int index) {
  // static vector<vector<double>> con_backup = this->constraints;
  // static vector<double> aim_backup = this->aim;

  /*转换的源头*/
  auto potiv_source = findIndexOfMCC(index);
  if (potiv_source == -2)
    return false;
  std::cout << "source_of_potiv: " << potiv_source << '\n';
  /*TODO 接着干！*/
  addNewVar(index, potiv_source);
  changeVar(index, potiv_source);
  changeVar3(index, potiv_source);

  return true;
}

bool BaseMatrix::addNewVar(int var_index, int con_index) {

  constraints[con_index][0] =
      -constraints[con_index][0] / constraints[con_index][var_index];

  auto base = constraints[con_index][var_index];
  for (int i = 1; i != constraints[con_index].size(); ++i) {
    if (i == var_index) {
      constraints[con_index][i] = 1 / base;
    } else {
      constraints[con_index][i] = -constraints[con_index][i] / base;
    }
  }
  return true;
}

bool BaseMatrix::changeVar(int var_index, int con_index) {
  // std::cout << "\n" << '\n';
  for (int i = 0; i != constraints.size(); ++i) {
    if (con_index == i)
      continue;
    else {
      // show(i);
      constraints[i][0] +=
          constraints[con_index][0] * constraints[i][var_index];
      /*x是防止覆盖的备份*/
      auto x = constraints[i];
      for (int j = 1; j != constraints[i].size(); ++j) {
        if (j == var_index) {
          constraints[i][j] = constraints[con_index][var_index] * x[j];
        } else {
          /*NOTE: 这个地方很危险，需要提前推导公式,同时需要注意值覆盖的问题*/
          // std::cout << "[i][j]:" << x[j] << " [i][var_index]:" <<
          // x[var_index]
          //           << " [con_index][j]:" << constraints[con_index][j] <<
          //           '\n';
          constraints[i][j] = x[j] + x[var_index] * constraints[con_index][j];
        }
      }
    }
    // show(i);
  }
  // std::cout << "\n" << '\n';
  return true;
}

bool BaseMatrix::changeVar3(int var_index, int con_index) {
  auto base = aim[var_index];
  aim[0] -= constraints[con_index][0] * base;
  for (int i = 1; i != aim.size(); ++i) {
    if (i == var_index) {
      aim[i] = constraints[con_index][i] * base;
    } else {
      aim[i] += constraints[con_index][i] * base;
    }
  }

  return true;
}

double BaseMatrix::getMaxValue(int var_index, int con_index) {
  assert(aim[var_index] > 0);
  if (constraints[con_index][var_index] == 0)
    return -123456;
  double max = constraints[con_index][0] / constraints[con_index][var_index];
  // std::cout << constraints[con_index][0] << " "
  //           << constraints[con_index][var_index] << " max:" << max << '\n';

  if (constraints[con_index][var_index] > 0) {
    return 123456;
  } else if (constraints[con_index][var_index] < 0) {
    if (constraints[con_index][0] > 0)
      return -1;
    else {
      auto max = constraints[con_index][0] / constraints[con_index][var_index];
      std::cout << "max = " << max << " int(Max) = " << int(max) << '\n';
      if (NeedIntegerValue)
        return int(max);
      else
        return max;
    }
  } else {
    return 0;
  }

  // if (NeedIntegerValue) {
  //   auto r = int(max);
  //   if (r == 0)
  //     throw std::exception();
  //   return r;
  // } else {
  //   if (max == 0)
  //     throw std::exception();
  //   return max;
  // }
}

void BaseMatrix::show(int i) {
  for (int j = 1; j != constraints[i].size(); ++j)
    std::cout << setw(5) << constraints[i][j] << " ";
  std::cout << constraints[i][0] << '\n';
}

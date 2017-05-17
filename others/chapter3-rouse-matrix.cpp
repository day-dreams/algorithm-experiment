/*
  玫瑰矩阵,不需要额外空间
*/

#include <iostream>

int sum_i(const int &i, const int &n) {
  /*
    返回第i圈之前一共有多少个元素
  */
  return 4 * (i - 1) * (n - i + 1);
}

int loop_of(const int &i, const int &j, const int &n) {
  /*
    返回当前元素在第几圈
  */
  int x, y;
  if (i > n / 2) {
    x = n - i + 1;
  } else {
    x = i;
  }
  if (j > n / 2) {
    y = n - j + 1;
  } else {
    y = j;
  }
  return x < y ? x : y;
}

int get_num(const int &i, const int &j, const int &n) {
  /*
    返回a[i,j]
  */
  auto loop_index = loop_of(i, j, n);
  auto num_per_edge = n - 2 * loop_index + 2;
  auto start = sum_i(loop_index, n);
  auto oo = loop_index;
  auto nn = loop_index + num_per_edge - 1;
  if (j == oo) {
    return start + i - oo + 1;
  } else if (i == nn) {
    return start + num_per_edge * 1 + j - oo;
  } else if (j == nn) {
    return start + num_per_edge * 2 + nn - i - 1;
  } else {
    return start + num_per_edge * 3 + nn - j - 2;
  }
}

int main(int argc, char const *argv[]) {
  auto n = atoi(argv[1]);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      std::cout << get_num(i, j, n) << '\t';
    }
    std::cout << '\n';
  }
  return 0;
}

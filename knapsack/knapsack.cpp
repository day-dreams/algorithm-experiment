/*
  画出那张表,按步骤填好就行
*/

#include <iostream>
#include <random>
#include <vector>
using namespace std;

void knapsack(vector<int> &weights, vector<int> &values, int max_weight) {
  std::vector<vector<int>> v(weights.size(), vector<int>(max_weight + 1, 0));
  {                                          /*填表*/
    for (int i = 0; i != v[0].size(); ++i) { /*只有第一个物品时*/
      if (weights[0] <= i) {
        v[0][i] = values[0];
      }
    }
    for (int i = 0; i != v.size(); ++i) /*最大重量为0时*/
      v[i][0] = 0;
    for (int i = 1; i < v.size(); ++i) { /*每次加一个物品作为一个阶段*/
      for (int j = 1; j <= max_weight;
           ++j) { /*求前i个物品,使用j个单位重量,可获得的最大收益*/
        if (j < weights[i]) { /*第i个物品无法在k个重量下放入*/
          v[i][j] = v[i - 1][j];
        } else if (v[i - 1][j - weights[i]] + values[i] >
                   v[i - 1][j]) { /*可装入且价值更大*/
          v[i][j] = v[i - 1][j - weights[i]] + values[i];
        } else {
          v[i][j] = v[i - 1][j];
        }
      }
    }

    for (auto &entry : v) { /*输出表*/
      for (auto &x : entry)
        std::cout << x << ' ';
      std::cout << '\n';
    }
    std::cout << "max value:" << v[weights.size() - 1][max_weight] << '\n';
  }
}

int main(int argc, char const *argv[]) {
  random_device d;
  auto n = 5;

  auto weights = vector<int>(n, 0);
  for (auto &x : weights)
    x = 1 + d() % 10;
  auto values = vector<int>(n, 0);
  for (auto &x : values)
    x = 1 + d() % 10;

  std::cout << "weights: ";
  for (auto &x : weights)
    std::cout << x << ' ';
  std::cout << "\nvalues: ";
  for (auto &x : values)
    std::cout << x << ' ';
  std::cout << '\n';

  knapsack(weights, values, 10); /*最大重量为10*/

  return 0;
}

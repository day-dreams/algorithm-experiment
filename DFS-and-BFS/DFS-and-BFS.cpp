#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <vector>
using namespace std;

void BFS(vector<vector<int>> &map) {
  std::cout << '\n';
  auto visited = vector<int>(map.size(), 0);
  queue<int> to_visit;
  to_visit.push(0); /*从第0个点开始访问*/
  visited[0] = 1;
  while (!to_visit.empty()) {
    auto cur = to_visit.front();
    to_visit.pop();
    std::cout << cur << ' ';
    for (int i = 0; i != map[cur].size(); ++i) {
      if (visited[i] == 0 && map[cur][i] > 0) { /*相连且未访问过*/
        to_visit.push(i);
        visited[i] = 1;
      }
    }
  }
  std::cout << '\n';
}

void DFS(vector<vector<int>> &map) {
  std::cout << '\n';
  stack<int> s;
  auto visited_num = 0;
  auto visited = vector<int>(map.size(), 0);
  s.push(0);
  visited[0] = 1;
  ++visited_num;
  while (!s.empty() | visited_num != map.size()) {
    if (s.empty()) {
      for (int i = 0; i != map.size(); ++i)
        if (visited[i] == 0) {
          s.push(i);
          visited[i] = 1;
          break;
        }
      if (s.empty())
        return;
    }
    auto cur = s.top();
    s.pop();
    std::cout << cur << ' ';
    for (int i = 0; i != map.size(); ++i) {
      if (visited[i] == 0 && map[i][cur] > 0) {
        s.push(i);
        visited[i] = 1;
      }
    }
  }
  std::cout << '\n';
}

int main(int argc, char const *argv[]) {
  auto n = 10;
  vector<vector<int>> map(n, vector<int>(n));
  { /*初始化*/
    random_device d;
    for (int i = 0; i != map.size(); ++i) {
      for (int j = i; j != map.size(); ++j) {
        map[i][j] = map[j][i] = d() % 10 - 5;
      }
    }
  }
  // for (auto &entry : map) {
  //   for (auto &x : entry)
  //     std::cout << x << ' ';
  //   std::cout << '\n';
  // }
  BFS(map);
  DFS(map);
  return 0;
}

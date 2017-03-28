#include <iostream>
#include <vector>
using namespace std;

int gcd_Euclid(int a, int b) {
  if (a < b) {
    auto temp = a;
    a = b;
    b = temp;
  }
  while (true) {
    auto r = a % b;
    if (r == 0)
      return b;
    else {
      a = b;
      b = r;
    }
  }
}

int new_index(int i, int k, int n) {
  auto r = (i - k) % n;
  if (r < 0)
    return r + n;
  else
    return r;
}

void move_left(vector<int> &col, int step) {
  auto e = gcd_Euclid(col.size(), step);
  for (int i = 0; i != e; ++i) {
    auto new_pos = new_index(i, step, col.size());
    auto backup = col[0];
    for (int j = 0; j != col.size() / e; ++j) {
      // std::cout << j << "->" << new_pos << '\n';
      auto temp = col[new_pos];
      col[new_pos] = backup;
      backup = temp;
      new_pos = new_index(new_pos, step, col.size());
    }
  }
}

void show(vector<int> &x) {
  for (auto item : x) {
    std::cout << " " << item;
  }
  std::cout << '\n' << '\n';
}

int main(int argc, char const *argv[]) {
  vector<int> x = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  show(x);
  move_left(x, 3);
  show(x);
  move_left(x, 3);
  show(x);

  return 0;
}

#include <iostream>

void show_matrix(int n) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      std::cout << (2 * n - i + j + 1) * (i - j) / 2 + j << ' ';
    }
    std::cout << '\n';
  }
}

int main(int argc, char const *argv[]) {
  auto n = atoi(argv[1]);
  show_matrix(n);
  return 0;
}

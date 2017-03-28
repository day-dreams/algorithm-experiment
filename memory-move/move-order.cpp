#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

void show_move_order(int m, int n, int i) {
  auto backup = i;
  do {
    auto j = (i - m) % n;
    if (j < 0)
      j += n;
    std::cout << setw(-5) << i << " --> " << setw(-5) << j << " , ";
    i = j;
  } while (i != backup);
  std::cout << "" << '\n';
}

int main(int argc, char const *argv[]) {
  int n = 10;
  for (int i = 0; i != n; ++i)
    show_move_order(25, n, i);
  return 0;
}

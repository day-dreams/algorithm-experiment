#include <cmath>
#include <iostream>

double next_x(const double x) { return sqrt((sin(x) + 1) / 9); }

bool accuracy_achieved(const double x) {
  double judge = 9 * x * x - sin(x) - 1;
  if (judge < 0.00001 && judge > -0.00001)
    return true;
  else
    return false;
}

int main(int argc, char const *argv[]) {
  double x = 0.5;
  for (int i = 1; !accuracy_achieved(x); ++i) {
    x = next_x(x);
    std::cout << "ite: " << i << "\tx: " << x << '\n';
  }
  return 0;
}

int gcd_exhaustion(int a, int b) {
  if (a < b) {
    auto temp = a;
    a = b;
    b = temp;
  }
  for (int i = b; i >= 1; --i)
    if (a % i == 0 & b % i == 0)
      return i;
}

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

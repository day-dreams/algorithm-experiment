#include "gcd.h"
#include <benchmark/benchmark.h>
#include <iostream>

using namespace std;

const int a = 56566, b = 64238;

static void BM_gcd_exhaustion(benchmark::State &s) {
  while (s.KeepRunning())
    for (int i = 0; i != s.range(0); ++i)
      gcd_exhaustion(a, b);
}

static void BM_gcd_Euclid(benchmark::State &s) {
  while (s.KeepRunning())
    for (int i = 0; i != s.range(0); ++i)
      gcd_Euclid(a, b);
}

BENCHMARK(BM_gcd_exhaustion)->Range(8, 8 << 10);
BENCHMARK(BM_gcd_Euclid)->Range(8, 8 << 10);

BENCHMARK_MAIN();

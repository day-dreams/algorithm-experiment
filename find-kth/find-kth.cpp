#include <iostream>
#include <vector>

using namespace std;

/*
  来自快速排序
*/
int participant(vector<int> &vec, int begin, int end) {
  auto povit = vec[begin];
  while (begin < end) {
    while (povit <= vec[end] && begin < end) {
      --end;
    }
    vec[begin] = vec[end];
    while (povit >= vec[begin] && begin < end) {
      ++begin;
    }
    vec[end] = vec[begin];
  }
  vec[begin] = povit;
  return begin;
}

/*
  寻找第k小元素.排序部分元素,比快排更快
*/
int find_kth(vector<int> &v, int begin, int end, int k) {
  auto index = participant(v, begin, end);
  if (index - begin + 1 == k)
    return v[index];
  else if (index - begin + 1 > k)
    return find_kth(v, begin, index - 1, k);
  else
    return find_kth(v, index + 1, end, k - index + begin - 1); /*注意更新k*/
}

int main(int argc, char const *argv[]) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto kth = 5;
  std::cout << find_kth(v, 0, v.size() - 1, kth) << '\n';
  return 0;
}

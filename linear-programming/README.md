# 线性规划

## 待优化的

  * 实现完美转发，避免矩阵的复制
  * 更好的处理值覆盖问题
  * 改变算法终止的应对
  
## 后记

算法导论确实不错。对于一个多元线性多项式，我的想法是表示成一个以pair为元素的vector，或者其他形式的vector组合，这样没有额外的空间开销。但是对于线性规划，会带来复杂的抽象：基本多项式，目标多项式，约束多项式，标准型约束多项式，松弛型约束多项式，它们之间会有复杂的继承关系，编码时会带来额外的代码负担。这两天被这个问题缠住，又没有集中的大块时间，一直没有开始架构、实现工作。

刚刚跳着翻了下算法导论，发现它直接把多个约束简化成矩阵，直接提炼成矩阵，定义相应的操作。这种简单粗暴的思路直接解决了我的问题。不过也有点不好的地方，无法划清概念之间的距离，可能会导致扩展时的编码困难。总的来说，这个想法还是很好的。也可能是我的错，总有个毛病，潜意识里为了印证学过的概念，忍不住把问题复杂化。

还是缺少透过现象看本质的能力。引以为戒。

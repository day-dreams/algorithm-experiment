# 最大公约数算法

## 穷举法
### 证明略
### 伪代码
```python
  def gcd_exhaustion(a,b):
    if a < b:
      swap(a,b)
    for r = b to 1:
      if (a%r == 0) and (b%r==0):
        return r
```

## 欧几里得法
### 算法思想
>正整数a和b (a>b) 的最大公约数同时也是b和（$a\pmod b$）的最大公约数

证明如下:  
>(1) 设 $r = a \pmod b$， 即：  
$a = b * k + r$  
取a和b的公约数d，上式两边对d作商，有：  
$a \div d = b \div d \times k+r\div d$  
显然两边同时为整数，则d是r的约数,且是r和
b的公约数  
(2) 设 $r = a \pmod b$,d为r和b的公约数，  
同样对$a = b * k + r$两边作商，有  
$a \div d = b \div d \times k+r\div d$  
同理，d也是a的公约数。  

>由(1)(2)可得，a、b的公约数和b、$a\pmod b$的公约数按大小顺序一一对应。结论得证。


### 伪代码
```python
  def gcd_Euclid(a,b):
    if a < b:
      swap(a,b)
    c = a % b
    return gcd_Euclid(b,c)
```

## 实现测试
下面是对 56566 和 64238 求最大公约数的测试结果,明显看出欧几里得算法效率更高。当然，a和b的取值影响二者的效率；由于不方便使a和b随机化，测试结果不代表普遍结论。  
```
--------------------------------------------------------------
Benchmark                       Time           CPU Iterations
--------------------------------------------------------------
BM_gcd_exhaustion/8       2296842 ns    2296703 ns        265
BM_gcd_exhaustion/64     18383722 ns   18382721 ns         38
BM_gcd_exhaustion/512   146901286 ns  146893895 ns          5
BM_gcd_exhaustion/4096 1175558090 ns 1175498825 ns          1
BM_gcd_exhaustion/8192 2349127077 ns 2349005938 ns          1
BM_gcd_Euclid/8               870 ns        870 ns     792697
BM_gcd_Euclid/64             6844 ns       6843 ns     100601
BM_gcd_Euclid/512           54588 ns      54585 ns      12559
BM_gcd_Euclid/4096         437100 ns     437077 ns       1601
BM_gcd_Euclid/8192         874482 ns     874435 ns        790

```

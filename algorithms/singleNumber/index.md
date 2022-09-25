[上一页](../index.md)

为什么说异或很神奇呢

想象这样一种对2进制数的运算BOp，支持交换律（所以位置无关，数组可以任意调换位置），且两个相等的数运算结果为0（保证调换之后可以相邻的抵消），自然的，01和10的运算结果要相等且只能等于1(要不然只存在零了)

可以写出如下表格

|  0   |  0   |  0   |
| :--: | :--: | :--: |
|  0   |  1   |  1   |
|  1   |  0   |  1   |
|  1   |  1   |  0   |

这是啥？？这不就是异或么。所以不是异或神奇，是这些运算性质保证了我们只能用异或（至少在二进制上）

有了这些神奇的性质，我们可以做什么呢？

看一下经典例题

[Single Number](https://leetcode.com/problems/single-number/solution/)

很显然，可以证明如下，对于任意序列，因为异或的交换律，我们可以通过调换位置使得所有出现两次的数相邻

a^b^a^c^b = (a^a)^(b^b)^c = c

接下来看这道题

[Single Number II](https://leetcode.com/problems/single-number-ii/)

你看，这里我们用异或显然不行了，因为他重复的数是出现三次。不重复的出现一次。

那我们该怎么办呢？

不要紧啊，异或只是我们推导出来的一个法则而已，我们还是动用原来的法则，自己定义一个运算呗，我们要求这个运算

- 满足交换律
- 三个相同的数连续运算结果为0
- 0和a运算结果 bop(0,a) 能够推导出来a的值

进制都无所谓了，我们来定义一下这个表格

| 累计结果 | 遇到的数 |      |
| -------- | -------- | ---- |
| 0        | 0        | 0    |
| 0        | 1        | 1    |
| 1        | 0        | 1    |
| 1        | 1        | 2    |
| 2        | 0        | 2    |
| 2        | 1        | 0    |

可以看出这是

bop(a,b) = (a+b)%3

仅针对每位而言

ok，done。 如果有负数，按位取反+1就行了

还有更有趣的

[Single Number III](https://leetcode.com/problems/single-number-iii/)

如果有两个数出现了一次，其他所有数出现了两次呢

这也就意味着我们只知道x^y的结果，我们怎么样才能算出x,y呢？

这里涉及一个思想，既然我们没法直接算出，我们可以把原问题分成两部分啊。

比如结果是00000010

我们根据异或的结果可以把原数组分成两部分，第一部分是第二位是0的，第二部分是第二位是1的。这样子我们就把原问题分成了两个小问题，每个小问题可以分开求解。

太机智了！
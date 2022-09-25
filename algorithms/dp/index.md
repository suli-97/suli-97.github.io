[返回上页](../index.md)

# <center>动态规划</center>

大部分dp题目是能通过类似于这种形式解决的
$$
\begin{align}
dp[n] &= a_1\cdot dp[n-1]+a_2\cdot dp[n-2]+...+a_k\cdot dp[n-k]\\
&= \sum_i^ka_i\cdot dp[n-i]
\end{align}
$$
大多数时候$a_i$和$dp[i]$都是整数，这个形式很好定义，关键是状态的选择，是一门大学问。

怎么去选择状态呢，如下要求

1. 由前一刻状态能推导出下一刻状态
2. 状态链可以推导出我们想要的结果，一般是取最后一个状态
3. 状态最好不要由操作定义，因为操作有历史效应，状态是无历史效应的，后面一刻的状态最好只取决于前k个状态，k<=i,最好为1。
4. 比较好的定义方式不是 我在index做了什么，而是index结束后会怎么影响我下一步。

例题：

- [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

  想象一下，这道卖股票题的变种。在每一天，三种不同状态决定了我能做出的操作

  - 我持有股票，所以我今天能什么都不做或者卖
  - 我没有持有股票，我第二天能什么都不动或者买
  - 我没有持有股票，且我是今天刚卖的，所以第2天只能什么都不能做

  在这里我们根据合法操作的不同定义出了三种状态

- 

但是有一部分题目需要更复杂的一维dp，我们需要用一个向量而不是一个数来表示当前状态，相应的 $a_i$ 也就是一个矩阵而不是一个数，这个时候怎么定义前一刻的状态最有利于我们导出下一刻状态，这就是一门学问。

比如

- 堆箱子(忘了哪道题了，大致就是只给你$2\cdot 1$的矩形，问你$2*n$的长方体有多少种堆法)

- 三维堆箱子(只给你$2*1*1$的箱子，问$n*2*2$的柱子有多少种堆法)

- 涂篱笆[276. Paint Fence][https://leetcode.com/problems/paint-fence/]

  这道题我们要把状态定义为dp[n] 为 $\begin{bmatrix}单色结尾[n]\\ 双色结尾[n]\end{bmatrix}$,

  这样定义我们就可以很容易的写出状态方程
  $$
  dp[n] = \begin{bmatrix}k-1&k-1\\1&0\end{bmatrix}dp[n-1]
  $$

二维

### 三维DP

这种一般都是超级难题了，建议课后熟读并背诵😭

[312. Burst Balloons](https://leetcode.com/problems/burst-balloons/)

扎气球，dp[i,j,k]表示扎完i-j这一段且k为最后一个在i-j中被扎的，其他的不动，所能享有的最高分数
$$
dp[i,j,k] = max(dp[i,k-1,:]) + max(dp[k+1,j,:]) + nums[i-1]*nums[j+1]*nums[k]
$$

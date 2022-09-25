[返回上页](../index.md)

# <center>拓扑排序</center>

这个一般是解决有向图判环和排序的问题。

这么说吧，如果一个有向图没有环（从a到b可以有多条路径，但是不可能既能从a到b也能从b到a），我们就能给他们定义一个根据指向的排序关系(可能不唯一)。

经典例题

[269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)

这题就是如果不存在环，则定义出一个排序关系。

很简单
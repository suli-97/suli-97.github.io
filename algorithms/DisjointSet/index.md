[返回上一页](../index.md)

# <center>并查集</center>

来一手标准实现吧

```python
class DisjointSet:
    def __init__(self, n):
        self.fa = [i for i in range(n)]
    def find(self, x):
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])
        return self.fa[x]
    def union(self, x, y):
        fax = self.find(x)
        fay = self.find(y)
        self.fa[fay] = self.fa[fax]
```

可以做的题有

[无向图判树](https://leetcode.com/problems/graph-valid-tree/submissions/)
[返回上页](../index.md)

# nth_element

这个函数接受的参数为

Nth_element(nums.begin(),nums.begin()+k,nums.end(),compare)

其中compare为自定义比较函数



他会找出按照compare排序后索引为k的数，并放在索引k处，另外的附加好处是自动帮你partition好，大的在右边，小的在左边。

可以用来秒杀一些题，比如[lc973](https://leetcode.com/problems/k-closest-points-to-origin/submissions/)

```c++
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n = points.size()-k;
        nth_element(points.begin(),points.begin()+n,points.end(),[](vector<int>& a, vector<int>& b){
        return a[0]*a[0]+a[1]*a[1]>b[0]*b[0]+b[1]*b[1];
    });
        return vector<vector<int>>(points.begin()+n,points.end());
    }
};
```


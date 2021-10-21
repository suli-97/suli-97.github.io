[返回上一页](../index.md)

# <center>经典动态规划</center>

[原题](https://leetcode.com/problems/longest-increasing-subsequence/)

这题为啥经典呢，因为有太多变种了，而且nlogn的最简单的解法也很trick

这道题的dp是$dp[i][t]$是从Num[0]到Num[t]的长度为i+1的上升子序列的末尾的最小值。

很绕是吧

其实就是利用了当t为一定值时，dp[i]肯定是严格递增的这一特性（很intuitive的其实，因为你想，肯定越短的上升序列末尾值越小

然后每次到Num[t]更新dp就行了，找到第一个大于等于Num[t]的dp[k]，然后让dp[k] = min(dp[k], Num[t])(这里取最小值是因为对于后面的数来说，长度相同的序列，末尾值越小，我越能占的越多，对后面的数来说，你越小越好，如果长度一样，末尾值大的后续肯定也是末尾值小的后续，反之则不然)

```c++
int lengthOfLIS(vector<int>& nums) {
  vector<int> dp(nums.size(),INT_MAX);// 这么初始化是因为后面要取min
  dp[0] = nums[0];
  int m = 0;
  for(int x:nums){
    int i = lower_bound(dp.begin(),dp.end(),x)-dp.begin();
    dp[i] = min(x,dp[i]);
    m = max(m,i);
  }
  return m+1;
}
```


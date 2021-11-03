[返回上页](..)

问题： 对一个无序数组寻找一个盒子数=n的一个分割-就是把数组分成连续的n- 使得所有（盒子内部的和）的最大值最小。

解法：

```c++
int f(vector<int> nums, int n){
	vector<int> prefix = nums;
	for(int i=1;i<nums.size();i++)
		prefix[i] += prefix[i-1];
	vector<vector<int>> dp(nums.size(),vector<int>(n+1));
	for(int h=1;h<=n;h++)
		dp[0][h] = nums[0]; 
	for(int i=1;i<nums.size();i++)
		dp[i][1] = dp[i-1][1] + nums[i];
	for(int i=1;i<nums.size();i++){
		for(int h=2;h<=n;h++){
			vector<int> widths;
			for(int j=0;j<i;j++){  //这里用二分查找更快
				int width = prefix[i] - prefix[j];	
				width = max(width, dp[j][h-1]);
				widths.push_back(width);
			}
			dp[i][h] = *min_element(widths.begin(),widths.end());
		}
	}
	return dp[nums.size()-1][n];
}
```

还是dp

$dp[i][h]$ 定义为从0到i的数，放进h个盒子里，内部和最大的盒子的最小能取多少。


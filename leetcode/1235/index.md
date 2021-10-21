[返回上一页](../index.md)

# <center>经典动态规划</center>

[原题](https://leetcode-cn.com/problems/maximum-profit-in-job-scheduling/)

显然这道题我们不能再用先做截止日期靠前的这个贪心算法了，因为附带了权重

做这种时间节点的问题，如果大概一想没有O(n)的算法的话，直接先排序再说(但凡涉及区间的问题基本都是这)，那么这道题具体怎么排序呢？

把开始时间和结束时间放在一起排！

for example：

输入：startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]

| 编号   | 1    | 2    | 3    | 4    | 5    |
| ------ | ---- | ---- | ---- | ---- | ---- |
| startT | 1    | 2    | 3    | 4    | 6    |
| endT   | 3    | 5    | 10   | 6    | 9    |
| profit | 20   | 20   | 100  | 70   | 60   |

我们把开始时间和结束时间放一起排序，$S_i, E_i$分别代表编号为i的任务的开始时间和结束时间(注意如果时间相同，结束时间排在开始时间前)

$S_1=1,S_2=2,E_1=3,S_3=3,S_4=4,E_2=5,E_4=6,S_5=6,E_5=9,E_3=10$

好了，这些时间节点就是按时间顺序所有我们需要做出判断的时间节点了

现在为每个$E_i$定义一个状态, $P(E_i)$代表从0到$E_i$时间内能赚到的最大收益

已知前一个$P(E_i)$,怎么算出下一个$P(E_i)$呢？转移方程该怎么写呢？

很显然，前一个任务做完后，新做的任务的收益会累加到之前的收益。

所以我们可以在碰到每个$S_j$的时候取之前的最近的$P(E_i)$,然后令$P(E_j)=P(E_i)+Profit_j$

但是很显然，真到了$E_j$的时候，最大收益不一定是这个值，因为我们还可以选择做其他的任务哇，说不定赚更多。

所以我们在遍历到每一个$E_i$时，都要和之前的$P(E_i)$做比较，选择较大的作为真实的。

以上题为例，我们每次遍历到$S_i$，就更新$P(E_i)$,每次遍历到$E_i$,就和之前的比大小

| 时间点           | S1   | S2   | E1   | S3   | S4   | E2   | E4       | S5   | E5        | E3         |
| ---------------- | ---- | ---- | ---- | ---- | ---- | ---- | -------- | ---- | --------- | ---------- |
| 可能收益         |      |      | 20   |      |      | 20   | 90=70+20 |      | 150=90+60 | 120=100+20 |
| 最大收益$P(E_i)$ |      |      | 20   |      |      | 20   | 90       |      | 150       | 150        |

我们可以用一个数组来存储$P_i=P(E_i)$

```c++
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<int> dp(n);
        vector<vector<int>> time;
        for(int i=0;i<n;i++){
            time.push_back({startTime[i],i+1});// positive means start time
            time.push_back({endTime[i],-i-1});// negative means end time
        }
        sort(time.begin(),time.end());
        int lastEnd = 0;
        for(vector<int> t:time){
            if(t[1]>0){
                int index = t[1]-1;
                dp[index] = lastEnd+profit[index];
            }else{
                int index = -t[1]-1;
                lastEnd = dp[index] = max(dp[index],lastEnd);
            }
        }
        return lastEnd;
    }
};
```

因为我们排序后只遍历了一遍数组，所以时间复杂度为O(nlogn)
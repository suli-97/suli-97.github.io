[返回上一页](..)

# <center>接雨水与包围圈</center>

[接雨水](https://leetcode-cn.com/problems/trapping-rain-water-ii/)

- 定义三个概念：

  * 点高 = 某点本身的高度

  * 蓄水高度  = 某点尝试蓄水之后的水位高，不会低于这个点本身的高度

  * 蓄水量 = 蓄水高度 - 这个点本身的高度

  

- 与接雨水Ⅰ要求一眼看出 在某个数学维度上可以构造一个单调函数 不同，接雨水二的主要难点在于包围这个概念。也即【外层环上的最低点的点高】决定【内部区域所有点】的最低【蓄水高度】。（一圈都给你兜圆了你能流哪去？

- 但是也只有【内部区域】中挨着【外层环上最低木板】的那一点的真实【蓄水量】是可以确定的。因为某一点具体的【蓄水高度】仅取决于四周四个点最低的【蓄水高度】和自己【点高】，而由前文可知，在这一点四周点的【蓄水高度】是不会低于【环上最低点的点高】，而又已知这一点挨着【环上的最低点】，所以这一点四周的四个点最低蓄水高度就是【外层环最低点的点高】，所以这一点的【蓄水高度】就是

- <CENTER>min(【这一点的点高】,【外层环最低点的点高】)</CENTER>

- 已知这一点的【蓄水高度】和这一点的【点高】，就能很轻松求出这一点的真实【蓄水量】

- 又因为已知这一点的【蓄水高度】，就可以构造新的【外层环】，继续求解【新环上的最低点】和【新环内部挨着环上最低点的点】的真实【蓄水量】了。

- 因为要不断找到外层环上的最低点，我们可以维持一个小顶堆数据结构来降低寻找的复杂度。（显而易见）

- ```c++
  class Solution {
  public:
      int trapRainWater(vector<vector<int>>& heightMap) {
          if(heightMap.empty() || heightMap[0].empty()) return 0;
          int m = heightMap.size(), n = heightMap[0].size(), res = 0;
          bool visited[m][n]; memset(visited, 0, m*n);
          auto compare = [](vector<int>& a, vector<int>& b){return a[0] > b[0];};
          priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> q(compare);
  
          for(int i=0; i<m; i++) {
              visited[i][0] = true;
              visited[i][n-1] = true;
              q.push( {heightMap[i][0], i, 0} );
              q.push( {heightMap[i][n-1], i, n-1} );
          }
          for(int j=0; j<n; j++) {
              visited[0][j] = true;
              visited[m-1][j] = true;
              q.push({heightMap[0][j], 0, j} );
              q.push({heightMap[m-1][j], m-1, j} );
          }
          
          int seaLevel = 0;
          int di[4] = {1,-1,0,0};
          int dj[4] = {0,0,1,-1};
          while(!q.empty()){
              auto tmp = q.top();
              q.pop();
              int h=tmp[0], i=tmp[1], j=tmp[2];
              seaLevel = max(seaLevel,h);
              for(int index=0;index<4;index++){
                  int i_ = i+di[index], j_=j+dj[index];
                  if(i_<0 || i_>=m || j_<0 || j_>=n || visited[i_][j_]) continue;
                  if(seaLevel > heightMap[i_][j_]) res += seaLevel - heightMap[i_][j_];
                  visited[i_][j_] = true;
                  q.push({heightMap[i_][j_],i_,j_});
              }
          }
          return res;
      }
  };
  ```

  
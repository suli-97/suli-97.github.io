# <center>接雨水与包围圈</center>

- 与接雨水Ⅰ要求一眼看出 在某个数学维度上可以构造一个单调函数 不同，接雨水二的主要难点在于包围这个概念。也即外层的最低板决定内层的蓄水量。（一圈都给你兜圆了你能流哪去？

- 但是也只有内层边界挨着外层最低木板的一点蓄水量是可以决定的，（某一点具体的蓄水量仅取决于四周最低的蓄水量），由蓄水的传导性可知（需要证明），在这一点周围的蓄水是不会低于最低木板的，而又已知这一点挨着最低木板，所以这一点的蓄水量就是max（0，最低木板的高度-这一点的高度）。把这个点的真实蓄水量算出之后，就可以抛弃之前的木板，把这个点当成新木板，继续求解新环内的最低木板周围点的真实蓄水量了。

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

  
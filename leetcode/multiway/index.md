[返回上页](..)

Question: 

给定一组二维点 (Xi,Yi), 你可以用无数根直线去拟合使得方差之和最小，但是每多加一根线有额外惩罚K，问怎么拟合使得总惩罚=方差之和+L*线的数量 最小

另外，在x轴上不连续的点不能被同一根线拟合。我们本质上是在对原数组在x轴排序完寻找一个分割 例如 对点按x轴排序之后是（P1,P2| P3,P4| P5,P6,P7） 这么分割最小。

Answer：

在每一点dp

定义dp[i]=点0到点i的最小loss。

dp[i] = min_j (dp[j]+LSE(j,i)+K)


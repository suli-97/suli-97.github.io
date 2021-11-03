[返回上页](..)

![image-20211029233243179](/Users/lisu/Library/Application Support/typora-user-images/image-20211029233243179.png)

# Shortest wireless path sequence

Suppose the E is given in the form of Adjancy Matrix with size $|V|\times|V|$.

### 1. Suppose it is possible to choose a single path P that is an s-t path in each of the graphs $G_0, G_1, . . . , G_b$. Give a polynomial-time algorithm to find the shortest such path.

**High Level Description**

Since we can choose a single path P from them, there must be a path that is constant in these graphs. So we can find the intersection of the edges where P must be in. Since each $E_i$ is a bool matrix, we can find its intersection with $E_j$ simply by element-wise multiplying. And we do this element-wise multiplication $b$ times to get the intersection of $E_0,E_1,...,E_b$

Now we have the intersection $E$, we wanna find the shortest path in it. It is trivial that we could run BFS here to find the shortest path starting from node $s$ to $t$.

**Correctness Proof**

If there is a constant P, then P must lies in the intersection $E$. Actually all constant path lies in $E$.

So the shortest path in $E$ is $P$.
$$
P\in E_1,P\in E_2,...,P\in E_b\Rightarrow P\in E_1\cap E_2\cap...\cap E_b
$$
**Time Complexity**

The element-wise multiplication of $E_i$ and $E_j$ takes $O(|V|^2)$ 

And we need to do this multiplication b times. So this step takes $O(b|V|^2)$

And we can run bfs in $O(|V|)$.

So the overall time complexity is $O(b|V|^2)$

### 2. Give a polynomial-time algorithm to find a sequence of paths P0, P1, . . . , Pb of minimum cost, where $P_i$ is an s-t path in Gi for i = 0, 1, . . . , b.

**High Level Description**

We define $P_{i,j}$ to be the shortest constant path from s to t in $\{G_i,G_{i+1},...,G_j\}$. Obviously $P_{i,i}$ is the shortest path in $G_i$

We define the $MinCost_{i,j}$ to be the minimum cost from $G_i$ to $G_j$
$$
MinCost_{i,j}=\begin{cases}(j-i+1)l(P_{i,j})&\exist P_{i,j}\\ \infty&else\end{cases}
$$


We define $MinCost_i$ which is the minimum cost from $G_0$ to $G_i$. Assume in the optimal answer, the last change of path happens at $P_j\ne P_i$, so $MinCost_i$ would be $MinCost_j+MinCost_{j+1,i}+K$. We can test all j and find the optimal as the $MinCost_i$. So we can write the dynamic formula.
$$
MinCost_i = \begin{cases}-K&i=-1\\ \min_{j=-1}^{i-1} (MinCost_j+MinCost_{j+1,i}+K)&else\end{cases}
$$

**Correctness Proof**

**base case**

we have
$$
\begin{align}
MinCost_0&=\min_{j=-1}^{-1} (MinCost_j+MinCost_{j+1,0}+K)\\
&=MinCost_{-1}+MinCost_{0,0}+K\\
&=-K+l(P_{0,0})+K\\
&=l(P_{0,0})\\
MinCost_1&=\min_{j=-1}^{0} (MinCost_j+MinCost_{j+1,1}+K)\\
&=min(MinCost_{0,1},MinCost_0+MinCost_{1,1}+K)\\
&=min(2\cdot l(P_{0,1}),l(P_{0,0})+l(P_{1,1})+K)
\end{align}
$$
these base cases are correct.

**Induction Step**

If there is an optimal solution of $\{P_0,P_1,...,P_b\}$. Then the last changing of path must happen at somewhere $j<b$. So we can compare all the possible changing point and pick the best one.

In this way, we can guarantee that we tried all possible solutions and the answer we find must be the minimum.

So if $\forall j<i,MinCost_j$ is correct, we would get the correct $MinCost_i$

**Summary**

According to the induction principle, for all $i>=0$, we would have correct result.



**Time Complexity**

In every step when we calculating $MinCost_{i}$, we need to calculate all $P_{j,i},\forall j\le i$. We can do this in $O(b|V|^2)$ since we can store the $\cap_{k=j}^i E_j$ for calculating $\cap_{k=j-1}^iE_k$.

And we need to traverse the whole array and do the above thing b times. So the overall time complexity would be $O(b^2|V|^2)$


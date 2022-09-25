[返回上页](..)

这又是一道非常典型的partition 问题啊，

所有的partition问题基本都是这种解法， 从数组0-i的最后一个partition的起始位置来考虑dp

一般是这种形式 i代表数组的0-i-1这长度为i的这一段，k代表分为k个partition，很显然为了有意义i必须大于等于k

dp[i, k] = someFunction（  [ Dp[j, k-1]    for  j  in  range(k-1) ]  ）

j从k-1开始是为了让j大于等于k-1
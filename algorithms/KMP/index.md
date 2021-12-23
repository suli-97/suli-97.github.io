市面上通常的KMP算法是错误的嗷

abcabcd的next数组应该是

a     b    c     a    b    c   d

-1    0    0    -1   0    0   3

而不是

0    0.    0.    1   2.   3.  0 

嗷
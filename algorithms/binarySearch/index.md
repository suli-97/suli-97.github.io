所有二分搜索的原则：不错过，问题规模在缩小，不浪费

当寻找插入位置时，我们记住不能让high=mid-1.因为我们寻找的是第一个大于等于target的数的位置，如果-1就会错过。但是可以low=mid+1，因为这样不会错过，而且不会浪费。 [题目](https://leetcode.com/problems/search-insert-position/submissions/)

```c++
int searchInsert(vector<int>& nums, int target) {
  if(target>nums.back()) return nums.size();
  int low = 0, high = nums.size()-1;
  while(low<high){
    int mid = (low+high)/2;
    int x = nums[mid];
    if(x==target) return mid;
    if(x<target)
    low=mid+1;
    else
    high=mid;
  }
  return low;
}
```

当已知一定存在target时，我们要让high=mid-1。[题目](https://leetcode.com/problems/guess-number-higher-or-lower/)

```c++
int guessNumber(int n) {
  int low = 1, high=n;
  while(low<high){
    int mid = low+(high-low)/2;
    int r = guess(mid);
    if(r==0) return mid;
    if(r==1) low = mid+1;
    else high = mid-1;
  }
  return low;
}
```


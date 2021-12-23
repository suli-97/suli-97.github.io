[返回上页](..)

# 二分搜索之大总结

### 二分查找第一个符合条件的元素

 找到第一个出现满足条件的⬇️, 全部可以复用这套逻辑，所以背死这个搜索模版

```python
# 找到符合条件的第一个元素的索引，若不存在返回 -1
def first(nums, valid):
	if not valid(nums[-1]):
		return -1
	st = 0
	ed = len(nums)-1
	while st<ed:
		mid = st + (ed-st)//2
		if valid(nums[mid]):
			ed = mid
		else:
			st = mid + 1
	return st
```

### 常见的转化

- 找到符合条件的最后一个, 若不存在返回-1

  ```python
  def last(nums, valid):
  	index = first(nums,lambda x : not valid(x))
  	return  index - 1 if index != -1 else len(nums) - 1
  ```

- 查找target插入位置

  ```python
  def insertPosition(nums, target):
  	index = first(nums, lambda x: x>=target)
  	return index if index!=-1 else len(nums)
  ```

- 查找有序数组里是否存在target

  ```python
  def exist(nums, target):
  	valid = lambda x: x>=target
  	index = first(nums,valid)
  	return index != -1 and nums[index]==target
  ```

### 练习题

- [题目](https://leetcode.com/problems/search-insert-position/submissions/)

- [题目](https://leetcode.com/problems/guess-number-higher-or-lower/)

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
def last(nums, valid):
	index = first(nums,lambda x : not valid(x))
	return  index - 1 if index != -1 else len(nums) - 1

def insertPosition(nums, target):
	index = first(nums, lambda x: x>=target)
	return index if index!=-1 else len(nums)

def exist(nums, target):
	valid = lambda x: x>=target
	index = first(nums,valid)
	return index != -1 and nums[index]==target
nums = [0,1,2,3,4,4,4,4,5,5,6,7,7,7,8,9]
valid = lambda x: x >10
print( exist(nums,6))
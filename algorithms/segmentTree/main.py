def f(nums):
	nums.sort()
	n = len(nums)
	deleted = set([1])
	maxDivisors = 0
	for i in range(n-1, -1, -1):
		divisors = 0
		if nums[i] in deleted:
			continue
		for j in range(i, -1, -1):
			if not nums[i]%nums[j]:
				divisors += 1
				deleted.add(nums[j])
		maxDivisors = max(maxDivisors, divisors)
	return maxDivisors

nums = [2,4,6,8,10,12,14,16,18,20]
res = f(nums)
print(res)
def getNext(pattern):
	n, k = len(pattern), 0
	next = [-1 for _ in range(n+1)]
	for i in range(1,n):
		if pattern[i]==pattern[k]:
			next[i] = next[k]
		else:
			next[i] = k
		while i!=-1 and pattern[k]!=pattern[i]:
			k = next[k]
		k += 1
	next[-1] = k
	return next
def search(target, pattern):
	next = getNext(pattern)
	i, j = 0, 0
	res = []
	while i<len(target):
		if j<len(pattern) and (j==-1 or target[i]==pattern[j]):
			i += 1
			j += 1
		else:
			if j==len(pattern):
				res.append(i-len(pattern))
			j = next[j]
	if j==len(pattern):
		res.append(i - len(pattern))
	return res
# 背死这个kmp模版！！！！！
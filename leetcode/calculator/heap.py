from random import random
import heapq
x = [random() for _ in range(10)]
heapq.heapify(x)
heapq.heappush(x,random())
while x:
	print(heapq.heappop(x))
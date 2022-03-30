class Node():
	def __init__(self,size=100):
		self.hash = [None for _ in range(size)]
	def search(self,key):
		quo, remainder = self.parse(key)
		if type(self.hash[remainder])==Node:
			return self.hash[remainder].search(quo)
		return self.hash[remainder] == quo
	def add(self,key):
		quo, remainder = self.parse(key)
		if self.hash[remainder]==None:
			self.hash[remainder] = quo
		elif type(self.hash[remainder])==Node:
			self.hash[remainder].add(quo)
		elif self.hash[remainder]!=quo:
			another = self.hash[remainder]
			self.hash[remainder] = Node()
			self.hash[remainder].add(another)
			self.hash[remainder].add(quo)
	def remove(self, key):
		quo, remainder = self.parse(key)
		if type(self.hash[remainder]) == Node:
			self.hash[remainder].remove(quo)
		elif self.hash[remainder]==quo:
			self.hash[remainder] = None
	def parse(self,key):
		return key//len(self.hash), key %len(self.hash)
root = Node()
for i in range(200):
	root.add(i)
print(1)
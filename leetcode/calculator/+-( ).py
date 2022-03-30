def eatExpr(s):
	if s=='':
		return 0
	if s[0]=='-':
		s = '0' + s
	term, s = eatTerm(s)
	if s=='':
		return term
	op, s = eatOp(s)
	return op(eatExpr(s), term)
def eatOp(s): #返回一个函数
	if s[-1]=='+':
		return (lambda x,y:x+y), s[:-1]
	return lambda x,y: x-y, s[:-1]
def eatTerm(s):
	pa = 0
	i = len(s)-1
	while i>=0:
		if pa==0 and (s[i]=='+' or s[i]=='-'):
			break
		if s[i]==')':
			pa += 1
		if s[i]=='(':
			pa -= 1
		i -= 1
	if s[-1]==')':
		return eatExpr(s[i+2:-1]), s[:i+1]
	return evalInt(s[i+1:]), s[:i+1]
def evalInt(s):
	return int(s)

s = "(-1+5)+((4+5+2)-3)+6+8"
x = eatExpr(s)
print(x)
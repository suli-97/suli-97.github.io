# from typing import Callable
# class Interval:
#     def __init__(self, st, ed, handler:Callable[[object],None]):
#         self.st = st
#         self.ed = ed
#         self.mid = None
#         self.left, self.right = None, None
#         handler(self)
#     def update(self, st, ed, handler):
#         if ed <= st:
#             return
#         if (self.st, self.ed) == (st, ed):
#             handler(self)
#         if self.mid == None:
#             self.mid = st if self.st != st else ed
#             self.left = Interval(st, self.mid, handler)
#             self.right = Interval(self.mid, ed, handler)
#         self.left.update(st, min(ed, self.mid), handler)
#         self.right.update(max(st,self.mid), ed, handler)
    
# rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]

# root = Interval()
# handler
# for x0, y0, x1, y1 in rectangles:
def f():
    for i in range(10):
        yield i
x = f()
print(next(x))
print(next(x))
print(next(x))
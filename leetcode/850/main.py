class Node:
    def __init__(self, st = float('-inf'), ed = float('inf'), **kwargs):
        self.st = st
        self.ed = ed
        for key,val in kwargs.items():
            self.__dict__[key] = val
    

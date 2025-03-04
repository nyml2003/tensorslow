class Graph:
    def __init__(self):
        self.nodes = []
        
    def add_node(self, node):
        self.nodes.append(node)
        
    def clear_jacobi(self):
        for node in self.nodes:
            node.clear_jacobi()
            
    def reset_value(self):
        for node in self.nodes:
            node.reset_value(False)
            

graph = Graph()

class Node:
    def __init__(self, parents):
        self.graph = graph
        self.parents = parents
        self.children = []
        self.value = None
        self.jacobi = None
        
        for parent in self.parents:
            parent.children.append(self)
            
        self.graph.add_node(self)
        
    def get_parents(self):
        return self.parents
    
    def get_children(self):
        return self.children
    
    def forward(self):
        for node in self.parents:
            if node.value is None:
                node.forward()
        self.compute()
        
    def compute(self):
        pass
        
    def clear_jacobi(self):
        self.jacobi = None
        
    def reset_value(self):
        self.value = None
        for child in self.children:
            child.reset_value()
    
    def get_shape(self):
        return self.value.shape
    
    def get_dimension(self):
        return self.value.shape[0] * self.value.shape[1]

class Variable(Node):
    def __init__(self, dim, init):
        self.graph = graph
        self.parents = []
        self.children = []
        self.value = None
        self.jacobi = None
        self.graph.add_node(self)
        self.dim = dim
        if init:
            self.value = ones(dim[0], dim[1])
            
    def set_value(self, value):
        self.reset_value()
        self.value = value
        
class Operator(Node):
    pass

class Add(Operator):
    def compute(self):
        shape = self.parents[0].get_shape()
        self.value = zeros(shape[0], shape[1])
        for parent in self.parents:
            self.value = self.value + parent.value
            

a = Variable([3,3], True)
b = Variable([3,3], True)
c = Add([a,b])
print(a.value)
print(b.value)
c.compute()
print(c.value)
a.set_value(eye(3))
c.compute()
print(c.value)

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
            node.reset_value()


graph = Graph()


class Node:
    def __init__(self, parents):
        self.graph = graph
        self.parents = parents
        self.children = []
        self.value = None
        self.jacobi = None
        self.trainable = False

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

    def backward(self, result):
        if self.jacobi is None:
            if self is result:
                self.jacobi = Eye(self.get_dimension())
            else:
                self.jacobi = Zeros((result.get_dimension(), self.get_dimension()))
                for child in self.get_children():
                    if child.value is not None:
                        self.jacobi += child.backward(result) @ child.get_jacobi(self)
        return self.jacobi

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
    def __init__(self, dim, init, trainable):
        self.graph = graph
        self.parents = []
        self.children = []
        self.value = None
        self.jacobi = None
        self.graph.add_node(self)
        self.dim = dim
        self.trainable = trainable
        if init:
            self.value = Normal(0.0, 0.001, self.dim)

    def set_value(self, value):
        self.reset_value()
        self.value = value


class TestNode(Node):
    def compute(self):
        pass


def test_add_node():
    print("测试添加节点到图中")
    node = Variable([2, 2], False, False)
    print("节点是否被添加到graph.nodes:", node in graph.nodes)
    print("graph.nodes当前长度:", len(graph.nodes))


def test_clear_jacobi():
    print("测试清除所有节点的雅可比矩阵")
    node = Variable([1, 1], False, False)
    node.jacobi = Ones([1, 1])
    graph.clear_jacobi()
    print("清除后节点的jacobi是否为None:", node.jacobi is None)


def test_reset_value():
    print("测试重置单个节点的值")
    node = Variable([1, 1], False, False)
    node.value = Ones([1, 1])
    graph.reset_value()
    print("重置后节点的value是否为None:", node.value is None)
    node.value = Array([[1.0]])
    graph.reset_value()
    print("重置后节点的value是否为None:", node.value is None)


def test_reset_value_with_children():
    print("测试重置父节点时子节点也被重置")
    parent = Variable([1, 1], False, False)

    child = TestNode([Variable([1, 1], False, False)])

    parent.value = Ones([1, 1])
    child.value = Ones([1, 1])
    graph.reset_value()

    print("父节点value是否为None", parent.value is None)
    print("子节点value是否为None", child.value is None)


graph.nodes = []
test_add_node()
test_clear_jacobi()
test_reset_value()
test_reset_value_with_children()

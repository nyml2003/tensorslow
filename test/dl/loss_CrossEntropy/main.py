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


class LossFunction(Node):
    pass


class CrossEntropyWithSoftMax(LossFunction):
    def compute(self):
        prob = Softmax(self.parents[0].value)
        value = -Sum(self.parents[1].value * Log(prob))
        self.value = Array(value).reshape([1, 1])

    def get_jacobi(self, parent):
        prob = Softmax(self.parents[0].value)
        if parent is self.parents[0]:
            return (prob - self.parents[1].value).T
        else:
            return (-Log(prob)).T


def test_cross_entropy_with_softmax():
    # 测试计算损失值
    logits = Array([[2.0, 1.0]])
    labels = Array([[1.0, 0.0]])

    # 创建父节点
    logits_node = Variable([1, 2], False, False)
    labels_node = Variable([1, 1], False, False)
    logits_node.set_value(logits)
    labels_node.set_value(labels)
    loss_node = CrossEntropyWithSoftMax([logits_node, labels_node])
    # 执行前向传播
    loss_node.forward()
    print("Computed loss:", loss_node.value)
    actual_jacobi_logits = loss_node.get_jacobi(logits_node)
    print("Actual Jacobian for logits:", actual_jacobi_logits)
    actual_jacobi_labels = loss_node.get_jacobi(labels_node)
    print("Actual Jacobian for labels:", actual_jacobi_labels)


# 运行测试
test_cross_entropy_with_softmax()

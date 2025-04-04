# def range(start, end, step):
#     if step == 0 or step is None:
#         step = 1
#     if end is None:
#         end = start
#         start = 0
#     if step > 0:
#         while start < end:
#             yield start
#             start += step
#     else:
#         while start > end:
#             yield start
#             start += step


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


class Node():
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

    def backward(self, result):
        if self.jacobi is None:
            if self is result:
                self.jacobi = Eye(self.get_dimension())
            else:
                self.jacobi = Zeros([result.get_dimension(), self.get_dimension()])
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
    def __init__(self, dim, init):
        self.graph = graph
        self.parents = []
        self.children = []
        self.value = None
        self.jacobi = None
        self.graph.add_node(self)
        self.dim = dim
        if init:
            self.value = Normal(0.0, 0.001, self.dim)

    def set_value(self, value):
        self.reset_value()
        self.value = value


class Operator(Node):
    pass


class Add(Operator):
    def compute(self):
        self.value = Zeros(self.parents[0].get_shape())
        for parent in self.parents:
            self.value += parent.value

    def get_jacobi(self, parent):
        return Eye(self.get_dimension())


class MatrixMultiply(Operator):
    def compute(self):
        self.value = self.parents[0].value @ self.parents[1].value

    def get_jacobi(self, parent):
        parent0 = self.parents[0]
        parent1 = self.parents[1]
        lhs_shape = parent0.get_shape()
        m = lhs_shape[0]
        n = lhs_shape[1]
        k = parent1.get_shape()[1]
        if parent is parent0:
            # C 对 A 的雅可比矩阵
            t = parent1.value.T
            jacobi = Zeros([m * k, m * n])
            for i in range(m):
                jacobi[i * k:(i + 1) * k, i * n:(i + 1) * n] = t
            return jacobi
        if parent is parent1:
            jacobi = Zeros([m * k, n * k])
            for i in range(m):
                for j in range(n):
                    jacobi[i * k:(i + 1) * k, j * k:(j + 1) * k] = Eye(k) * parent0.value[i, j]
            return jacobi


class Step(Operator):
    def compute(self):
        parent0 = self.parents[0]
        shape = parent0.get_shape()
        self.value = Zeros(shape)
        for i in range(shape[0]):
            for j in range(shape[1]):
                if parent0.value[i, j] >= 0.0:
                    self.value[i, j] = 1.0

    def get_jacobi(self, parent):
        return Zeros(self.parents[0].get_shape())


class LossFunction(Node):
    pass


class PerceptionLoss(LossFunction):
    def compute(self):
        parent0 = self.parents[0]
        shape = parent0.get_shape()
        row = shape[0]
        col = shape[1]
        self.value = Zeros(shape)
        for i in range(row):
            for j in range(col):
                if parent0.value[i, j] >= 0.0:
                    self.value[i, j] = 0.0
                else:
                    self.value[i, j] = -parent0.value[i, j]

    def get_jacobi(self, parent):
        parent0 = self.parents[0]
        shape = parent0.get_shape()
        row = shape[0]
        col = shape[1]
        diag = Zeros([row, col])
        for i in range(row):
            for j in range(col):
                if parent0.value[i, j] < 0.0:
                    diag[i, j] = -1.0
        return Diag(diag.ravel())


x = Variable([3, 1], True)  # 初始化一个 3x1 的随机值
y = Variable([3, 1], True)  # 初始化一个 3x1 的随机值
z = Add([x, y])
x.set_value(Array([[1.0], [-2.0], [0.0]]))  # 设置具体值
step_node = Step([x])
loss_node = PerceptionLoss([step_node])
loss_node.forward()
print("组合 Step 和 PerceptionLoss 的正向传播结果 (损失值):")
print(loss_node.value)
jacobi = loss_node.backward(loss_node)
print("组合 Step 和 PerceptionLoss 的反向传播结果 (雅可比矩阵):")
print(jacobi)

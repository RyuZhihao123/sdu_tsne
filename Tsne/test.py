#encoding = utf-8
import numpy as np
import pylab
import matplotlib.pyplot as plt
import networkx as nx

# n = 3

# data1 = np.ones((n, n))
# # print(range(n))

# data1[range(n), range(n)] = 0


# print(np.sum(data1, 1))

# print(data1.shape)
# print(np.sum(data1, 1).shape)

# a=np.array([0,1,2])
# print(a.shape)

# n0 = 7
# no_dims = 2

# print(d3)

# G = nx.DiGraph()
# G.add_node(0, pos=(0, 0))
# G.add_node(1, pos=(1, 1))
# G.add_edge(0, 1)
# nx.draw(G)
# plt.show()

# arr1 = np.array([1, 2, 3, 4, 5])
# arr2 = np.array([1, 2, 3, 4, 5])
# print(np.multiply(arr1, arr2))# bit mul
# print(arr1*arr2)# bit mul
# print(np.dot(arr1, arr2))# dot product

a = [3, 2, 1, 9, 8]
rank = np.argsort(a)

print(rank)
print(a)

# print(np.sum(np.square(np.subtract(d0, d1))))
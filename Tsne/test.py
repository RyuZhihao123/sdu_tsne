#encoding = utf-8
import numpy as np
import pylab

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


a = np.array([0, 1, 2, 3, 4])
print(np.min(a))
print(np.max(a))
print(np.max(np.min(a), np.max(a)))
# print(d3)
#
#  tsne.py
#
# Implementation of t-SNE in Python. The implementation was tested on Python
# 2.7.10, and it requires a working installation of NumPy. The implementation
# comes with an example on the MNIST dataset. In order to plot the
# results of this example, a working installation of matplotlib is required.
#
# The example can be run by executing: `ipython tsne.py`
#
#
#  Created by Laurens van der Maaten on 20-12-08.
#  Copyright (c) 2008 Tilburg University. All rights reserved.

import os
import numpy as np
import pylab
import matplotlib.pyplot as plt



# # accepted from C++ program
M = []  # (eij, ekl) 
S = {}  # (eij, ekl): s
beta = 0.001

def read_fm_data(filepath):
    pts = []
    labels = []
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            line=line.strip('\n')
            # print(line)
            if line[0] == 'G':
                # edge information is not needed here
                print("Break!")
                break
            #  points
            items = line.split()
            # items = line.split("\t+")
            pt = [float(i) for i in items[:-1]]
            # print(pt)
            pts.append(pt)
            # labels
            labels.append(int(items[-1]))
        return np.array(pts), labels

def read_similarity(filepath):
    M = []  # (eij, ekl)
    S = {}
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            line=line.strip('\n')
            items = line.split()
            # e = (int(i) for i in items)
            # push tuple
            M.append((int(items[0]), int(items[1])))

    # We assume that similarity weights are one
    for m in M:
        # print(m) ?? seems some problems
        S[m] = 1.0
    return S, M


def Hbeta(D=np.array([]), beta=1.0):
    """
        Compute the perplexity and the P-row for a specific value of the
        precision of a Gaussian distribution.
    """

    # Compute P-row and corresponding perplexity
    P = np.exp(-D.copy() * beta)
    sumP = sum(P)
    H = np.log(sumP) + beta * np.sum(D * P) / sumP
    P = P / sumP
    return H, P


def cal_pairwise_dist(x):
    '''(a-b)^2 = a^2 + b^2 - 2*a*b'''
    sum_x = np.sum(np.square(x), 1)
    dist = np.add(np.add(-2 * np.dot(x, x.T), sum_x).T, sum_x)
    return dist


def x2p(X=np.array([]), tol=1e-5, perplexity=30.0):
    """
        Performs a binary search to get P-values in such a way that each
        conditional Gaussian has the same perplexity.
    """

    # Initialize some variables
    print("Computing pairwise distances...")
    (n, d) = X.shape
    D = cal_pairwise_dist(X)
    P = np.zeros((n, n))
    beta = np.ones((n, 1))
    logU = np.log(perplexity)

    # Loop over all datapoints
    for i in range(n):

        # Print progress
        if i % 500 == 0:
            print("Computing P-values for point %d of %d..." % (i, n))

        # Compute the Gaussian kernel and entropy for the current precision
        betamin = -np.inf
        betamax = np.inf
        Di = D[i, np.concatenate((np.r_[0:i], np.r_[i+1:n]))]
        (H, thisP) = Hbeta(Di, beta[i])

        # Evaluate whether the perplexity is within tolerance
        Hdiff = H - logU
        tries = 0
        while np.abs(Hdiff) > tol and tries < 50:

            # If not, increase or decrease precision
            if Hdiff > 0:
                betamin = beta[i].copy()
                if betamax == np.inf or betamax == -np.inf:
                    beta[i] = beta[i] * 2.
                else:
                    beta[i] = (beta[i] + betamax) / 2.
            else:
                betamax = beta[i].copy()
                if betamin == np.inf or betamin == -np.inf:
                    beta[i] = beta[i] / 2.
                else:
                    beta[i] = (beta[i] + betamin) / 2.

            # Recompute the values
            (H, thisP) = Hbeta(Di, beta[i])
            Hdiff = H - logU
            tries += 1

        # Set the final row of P
        P[i, np.concatenate((np.r_[0:i], np.r_[i+1:n]))] = thisP

    # Return final P-matrix
    print("Mean value of sigma: %f" % np.mean(np.sqrt(1 / beta)))
    return P


def pca(X=np.array([]), no_dims=50):
    """
        Runs PCA on the NxD array X in order to reduce its dimensionality to
        no_dims dimensions.
    """

    print("Preprocessing the data using PCA...")
    (n, d) = X.shape
    X = X - np.tile(np.mean(X, 0), (n, 1))
    (l, M) = np.linalg.eig(np.dot(X.T, X))
    Y = np.dot(X, M[:, 0:no_dims])
    return Y


def joint_tsne(X_0=np.array([]), X_1=np.array([]),
               no_dims=2,
               initial_dims_0=50, initial_dims_1=50,
               perplexity=30.0):
    """
        Runs t-SNE on two datasets in the NxD array X to reduce its
        dimensionality to no_dims dimensions. The syntaxis of the function is
        `Y = tsne.tsne(X, no_dims, perplexity), where X is an NxD NumPy array.
    """

    # Check inputs
    if isinstance(no_dims, float):
        print("Error: array X should have type float.")
        return -1
    if round(no_dims) != no_dims:
        print("Error: number of dimensions should be an integer.")
        return -1

    # Initialize variables
    X_0 = pca(X_0, initial_dims_0).real
    X_1 = pca(X_1, initial_dims_1).real

    (n0, d0) = X_0.shape
    (n1, d1) = X_1.shape

    max_iter = 1000
    initial_momentum = 0.5
    final_momentum = 0.8
    # momentum
    eta = 500
    min_gain = 0.01

    Y0 = Y1 = np.array([[ 1.52340745, 1.37944798],
    [ 1.04632537 , 1.94709421],
    [-1.09114757 , -0.47318732],
    [-1.17815386 , -2.53435897],
    [ 0.52436536 , 1.19015593],
    [-0.65184383 , 0.65576772],
    [ 0.162397  , -1.43788719]])
    #Y0 = np.random.randn(n0, no_dims)  # init y problem: change to fix...
    #Y1 = np.random.randn(n1, no_dims)  # init y problem: change to fix...

    # dy0: gradient for data1
    dY0 = np.zeros((n0, no_dims))     
    iY0 = np.zeros((n0, no_dims))
    gains0 = np.ones((n0, no_dims))

    # dy1: gradient for data2
    dY1 = np.zeros((n1, no_dims))     
    iY1 = np.zeros((n1, no_dims))
    gains1 = np.ones((n1, no_dims))

    # Compute P-values
    # 对称化
    P0 = x2p(X_0, 1e-5, perplexity)
    P0 = P0 + np.transpose(P0)
    P0 = P0 / np.sum(P0)
    # early exaggeration
    P0 = P0 * 4.
    P0 = np.maximum(P0, 1e-12)

    # 对称化
    P1 = x2p(X_1, 1e-5, perplexity)
    P1 = P1 + np.transpose(P1)
    P1 = P1 / np.sum(P1)
    # early exaggeration
    P1 = P1 * 4.
    P1 = np.maximum(P1, 1e-12)

    # Run iterations
    for iter in range(max_iter):
        # Compute pairwise affinities
        sum_Y0 = np.sum(np.square(Y0), 1)
        num0 = -2. * np.dot(Y0, Y0.T)
        num0 = 1. / (1. + np.add(np.add(num0, sum_Y0).T, sum_Y0))
        num0[range(n0), range(n0)] = 0.
        Q0 = num0 / np.sum(num0)  # qij
        Q0 = np.maximum(Q0, 1e-12)

        sum_Y1 = np.sum(np.square(Y1), 1)
        num1 = -2. * np.dot(Y1, Y1.T)
        num1 = 1. / (1. + np.add(np.add(num1, sum_Y1).T, sum_Y1))
        num1[range(n1), range(n1)] = 0.
        Q1 = num1 / np.sum(num1)  # qij
        Q1 = np.maximum(Q1, 1e-12)

        ''' 
        Compute gradient
        '''
        PQ0 = P0 - Q0
        PQ1 = P1 - Q1
        # print(PQ0)
        # input()
        for i in range(n0):
            dY0[i, :] = np.sum(np.tile(PQ0[:, i] * num0[:, i], (no_dims, 1)).T * (Y0[i, :] - Y0), 0)  
                # + penalty gradient
            for m in M:
                # get matching edge
                # eij = m[0]
                # ekl = m[1]
                eij = ekl = m
                # print(eij)

                vi = eij[0]
                vj = eij[1]
                vk = ekl[0]
                vl = ekl[1]

                if vi == i:
                    # get edge vector
                    d0 = np.subtract(Y0[i, :], Y0[vj, :])
                    d1 = np.subtract(Y1[vk, :], Y1[vl, :])
                    dY0[i, :] += 2*beta*S[m]*(d0-d1)
                

        for i in range(n1):
            dY1[i, :] = np.sum(np.tile(PQ1[:, i] * num1[:, i], (no_dims, 1)).T * (Y1[i, :] - Y1), 0)  
                # + penalty gradient
            for m in M:
                 # get matching edge
                # eij = m[0]
                # ekl = m[1]
                eij = ekl = m

                vi = eij[0]
                vj = eij[1]
                vk = ekl[0]
                vl = ekl[1]

                if vk == i:
                    # get edge vector
                    d0 = np.subtract(Y0[vi, :], Y0[vj, :])
                    d1 = np.subtract(Y1[i, :], Y1[vl, :])
                    dY1[i, :] -= 2*beta*S[m]*(d0-d1)               

        # Perform the update
        if iter < 20:
            momentum = initial_momentum
        else:
            momentum = final_momentum

        # ?
        gains0 = (gains0 + 0.2) * ((dY0 > 0.) != (iY0 > 0.)) + \
                (gains0 * 0.8) * ((dY0 > 0.) == (iY0 > 0.))
        gains0[gains0 < min_gain] = min_gain

        gains1 = (gains1 + 0.2) * ((dY1 > 0.) != (iY1 > 0.)) + \
            (gains1 * 0.8) * ((dY1 > 0.) == (iY1 > 0.))
        gains1[gains1 < min_gain] = min_gain

        # update momentum
        # momentum is the 阻力
        # iY is the 
        iY0 = momentum * iY0 - eta * (gains0 * dY0)
        iY1 = momentum * iY1 - eta * (gains1 * dY1)

        # update y
        Y0 = Y0 + iY0
        Y1 = Y1 + iY1

        tmp = np.mean(Y0, 0)
        # print("mean:" + str())

        # subtract mean
        Y0 = Y0 - np.tile(np.mean(Y0, 0), (n0, 1))
        Y1 = Y1 - np.tile(np.mean(Y1, 0), (n1, 1))

        
        ''' 
        Compute current value of cost function
        '''
        if (iter + 1) % 10 == 0:
            C = np.sum(P0 * np.log(P0 / Q0)) +  np.sum(P1 * np.log(P1 / Q1))
            # + penalty term
            for m in M:
                # get matching edge
                eij = ekl = m

                i = eij[0]
                j = eij[1]
                k = ekl[0]
                l = ekl[1]

                # get edge vector
                d0 = np.subtract(Y0[i, :], Y0[j, :])
                d1 = np.subtract(Y1[k, :], Y1[l, :])
                # print(d0)
                # print(d0)
                C += beta * S[m] * np.sum(np.square(np.subtract(d0, d1)))

            # np.sum()
            print("Iteration %d: error is %f" % (iter + 1, C))

        # Stop lying about P-values
        if iter == 100:
            P0 = P0 / 4.
            P1 = P1 / 4.

    # Return solution
    return Y0, Y1


if __name__ == "__main__":
    print("Joint-tsne running test.")
    
    # read high dimensioal data
    hdd0 = "../data/highdims/edges/test1.txt"
    hdd1 = "../data/highdims/edges/test2.txt"
    sm = "../data/similarities/edges/test_similar_edges_1_2.txt"
    X0, labels0 = read_fm_data(hdd0)
    X1, labels1 = read_fm_data(hdd1)
    S, M = read_similarity(sm)

    # labels_0 = labels_1
    # labels = np.loadtxt("data/mnist2500_labels.txt")
    Y0, Y1 = joint_tsne(X0, X1, 2, 3, 3, 20.0)

    # draw two scatterplots
    plt.figure(1)
    plt.scatter(Y0[:, 0], Y0[:, 1], 20, labels0)#

    plt.figure(2)
    plt.scatter(Y1[:, 0], Y1[:, 1], 20, labels1)# 

    plt.show()

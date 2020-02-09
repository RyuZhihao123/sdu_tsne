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
import networkx as nx


# # accepted from C++ program
M = []  # (eij, ekl) 
S = {}  # (eij, ekl): s
beta = 0.00001

def read_fm_data(filepath):
    pts = []
    labels = []
    edges = []
    N = 0

    with open(filepath, 'r', encoding='utf-8') as f:
        line = f.readline()
        while line:
            line=line.strip('\n')
            # print(line)
            if line[0] == 'G':
                N = int(line[1:])
                # begin reading edge information
                print("Neighbor num: " + str(N))
                break
            #  points
            items = line.split()
            # items = line.split("\t+")
            pt = [float(i) for i in items[:-1]]
            # positions
            pts.append(pt)
            # labels
            labels.append(int(items[-1]))
            line = f.readline()
        
        # here we continue to readline
        line = f.readline()
        while line:
            line=line.strip('\n')
            items = line.split()
            # print(items)
            assert(len(items) == N*2 + 1)
            
            i = int(items[0])
            # WE discard distance here
            for n in range(N):
                j = int(items[n*2+1])
                # n*2+2
                edges.append((i, j))

            line = f.readline()


        
        return np.array(pts), labels, edges


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


def tsne(X=np.array([]), Y_I = np.array([]), no_dims=2, initial_dims=50, perplexity=30.0):
    """
        Runs t-SNE on the dataset in the NxD array X to reduce its
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
    X = pca(X, initial_dims).real
    (n, d) = X.shape
    max_iter = 1000
    initial_momentum = 0.5
    final_momentum = 0.8
    eta = 500
    min_gain = 0.01

    if Y_I.shape[0] == 0:# initial solution is not given
        print("Random generate initials.")
        Y = np.random.randn(n, no_dims)
    else:
        print("Initials are given.")
        Y = Y_I

    Y_1_I = Y       # store initial and return


    dY = np.zeros((n, no_dims))
    iY = np.zeros((n, no_dims))
    gains = np.ones((n, no_dims))

    # Compute P-values
    P = x2p(X, 1e-5, perplexity)
    P = P + np.transpose(P)
    P = P / np.sum(P)
    P = P * 4.									# early exaggeration
    P = np.maximum(P, 1e-12)

    # Run iterations
    for iter in range(max_iter):

        # Compute pairwise affinities
        sum_Y = np.sum(np.square(Y), 1)
        num = -2. * np.dot(Y, Y.T)
        num = 1. / (1. + np.add(np.add(num, sum_Y).T, sum_Y))
        num[range(n), range(n)] = 0.
        Q = num / np.sum(num)
        Q = np.maximum(Q, 1e-12)

        # Compute gradient
        PQ = P - Q
        for i in range(n):
            dY[i, :] = np.sum(np.tile(PQ[:, i] * num[:, i], (no_dims, 1)).T * (Y[i, :] - Y), 0)

        # Perform the update
        if iter < 20:
            momentum = initial_momentum
        else:
            momentum = final_momentum
        gains = (gains + 0.2) * ((dY > 0.) != (iY > 0.)) + \
                (gains * 0.8) * ((dY > 0.) == (iY > 0.))
        gains[gains < min_gain] = min_gain
        iY = momentum * iY - eta * (gains * dY)
        Y = Y + iY
        Y = Y - np.tile(np.mean(Y, 0), (n, 1))

        # Compute current value of cost function
        if (iter + 1) % 10 == 0:
            C = np.sum(P * np.log(P / Q))
            print("Iteration %d: error is %f" % (iter + 1, C))

        # Stop lying about P-values
        if iter == 100:
            P = P / 4.

    # Return solution
    return Y, Y_1_I


def joint_tsne(Y_0=np.array([]), 
                X_1=np.array([]),
                Y_1_I = np.array([]), 
               no_dims=2,
               initial_dims_1=50,
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
    X_1 = pca(X_1, initial_dims_1).real

    (n1, d1) = X_1.shape

    max_iter = 1000
    initial_momentum = 0.5
    final_momentum = 0.8
    # momentum
    eta = 500
    min_gain = 0.01

    # Y1 = np.random.randn(n1, no_dims)
    Y1 = Y_1_I
    # Y1 = np.array([[ 1.52340745, 1.37944798],
    # [ 1.04632537 , 1.94709421],
    # [-1.09114757 , -0.47318732],
    # [-1.17815386 , -2.53435897],
    # [ 0.52436536 , 1.19015593],
    # [-0.65184383 , 0.65576772],
    # [ 0.162397  , -1.43788719]])

    # dy1: gradient for data2
    dY1 = np.zeros((n1, no_dims))     
    iY1 = np.zeros((n1, no_dims))
    gains1 = np.ones((n1, no_dims))

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
        sum_Y1 = np.sum(np.square(Y1), 1)
        num1 = -2. * np.dot(Y1, Y1.T)
        num1 = 1. / (1. + np.add(np.add(num1, sum_Y1).T, sum_Y1)) # qij分子 ????
        num1[range(n1), range(n1)] = 0.
        Q1 = num1 / np.sum(num1)  # qij
        Q1 = np.maximum(Q1, 1e-12)

        ''' 
        Compute gradient
        '''
        PQ1 = P1 - Q1

        for i in range(n1):
            dY1[i, :] = np.sum(np.tile(PQ1[:, i] * num1[:, i], (no_dims, 1)).T * (Y1[i, :] - Y1), 0)  
                # + penalty gradient
            for m in M:
                 # get matching edge
                eij = ekl = m

                vi = eij[0]
                vj = eij[1]
                vk = ekl[0]
                vl = ekl[1]

                if vk == i:
                    # get edge vector
                    d0 = np.subtract(Y_0[vi, :], Y_0[vj, :])
                    d1 = np.subtract(Y1[i, :], Y1[vl, :])
                    dY1[i, :] -= 2*beta*S[m]*(d0-d1)          # seems some problems

        # Perform the update
        if iter < 20:
            momentum = initial_momentum
        else:
            momentum = final_momentum

        gains1 = (gains1 + 0.2) * ((dY1 > 0.) != (iY1 > 0.)) + \
            (gains1 * 0.8) * ((dY1 > 0.) == (iY1 > 0.))
        gains1[gains1 < min_gain] = min_gain

        # update momentum
        # momentum is the 阻力
        iY1 = momentum * iY1 - eta * (gains1 * dY1)

        # update y
        Y1 = Y1 + iY1

        # subtract mean
        Y1 = Y1 - np.tile(np.mean(Y1, 0), (n1, 1))

        
        ''' 
        Compute current value of cost function
        '''
        if (iter + 1) % 10 == 0:
            C0 = np.sum(P1 * np.log(P1 / Q1))
            C1= 0
            # + penalty term
            for m in M:
                # get matching edge
                eij = ekl = m

                i = eij[0]
                j = eij[1]
                k = ekl[0]
                l = ekl[1]

                # get edge vector
                d0 = np.subtract(Y_0[i, :], Y_0[j, :])
                d1 = np.subtract(Y1[k, :], Y1[l, :])
                # print(d0)
                # print(d0)
                C1 += beta * S[m] * np.sum(np.square(np.subtract(d0, d1)))
            C = C0+ C1
            # np.sum()
            print("Iteration %d: KL error is %f similarity error is %f" % (iter + 1, C0, C1))

        # Stop lying about P-values
        if iter == 100:
            P1 = P1 / 4.

    # Return solution
    return Y1


def drawGraph(Y, E, labels, match_edges, ax):
    G = nx.DiGraph()
    G.add_edges_from(E)
    Y_ = Y.tolist()
    pos = {}
    for l in range(len(Y_)):
        y = Y_[l]
        # G.add_node(i, pos = (y[0], y[1]))
        pos[l] = (y[0], y[1])
    # for e in E:
    #     G.add_edge(e[0], e[1])
    
    # filter by label
    labelSet = []
    for l in labels:
        if l not in labelSet:
            labelSet.append(l)

    fpos = {}
    for l in labelSet:
        # filter data points for each label
        fpos[l] = {i: pos[i] for i in range(len(labels)) if labels[i] == l}

    # print(fpos)
    # for each label use different colors
    cmap = ['r', 'b', 'y', 'g'] #...
    for l in fpos:
        # print(fpos[l].keys())
        # print(fpos[l].values())
        nx.draw_networkx_nodes(G, pos = fpos[l], nodelist = fpos[l].keys(), node_color= cmap[l], ax = ax)
    nx.draw_networkx_labels(G, pos, font_color='w')

    # similar edges with black
    # similar edges with red
    red_edges = []
    black_edges = []
    for e in E:
        if e in match_edges:
            black_edges.append(e)
        else:
            red_edges.append(e)

    nx.draw_networkx_edges(G, pos, edgelist=black_edges, edge_color='k', arrows=True)
    nx.draw_networkx_edges(G, pos, edgelist=red_edges, edge_color='r', arrows=True)
    

if __name__ == "__main__":
    print("Joint-tsne step running test.")
    
    ''' read high dimensioal data '''
    #../data/highdims/test/fm_2.txt 
    #../data/highdims/edges/fm_1.txt
    hdd0 = "../data/highdims/test/fm_2.txt" 

    #../data/highdims/test/fm_3.txt 
    #../data/highdims/edges/fm_2.txt
    hdd1 = "../data/highdims/test/fm_3.txt" 
    
    #../data/similarities/test/similar_edges_2_3.txt 
    #../data/similarities/edges/similar_edges_1_2.txt
    sm = "../data/similarities/test/similar_edges_2_3.txt" 
    X0, labels0, edges0 = read_fm_data(hdd0)
    X1, labels1, edges1 = read_fm_data(hdd1)
    S, M = read_similarity(sm)
 
    ''' first we apply t-sne to D0 '''
    Y0, Y_1_I = tsne(X = X0, no_dims = 2, initial_dims = 3, perplexity = 20.0)
    ''' then we apply joint-tsne to D1 '''
    # Y1 = joint_tsne(Y_0 = Y0, Y_1_I = Y_1_I, X_1 = X1, no_dims = 2, initial_dims_1 = 3, perplexity = 20.0)
    Y1, dump = tsne(X = X1, Y_I = Y_1_I, no_dims = 2, initial_dims = 3, perplexity = 20.0)


    margin_top = 20
    margin_bottom = 20
    margin_left = 20
    margin_right = 20
    # min_x, max_x
    minX = np.min([np.min(Y0[:, 0]), np.min(Y1[:, 0])]) - margin_left
    maxX = np.max([np.max(Y0[:, 0]), np.max(Y1[:, 0])]) + margin_right
    # min_y, max_y
    minY = np.min([np.min(Y0[:, 1]), np.min(Y1[:, 1])]) - margin_bottom
    maxY = np.max([np.max(Y0[:, 1]), np.max(Y1[:, 1])]) + margin_top

    FLAG_ = True # True False

    '''1. draw graphs'''
    '''2. draw scatterplots'''
    if FLAG_ == True:
        fig0, ax0 = plt.subplots()
        # nx.draw_networkx_nodes(..., ax=ax)
        ax0.set(xlim = (minX, maxX), ylim = (minY, maxY))
        ax0.tick_params(left=True, bottom=True, labelleft=True, labelbottom=True)
        drawGraph(Y = Y0, E = edges0, labels = labels0, match_edges = M, ax = ax0)


        fig1, ax1 = plt.subplots()
        # nx.draw_networkx_nodes(..., ax=ax)
        ax1.set(xlim = (minX, maxX), ylim = (minY, maxY))
        ax1.tick_params(left=True, bottom=True, labelleft=True, labelbottom=True)
        drawGraph(Y = Y1, E = edges1, labels = labels1, match_edges = M, ax = ax1)

        plt.show()
    else:
        plt.figure(1)
        plt.xlim(minX, maxX)
        plt.ylim(minY, maxY)
        plt.scatter(Y0[:, 0], Y0[:, 1], 20, labels0)#

        plt.figure(2)
        plt.xlim(minX, maxX)
        plt.ylim(minY, maxY)
        plt.scatter(Y1[:, 0], Y1[:, 1], 20, labels1)# 

        plt.show()

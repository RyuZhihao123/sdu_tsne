#encoding = utf-8
import numpy as np
import os
from sklearn.neighbors import KDTree
import shutil
import random
from Graph_config_1 import ClearDir, Configuration

config = Configuration()

# read point sets from  file and modify the configuration.
def ReadPointSets(filepath):
    _points = []
    _labels = []

    with open(filepath, 'r') as f:
        for line in f:
            # config.dim = 
            # config.pts_size = 
            _points.append(line[:-1])
            _labels.append(int(line[-1]))


    return _points, _labels


def GetPointSets():  # 获得最初的point set（包含num_clusters个簇，每个簇
    _points = []
    _labels = []
    for i in range(config.num_clusters):
        # 生成一个多维高斯分布
        _mean = np.random.uniform(-config.half_space_dist_, config.half_space_dist_, (config.dim))  # z
        _cov = np.diag(np.array([config.gauss_delta_ for i in range(config.dim)]))  # 方差0.5
        _points.append(np.random.multivariate_normal(
            size=config.pts_size//config.num_clusters, mean=_mean, cov=_cov))
        _labels.append([i for t in range(config.pts_size//config.num_clusters)])

    p = np.array(_points).reshape((config.pts_size, config.dim))
    l = np.array(_labels).reshape((config.pts_size, 1))

    state = np.random.get_state()
    np.random.shuffle(p)
    np.random.set_state(state)
    np.random.shuffle(l)
    return p, l

# 返回扰动的点集以及相似的点


def DisturbPoints(inputs, keep_ratio=0.7):
    output = inputs
    np.arange(0, points.shape[0])
    ids = range(0, config.pts_size)
    # keep_ids 相似性的点
    # dist_ids 不相似的点
    keep_ids = random.sample(ids, int(keep_ratio * config.pts_size))
    keep_ids.sort()
    dist_ids = [i for i in ids if i not in keep_ids]

    for i in dist_ids:
        if config.HARD_MOVE_ == True:
            _moveVec = np.tile(config.distrub_dist_, config.dim)
        else:
            _moveVec = np.random.uniform(-config.distrub_dist_, config.distrub_dist_, (config.dim))

        output[i] += _moveVec
    return output, keep_ids


def DisturbClusters(inputs, labels, disturb_labels = []):
    output = inputs
    np.arange(0, points.shape[0])
    ids = range(0, config.pts_size)
    # dist_ids 不相似的点
    dist_ids = [i for i in range(len(labels)) if labels[i] in disturb_labels]
    # keep_ids 相似性的点
    keep_ids = [i for i in ids if i not in dist_ids]

    if config.HARD_MOVE_ == True:
        _moveVec = np.tile(config.distrub_dist_, config.dim)
    else:
        _moveVec = np.random.uniform(-config.distrub_dist_, config.distrub_dist_, (config.dim))

    # the same displacement
    for i in dist_ids:
        output[i] += _moveVec
    return output, keep_ids


# disturb point sets from different clusters
def DisturbPointSets(inputs, labels, disturb_label_num, keep_ratio= 0.7):
    assert(disturb_label_num>0 and disturb_label_num <= config.num_clusters)

    output = inputs
    np.arange(0, points.shape[0])
    ids = range(0, config.pts_size)
    # keep_ids 相似性的点
    # dist_ids 不相似的点
    disturb_labels = random.sample(range(config.num_clusters), disturb_label_num)

    num_each_cluster = int((1.-keep_ratio)*config.pts_size / disturb_label_num)

    # for each cluster disturb the same number of 
    dist_ids = {}
    for label in disturb_labels:
        label_ids = [i for i in range(len(labels)) if labels[i] == label]
        dist_ids[label] = random.sample(label_ids, num_each_cluster)

    keep_ids = []
    for i in ids:
        flag = True
        for label in disturb_labels:
            if i in dist_ids[label]:
                flag = False
        if flag == True:
            keep_ids.append(i)


    # ...
    for label in disturb_labels:
        if config.HARD_MOVE_ == True:
            _moveVec = np.tile(config.distrub_dist_, config.dim)*random.sample([-1, 1], 1)[0]
        else:
            _moveVec = np.random.uniform(-config.distrub_dist_, config.distrub_dist_, (config.dim))

        # the same displacement
        for i in dist_ids[label]:
            output[i] += _moveVec

    return output, keep_ids



def shiftAllPoints(inputs):
    if config.HARD_MOVE_ == True:
        _moveVec = np.tile(config.distrub_dist_, config.dim)*random.sample([-1, 1], 1)[0]
    else:
        _moveVec = np.random.uniform(-config.distrub_dist_, config.distrub_dist_, (config.dim))

    output = inputs
    for i in range(output.shape[0]):
        output[i] += _moveVec

    # no keeping id
    return output, []


# add noise to undisturbed points
def addNoise(inputs, keep_ids = []):
    outputs = inputs
    for id in keep_ids:
        moveVec = np.random.uniform(-config.noise, config.noise, (config.dim))
        outputs[id] += moveVec

    print("add noise to current data")
    return outputs

# # Amplify the cluster
# def DiffuseCluster(inputs, labels, disturb_label):
#     output = inputs
#     assert(disturb_label>=0 and disturb_label<=config.num_clusters)

#     # compute the centroid of the cluster
#     disturb_ids = [i for i in range(len(labels)) if labels[i] == disturb_label]
#     disturb_inputs = [inputs[id] for id in disturb_ids]
#     disturb_inputs = np.array(disturb_ids)

#     centroid = np.sum(disturb_ids, 0) / disturb_ids.shape(0)

#     # for each point, compute the vector
#     for i in disturb_inputs.shape[0]:
#         # each point go through the vector
#         output[i] += 

#     return output

# # random select keeping edges. NEVER USE IT
# def DisturbEdges(inputs, kd_tree, keep_ratio=0.7):
#     outputs = inputs
#     dists, indices = kd_tree.query(
#         inputs, k=k_closest_count)  # 一口气对所有points构建knn
#     edge_size = indices.shape[0]*(k_closest_count-1)

#     np.arange(0, points.shape[0])
#     ids = range(0, config.pts_size)

#     # keep_edges 相似性的边
#     keep_edges = []
#     while len(keep_edges) != edge_size*keep_ratio:
#         keep_ids_0 = np.random.randint(0, config.pts_size)
#         keep_ids_1 = np.random.randint(0, config.pts_size)
#         # ensure no self-loop and duplicate
#         if keep_ids_0 == keep_ids_1 or [keep_ids_0, keep_ids_1] in keep_edges:
#             continue
#         keep_edges.append([keep_ids_0, keep_ids_1])

#     keep_edges.sort()
#     # dist_edges 不相似的边
#     dist_edges = []
#     for i in range(len(indices)):
#         for j in indices[i]:
#             # print(i)
#             # print(j)
#             if [i, j] not in keep_edges:
#                 dist_edges.append([i, j])

#     # disturb edge endpoints
#     for [i, j] in dist_edges:
#         _moveVec_i = np.random.uniform(-0.5, 0.5, (dim))
#         _moveVec_j = np.random.uniform(-0.5, 0.5, (dim))

#         outputs[i] += _moveVec_i
#         outputs[j] += _moveVec_j

#     return outputs, keep_edges


def DistOfEdges(dists, indices):
    E = {}
    for i in range(indices.shape[0]):
        vi = i
        for j in range(indices[i].shape[0]):
            vj = indices[i][j]
            if vi != vj:
                E[(vi, vj)] = dists[i][j]
    return E


if __name__ == '__main__':
    disturb_cluster_num = 2

    ClearDir(config.dir_graph)
    ClearDir(config.dir_similarity)

    # initial points and corresponding knn tree
    points, labels = GetPointSets()
    tree_0 = KDTree(points)
    dists_0, indices_0 = tree_0.query(
        points, k=config.k_closest_count)  # 一口气对所有points构建knn
    # indices stores k nearest neighbor for each query points
    E_0 = DistOfEdges(dists_0, indices_0)

    print("当前处理: " + str(0) + " Graph")

    file = open(config.dir_graph + "fm_{}.txt".format(0),'w')  # 打开新文件fm_{0}.txt

    ''' 1. 将node信息存储到文件中 '''
    for i in range(config.pts_size):
        fstr = ""
        for j in range(points.shape[1]):
            fstr += "%.16f\t" % (points[i][j])
        fstr += "%d\n" % (labels[i])
        file.write(fstr)

    file.write('G{}\n'.format(config.k_closest_count - 1))
    for i in range(points.shape[0]):  # 遍历每个点，寻找knn，i是下标[0,....,]
        file.write(str(i) + "\t")  # 写入当前点
        count = 0
        for t in range(indices_0[i].shape[0]):
            if indices_0[i][t] == i:  # 是否包含自身
                continue
            if count == config.k_closest_count - 1:  # 只写入Indices中前k-1个点
                break
            # write incient point and corresponding distance
            file.write(str(indices_0[i][t]) +
                        "\t" + str(dists_0[i][t]) + "\t")
            count += 1
        file.write('\n')
    file.close()


    # 循环10次，生成10个图
    for layer in range(1, 10):
        print("当前处理: " + str(layer) + " Graph")

        cur_points, keep_ids = DisturbClusters(points, labels, disturb_labels = random.sample(range(config.num_clusters), disturb_cluster_num))
        if config.add_noise == True:
            cur_points = addNoise(cur_points, keep_ids)


        # 构建新的KNN图
        tree_1 = KDTree(cur_points)
        dists_1, indices_1 = tree_1.query(cur_points, k=config.k_closest_count)
        E_1 = DistOfEdges(dists_1, indices_1)


        file = open(config.dir_graph + "fm_{}.txt".format(layer),'w')  # 打开新文件fm_{1}.txt
        ''' 1. 将node信息存储到文件中 '''
        for i in range(config.pts_size):
            fstr = ""
            for j in range(cur_points.shape[1]):
                fstr += "%.16f\t" % (cur_points[i][j])
            fstr += "%d\n" % (labels[i])
            file.write(fstr)

        ''' 2. store the neighor information '''
        file.write('G{}\n'.format(config.k_closest_count - 1))
        for i in range(cur_points.shape[0]):  # 遍历每个点，寻找knn，i是下标[0,....,]
            file.write(str(i) + "\t")  # 写入当前点
            count = 0
            for t in range(indices_1[i].shape[0]):
                if indices_1[i][t] == i:  # 是否包含自身
                    continue
                if count == config.k_closest_count - 1:  # 只写入Indices中前k-1个点
                    break
                # write incient point and corresponding distance
                file.write(str(indices_1[i][t]) + "\t" + str(dists_1[i][t]) + "\t")
                count += 1
            file.write('\n')
        file.close()

    
        ''' 3. find edges with the same vector '''
        keep_edges = []
        for i in E_0:
            for j in E_1:
                d0 = points[i[0]] - points[i[1]]
                d1 = cur_points[j[0]] - cur_points[j[1]]
                # print(d0)
                if i == j and (d0==d1).all:
                    # print(i)
                    # print(d0)
                    keep_edges.append(i)
        

        # store current loop variables
        points = cur_points                           
        E_0 = E_1

        ''' store similar edges '''
        file = open(config.dir_similarity + "similar_edges_{}_{}.txt".format(layer - 1, layer), 'w')
        for [i, j] in keep_edges:
            # default similarity is 1
            file.write(str(i) + "\t" + str(j) + "\t" + str(i) + "\t" + str(j) + "\t1.0\n")
        file.close()

        ''' store all points and similarities'''
        file = open(config.dir_similarity + "similar_points_{}_{}.txt".format(layer - 1, layer), 'w')
        for i in range(config.pts_size):
            if i in keep_ids:
                # keeping point is 1
                file.write(str(i) + "\t" + str(i) + "\t1.0\n")
            else:
                # distrubbed point is 0
                file.write(str(i) + "\t" + str(i) + "\t0.0\n")
        file.close()


        
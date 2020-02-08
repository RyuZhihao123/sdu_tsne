# it seems there are some problems...
import numpy as np
import os
from sklearn.neighbors import KDTree
import shutil
import random
from Config import ClearDir, Configuration

config = Configuration()

k_closest_count = 4  # K近邻的个数+1（虽然是K=4，但由于包含自身，实际为K-1邻近）
dim = 3              # 点的纬度
num_clusters = 5     # 聚类的数量（尽量是config.pts_size的倍数）

# 
def GetPointSets():  # 获得最初的point set（包含num_clusters个簇，每个簇
    _points = []
    _labels = []
    for i in range(num_clusters):
        # 生成一个多维高斯分布
        _mean = np.random.uniform(-3, 3, (dim))   #z
        _cov = np.diag(np.array([0.5 for i in range(dim)]))  # 方差0.5
        _points.append(np.random.multivariate_normal(size=config.pts_size//num_clusters, mean=_mean, cov=_cov))
        _labels.append([i for t in range(config.pts_size//num_clusters)])

    p = np.array(_points).reshape((config.pts_size, dim))
    l = np.array(_labels).reshape((config.pts_size, 1))

    state = np.random.get_state()
    np.random.shuffle(p)
    np.random.set_state(state)
    np.random.shuffle(l)
    return p, l

# 为
def DisturbPoints(inputs, keep_ratio = 0.7):
    output = inputs
    np.arange(0, points.shape[0])
    ids = range(0,config.pts_size)
    # keep_ids 相似性的点
    # dist_ids 不相似的点
    keep_ids= random.sample(ids,int(keep_ratio * config.pts_size))
    keep_ids.sort()
    dist_ids = [i for i in ids if i not in keep_ids]

    for i in dist_ids:
        _moveVec = np.random.uniform(-0.5,0.5,(dim))
        output[i] += _moveVec
    return output, keep_ids


# random select keeping edges
# disturb points that are not keeping edges
# 1. 先计算knn之后，再删除边以及改变边两端点的位置，但这样就不再满足knn了，又得重新构建，然后不再清楚哪些边是保留的
# 2. 先随机选扰动点，然后构建knn graph。 这样与扰动点临接的边应该都变了。

def DisturbEdges(inputs, kd_tree, keep_ratio = 0.7):
    outputs = inputs
    dists, indices = kd_tree.query(inputs, k=k_closest_count)  # 一口气对所有points构建knn
    edge_size = indices.shape[0]*(k_closest_count-1)

    np.arange(0, points.shape[0])
    ids = range(0,config.pts_size)
    # keep_edges 相似性的边
    keep_edges = []
    while len(keep_edges) != edge_size*keep_ratio:
        keep_ids_0= np.random.randint(0, config.pts_size)
        keep_ids_1= np.random.randint(0, config.pts_size)
        if keep_ids_0 == keep_ids_1:
            continue
        keep_edges.append([keep_ids_0, keep_ids_1])
    
    keep_edges.sort()
    # dist_edges 不相似的边
    dist_edges = []
    for i in range(len(indices)):
        for j in indices[i]:
            # print(i)
            # print(j)
            if [i, j] not in keep_edges:
                dist_edges.append([i, j])

    # disturb edges 
    for [i, j] in dist_edges:
        _moveVec_i = np.random.uniform(-0.5,0.5,(dim))
        _moveVec_j = np.random.uniform(-0.5,0.5,(dim))

        outputs[i] += _moveVec_i
        outputs[j] += _moveVec_j

    return outputs, keep_edges


if __name__ == '__main__':
    
    ClearDir(config.dir_graph)
    ClearDir(config.dir_similarity)
    
    # initial points and corresponding knn tree
    points, labels = GetPointSets()
    tree = KDTree(points)
    dists, indices = tree.query(points, k=k_closest_count)  # 一口气对所有points构建knn

    # 循环10次，生成10个图
    for layer in range(0, 10):
        print("当前处理: " + str(layer) + " Graph")
        cur_points = points
        keep_edges = []
        if layer != 0:
            cur_points, keep_edges = DisturbEdges(points, tree)  # 如果不是第一个，则获取扰动后的点集，以及保持不变的ids

        file = open(config.dir_graph + "fm_{}.txt".format(layer), 'w')  # 打开新文件fm_{1}.txt

        # 首先将node信息存储到文件中
        for i in range(config.pts_size):
            file.write('%.16f\t%.16f\t%.16f\t%d\n' % (cur_points[i][0], cur_points[i][1], cur_points[i][2], labels[i]))
        # 构建新的KNN图
        tree = KDTree(cur_points)
        dists, indices = tree.query(cur_points, k=k_closest_count)  # 一口气对所有points构建knn
        # indices stores k nearest neighbor for each query points
        file.write('G{}\n'.format(k_closest_count - 1))

        for i in range(cur_points.shape[0]):  # 遍历每个点，寻找knn，i是下标[0,....,]
            # kNN
            # print(i, indices[i], points[i], points[indices[i][0]])
            file.write(str(i) + "\t")  # 写入当前点
            count = 0
            for t in range(indices[i].shape[0]):
                if indices[i][t] == i:  # 是否包含自身
                    continue
                if count == k_closest_count - 1:  # 只写入Indices中前k-1个点
                    break
                # write incient point and corresponding distance
                file.write(str(indices[i][t]) + "\t" + str(dists[i][t]) + "\t")
                count += 1
            file.write('\n')
        file.close()
        points = cur_points

        # 存储相似边
        if layer != 0:
            file = open(config.dir_similarity + "similar_edges_{}_{}.txt".format(layer - 1, layer), 'w')
            for [i, j] in keep_edges:
                file.write(str(i)+ "\t" + str(j) + "\n")
            file.close()

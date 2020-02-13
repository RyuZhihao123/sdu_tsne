#encoding = utf-8
import numpy as np
import os
from sklearn.neighbors import KDTree
import shutil
import random
from Config import ClearDir, Configuration

config = Configuration()

# Hyper parameters
k_closest_count = 4  # K近邻的个数+1（虽然是K=4，但由于包含自身，实际为K-1邻近）
dim = 3              # 点的纬度
num_clusters = 5     # 聚类的数量（尽量是config.pts_size的倍数） 
gauss_delta_ = 1.0
keep_ratio_ = 0.9
half_space_dist_ = 3.0
distrub_dist_ = 1.0
HARD_MOVE_ = False  # False True

def GetPointSets():  # 获得最初的point set（包含num_clusters个簇，每个簇
    _points = []
    _labels = []
    for i in range(num_clusters):
        # 生成一个多维高斯分布
        _mean = np.random.uniform(-half_space_dist_, half_space_dist_, (dim))  # z
        _cov = np.diag(np.array([gauss_delta_ for i in range(dim)]))  # 方差0.5
        _points.append(np.random.multivariate_normal(
            size=config.pts_size//num_clusters, mean=_mean, cov=_cov))
        _labels.append([i for t in range(config.pts_size//num_clusters)])

    p = np.array(_points).reshape((config.pts_size, dim))
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
        if HARD_MOVE_ == True:
            _moveVec = np.tile(distrub_dist_, dim)
        else:
            _moveVec = np.random.uniform(-distrub_dist_, distrub_dist_, (dim))

        output[i] += _moveVec
    return output, keep_ids


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

    ClearDir(config.dir_graph)
    ClearDir(config.dir_similarity)

    # initial points and corresponding knn tree
    points, labels = GetPointSets()
    tree_0 = KDTree(points)
    dists_0, indices_0 = tree_0.query(
        points, k=k_closest_count)  # 一口气对所有points构建knn
    # indices stores k nearest neighbor for each query points
    E_0 = DistOfEdges(dists_0, indices_0)

    print("当前处理: " + str(0) + " Graph")

    file = open(config.dir_graph + "fm_{}.txt".format(0),'w')  # 打开新文件fm_{0}.txt

    ''' 1. 将node信息存储到文件中 '''
    for i in range(config.pts_size):
        file.write('%.16f\t%.16f\t%.16f\t%d\n' % (
            points[i][0], points[i][1], points[i][2], labels[i]))

    file.write('G{}\n'.format(k_closest_count - 1))
    for i in range(points.shape[0]):  # 遍历每个点，寻找knn，i是下标[0,....,]
        file.write(str(i) + "\t")  # 写入当前点
        count = 0
        for t in range(indices_0[i].shape[0]):
            if indices_0[i][t] == i:  # 是否包含自身
                continue
            if count == k_closest_count - 1:  # 只写入Indices中前k-1个点
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

        # 扰动前一个点集
        cur_points, keep_ids = DisturbPoints(points, keep_ratio = keep_ratio_)
        # 构建新的KNN图
        tree_1 = KDTree(cur_points)
        dists_1, indices_1 = tree_1.query(cur_points, k=k_closest_count)
        E_1 = DistOfEdges(dists_1, indices_1)


        file = open(config.dir_graph + "fm_{}.txt".format(layer),'w')  # 打开新文件fm_{1}.txt
        ''' 1. 将node信息存储到文件中 '''
        for i in range(config.pts_size):
            file.write('%.16f\t%.16f\t%.16f\t%d\n' % (
                cur_points[i][0], cur_points[i][1], cur_points[i][2], labels[i]))

        ''' 2. store the neighor information '''
        file.write('G{}\n'.format(k_closest_count - 1))
        for i in range(cur_points.shape[0]):  # 遍历每个点，寻找knn，i是下标[0,....,]
            file.write(str(i) + "\t")  # 写入当前点
            count = 0
            for t in range(indices_1[i].shape[0]):
                if indices_1[i][t] == i:  # 是否包含自身
                    continue
                if count == k_closest_count - 1:  # 只写入Indices中前k-1个点
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

        ''' store similar points '''
        file = open(config.dir_similarity + "similar_points_{}_{}.txt".format(layer - 1, layer), 'w')
        for i in keep_ids:
            # default similarity is 1
            file.write(str(i) + "\t" + str(i) + "\t1.0\n")
        file.close()


        
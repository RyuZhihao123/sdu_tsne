#encoding = utf-8
import numpy as np
import os
from sklearn.neighbors import KDTree
import shutil
import random
from add_graph_config import ClearDir, GetGraphIDFromPath, Configuration

config = Configuration()

# read point sets and configuration from file.
def ReadPointSets(filepath):
    _points = []
    _labels = []


    _dim = 0
    _pts_size = 0
    _flag = False

    with open(filepath, 'r') as f:
        lines = f.readlines()
        _pts_size = len(lines)

        for line in lines:
            items = line.split()
            _point = []

            for item in items[:-1]:
                _point.append(float(item))
                
                if not _flag:
                    _dim += 1
            _flag = True

            _points.append(_point)
            # label
            _labels.append(int(items[-1]))


    return np.array(_points), np.array(_labels), _pts_size, _dim


if __name__ == '__main__':
    raw_files = []
    for filename in os.listdir(config.raw_data_path):
        raw_file = os.path.join(config.raw_data_path, filename)
        (file, ext) = os.path.splitext(raw_file)
        if ext == ".txt":
            raw_files.append(raw_file)

    _flag = False
    # 循环10次，生成10个图
    for filepath in raw_files:
        data_id = GetGraphIDFromPath(filepath)
        print("当前处理: " + str(data_id) + " Graph")

        cur_points, labels, pts_size, dim = ReadPointSets(filepath)

        # 必须读完point sets才知道多少点维度，然后才能clear directory
        dir_graph = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/{}/highdims/dim{}/size{}/{}nn/".format(config.dataName, dim, pts_size, config.k_closest_count-1)             # 点集的文件夹
        # dir_similarity = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/{}/similarities/dim{}/size{}/{}nn/".format(config.dataName, dim, pts_size, config.k_closest_count-1)  # 相似性文件夹（哪一些点和边是相似的）

        if _flag == False:
            print((pts_size, dim))
            ClearDir(dir_graph)
            # ClearDir(dir_similarity)
        _flag = True

        # 构建KNN图
        tree = KDTree(cur_points)
        dists, indices = tree.query(cur_points, k=config.k_closest_count)

        file = open(dir_graph + "fm_{}.txt".format(data_id),'w')  # 打开新文件fm_{1}.txt
        ''' 1. 将node信息存储到文件中 '''
        for i in range(pts_size):
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
            for t in range(indices[i].shape[0]):
                if indices[i][t] == i:  # 是否包含自身
                    continue
                if count == config.k_closest_count - 1:  # 只写入Indices中前k-1个点
                    break
                # write incient point and corresponding distance
                file.write(str(indices[i][t]) + "\t" + str(dists[i][t]) + "\t")
                count += 1
            file.write('\n')
        file.close()


        
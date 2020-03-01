import os
import shutil

class Configuration:
    pts_size = 100  # 图中总共点的数量
    keep_ratio = 0.9
    # Hyper parameters
    # perplexity = 50
    # k_closest_count = min(3*perplexity, pts_size)   # K近邻的个数+1（虽然是K=4，但由于包含自身，实际为K-1邻近）
    k_closest_count = 4
    dim = 6              # 点的纬度
    num_clusters = 5     # 聚类的数量（尽量是config.pts_size的倍数） 
    gauss_delta_ = 1.0
    half_space_dist_ = 3.0
    distrub_dist_ = 3.0 * half_space_dist_ #1.0 1./100
    HARD_MOVE_ = False  # False True

    add_noise = True                # 是否为扰动后的点添加噪声
    noise = half_space_dist_/2.    # 噪声大小：即每个点移动的最大距离

    dir_graph = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/data1/highdims/dim{}/size{}/{}nn/".format(dim, pts_size, k_closest_count-1)             # 点集的文件夹
    dir_similarity = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/data1/similarities/dim{}/size{}/{}nn/".format(dim, pts_size, k_closest_count-1)  # 相似性文件夹（哪一些点和边是相似的）
    dir_tsneoutputs = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/data1/results/dim{}/size{}/{}nn/".format(dim, pts_size, k_closest_count-1) # tsne降维后的结果

def ClearDir(dirpath):
    if os.path.exists(dirpath):
        print("正在删除.....",dirpath)
        shutil.rmtree(path=dirpath)
    os.makedirs(dirpath)

def GetFilesIn(dir):
    res = []
    for dir, _, files in os.walk(dir):
        for file in files:
            res.append(dir+file)
    return res

def GetGraphIDFromPath(path):
    print(path)
    ID = path.split(".")[-2].split("_")[-1]
    return int(ID)
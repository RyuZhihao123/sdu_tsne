import os
import shutil

class Configuration:

    dir_graph = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/highdims/edges/"  # 点集的文件夹
    dir_similarity = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/similarities/edges/"  # 相似性文件夹（哪一些点是相似的）
    # dir_tsneoutputs = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/outputs/"  # tsne降维后的结果
    pts_size = 500  # 图中总共点的数量
    # edge_size = 499 # 图中总共边的数量

    # path_similarity = "c:/Users/liuzh/Desktop/similarities/similar_ids_{}_{}.txt"

def ClearDir(dirpath):
    if os.path.exists(dirpath):
        print("正在删除.....",dirpath)
        shutil.rmtree(path=dirpath)
    os.mkdir(dirpath)

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
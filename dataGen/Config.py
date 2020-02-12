import os
import shutil

class Configuration:
    pts_size = 50  # 图中总共点的数量
    # keep_ratio = 0.9
    dir_graph = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/highdims/{}/".format(pts_size)             # 点集的文件夹
    dir_similarity = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/similarities/{}/".format(pts_size)  # 相似性文件夹（哪一些点和边是相似的）
    dir_tsneoutputs = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/results/{}/".format(pts_size) # tsne降维后的结果

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
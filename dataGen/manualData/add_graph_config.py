import os
import shutil

class Configuration:
    # K近邻的个数+1（虽然是K=4，但由于包含自身，实际为K-1邻近）
    k_closest_count = 4

    dataName = "DailySports"
    raw_data_path = "/Users/joe/Codes/QtProjects/t-sne for comparison/data/{}/".format(dataName)

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
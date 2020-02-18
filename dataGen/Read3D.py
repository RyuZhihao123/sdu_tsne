#encoding = utf-8
import numpy as np
import os
from sklearn.neighbors import KDTree
import shutil
import random

def read_ply(filepath):
    points = []
    with open(filepath, "r", encoding="utf-8") as f:
        vertex_count = 0

        line = f.readline()
        while line:
            line = line.strip()
            items = line.split()

            if items[0] == "element":
                if items[1] == "vertex":
                    vertex_count = int(items[2])

            if line == "end_header":
                break
            line = f.readline()
        
        # begin read coordinates of points
        line = f.readline()
        i = 0
        while i < vertex_count:
            line = line.strip()
            items = line.split()

            # only read first 3 items .i. e. position
            points.append(float(items[:3]))
            line = f.readline()
            i += 1

    labels = [0 for i in range(vertex_count)]
    return np.array(points), labels



if __name__ == "__main__":
    points, labels = read_ply("../data/meshlab/off/bunny/data/reconstruction/bun_zipper.ply")

    # for i in range(len()):


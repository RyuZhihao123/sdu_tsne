from sklearn.cluster import KMeans
import numpy as np
# import panda as pd


data_to_cluster = "fm_0.txt"

raw_datas = ["fm_0.txt", "fm_1.txt", "fm_2.txt", "fm_3.txt"]


X = np.loadtxt(data_to_cluster)


k = 4
iteration = 500

model = KMeans(n_clusters = k, n_jobs = 4, max_iter = iteration) #分为k类, 并发数4
model.fit(X) #开始聚类

#简单打印结果
print(model.labels_)#统计各个类别的数目
print(model.cluster_centers_) #找出聚类中心


# Then add label to each file
for raw_data in raw_datas:
    lines = []
    with open(raw_data, 'r') as f:
        lines = f.readlines()
        assert(len(model.labels_) == len(lines))
        for i in range(len(lines)):
            print(lines[i])
            lines[i] = lines[i].strip()
            lines[i]+= ("\t" + str(model.labels_[i])+"\n")
            print(lines[i])


        f.close()

    with open(raw_data, 'w') as f:
        for line in lines:
            f.write(line)

        f.close()
    


            
            


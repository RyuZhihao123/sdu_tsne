import os
import shutil


inputdir = "."
outputdir = "./output/"
# 选取的cluster 下标
data_cluster = [1, 2, 3, 4, 5] # 0 is .DS_STORE
# 选取的player 下标
data_frames = [0, 1, 2, 3, 4, 5, 6, 7, 8]
fm_files = {}

def ClearDir(dirpath):
    if os.path.exists(dirpath):
        print("正在删除.....",dirpath)
        shutil.rmtree(path=dirpath)
    os.makedirs(dirpath)

# create output directory
if not os.path.exists(outputdir):
      os.makedirs(outputdir)
else:
    ClearDir(outputdir)

# create fm_file in the output directory
for f in data_frames:
    fm_path = os.path.join(outputdir, "fm_raw_" + str(f) + ".txt")
    print("create:" + fm_path)
    if not os.path.exists(fm_path):
        fm_file = open(fm_path, 'w')
        fm_files[f] = fm_file


cluster_dirs = os.listdir(inputdir)

label = 0
for c in data_cluster:
    cluster_dir = cluster_dirs[c]
    cluster_path = os.path.join(inputdir,cluster_dir)
    if  os.path.isdir(cluster_path): # one cluster
        print("read cluster: " + cluster_dir)

        for player in os.listdir(cluster_path): 
            player_path = os.path.join(cluster_path,player)
            print("read player: " + player)

            if os.path.isdir(player_path):# one player
                for s in os.listdir(player_path):
                    s_path = os.path.join(player_path, s)
                    print("read s: " + s)

                    with open(s_path, 'r') as f:# one s
                        # one player and s consists of instance
                        # select data frames
                        lines = f.readlines()
                        for f in data_frames:
                            # read one line as one sample and push back to current frame
                            for item in lines[f].strip().split(","):
                                fm_files[f].write(item + "\t")
                            # ADD LABEL
                            fm_files[f].write(str(label) + "\n")
                            # fm_files[f].write("\n")


        print("label{} done. ".format(label))
        label += 1

# all write in
for f in fm_files:
    fm_files[f].close()

print("done")
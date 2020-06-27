#**********************************************************************
#                                                                     *
#               University Of North Carolina Charlotte                *
#                                                                     *
#Program: collision analysis                                          *
#Description: This program is to analyze the collision distribution   *
#                                                                     *
#                                                                     *
#File Name: collisionDistribution.py                                  *
#File Version: 5.0                                                    *
#                                                                     *
#Programmed by: Yu Liu                                                *
#                                                                     *
#Input file: shake_200K_XX.dat                                        *
#Output file:collisionDistribution_200K.txt"                          *
#**********************************************************************
import numpy as np
import matplotlib.pyplot as plt
import math
if __name__ == '__main__':
    path="dataV5/"
    #inputfiles = ["shake_1M_20.dat"]
    inputfiles = ["shake_1M_16.dat","shake_1M_20.dat","shake_1M_24.dat","shake_1M_28.dat","shake_1M_32.dat","shake_1M_36.dat"]
    #inputfiles = ["shake_200K_24.dat","shake_200K_28.dat","shake_200K_32.dat"]
    #inputfiles = ["shake_1M_16.dat","shake_1M_20.dat","shake_1M_24.dat","shake_1M_28.dat","shake_1M_32.dat","shake_1M_36.dat"]
    outputfile="collisionDistribution_1M.txt"

    k=0
    filename=[]
    collisionList = {}
    collisions = []
    collidedDataNum = []
    collisionPositionList = []
    distribution = [[0]*10 for _ in range(len(inputfiles))] # initialization distribution array

    for file in (inputfiles):
        filename.append(file)
        f = open(path+file, mode='r')
        content = f.readlines()
        f.close()

        # find the collision data
        dupCountList= dict(zip(*np.unique(content, return_counts=True))) # duplicate count list #
        # print(dataWithCount)
        # print("Collision list:", collisionList)
        collidedDataNum.append(0)
        collisions.append(0)  #amount of collision
        for key,value in dupCountList.items():
           if value >=2:
                collisionList.update({key:value-1})  #add collision data key=data, valune-1 = collision times
                collisions[k]= collisions[k] + value - 1   #total collision in this file
                collidedDataNum[k] +=1   # number of collision data in this file
        dupCountList.clear()

        # record all collision positions
        p = 0
        fstTime = 1
        a=[]
        a= collisionList.keys()
        collisionPositionList.clear()

        a=collisionList.keys()
        b=[0]*len(collisionList)
        collisionListStatus = dict(zip(a,b))
        for data in content:
            if data in a:
                if collisionListStatus[data] == 1: #the first duplicated data doesn't count in collision
                    collisionPositionList.append(p)
                else:
                    collisionListStatus[data] = 1
            p += 1

        # print(collisionPositionList)
        for n in range(1,11):
            for record in collisionPositionList:
                if record < n*100000 and record >= (n-1)*100000: # for 200k data set
                    distribution[k][n-1]+=1
        k += 1

f = open(outputfile, 'w')
print ("Collision Distribution:")
f.write("Collision Distribution:\n\n")
f.write("Range of Items:    ")
for j in range(10):
    r=100000*(j+1) #for 1 million data set
    f.write("%-6d    " % r)
f.write("\n")
for i in range (len(inputfiles)):
    print("%s:" % inputfiles[i], end='')
    f.write("%s: " % inputfiles[i])
    print(distribution[i], end='')
    for j in range (10):
        f.write("%-6d    "%distribution[i][j])
    print("Total Collisions: %d" % collisions[i])
    f.write("Total Collisions: %d\n" % collisions[i])

f.close()
'''


distribution=[[2782,7274,10740,12972,14897,16273,17197,17969,18516,18964],[180,553,933,1253,1651,1984,2321,2658,3025,3292],
              [11,35,54,89,104,116,131,179,210,233],[3,3,1,10,4,10,6,10,12,19],
              [0,1,0,2,1,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0]]

distribution_accu=[[2782,10056,20796,33768,48665,64938,82135,100104,118620,137584],[180,733,1666,2919,4570,6554,8875,11533,14558,17850],
              [11,46,100,189,293,409,540,719,929,1162],[3,6,7,17,21,31,37,47,59,78],
              [0,1,1,3,4,4,4,4,4,4],[0,0,0,0,0,0,0,0,0,0]]
'''

# accumulated collision from 0 to 200K
distribution_accu= [[0]*10 for _ in range(len(inputfiles))]
for i in range(len(inputfiles)):
    distribution_accu[i][0]= distribution[i][0]
    for j in range(1,10):
        distribution_accu[i][j] = distribution[i][j]+distribution_accu[i][j-1]

# plot
x=["100000","200000","300000","400000","500000","600000","700000","800000","900000","1000000"]
markes = ['-o', '-s', '-^', '-p', '-^',  '-h','-v', '-p', '-d', '-2', '-8', '-6']
colors = ['lightcoral', 'darkorange', 'yellowgreen', 'springgreen', 'dodgerblue', 'purple']

#bar figure
for i in range(len(inputfiles)):
    y1 = [0] * 10
    y = [0] * 10
    for j in range(10):
        if distribution[i][j] != 0:
            y[j] = distribution[i][j]
            y1[j] = math.log10(distribution[i][j])+.2
    #plt.bar(x1,y2,label=inputfiles[i],color='steelblue',alpha=0.8)
    plt.bar(x, y1, label= inputfiles[i][-6:-4]+' bits', color=colors[i], width=0.8)
    for a,b,c in zip (x,y1,y):  #options:  y or y1 (log)
        plt.text(a,b, "%d"% c,ha='center', va= 'bottom',fontsize=8)
plt.xlabel("Data Range")
plt.ylabel("Collision Times (scaled in log10)")
#plt.xlim(20000, 213000, 20000)
plt.ylim(0, 6, 1)
plt.title(u"Collision Distribution by Bitwidth (Dataset Size: 1M)")
#plt.legend(loc="upper right", bbox_to_anchor=(0, 0))
#plt.legend(loc='EastOutside')
plt.xticks(["100000","200000","300000","400000","500000","600000","700000","800000","900000","1000000"],
          ['$0-100K$', '$100-200K$', '$200-300K$', '$300-400K$','$400-500K$','$500-600K$','$600-700K$','$700-800K$','$800-900K$','$900-1000K$'], size = 6)
plt.yticks([0, 1, 2, 3, 4,5,6],
          [r'$0$', r'$10$', r'$100$', r'$1K$', r'$10K$',r'$100K$'], size = 8)
plt.legend(loc='upper center', bbox_to_anchor=(0.5,1),ncol=3,fancybox=True)
plt.show()


#line figure_accumulated
for i in range (len(inputfiles)):
    #y = distribution[i]
    y1 = [0] * 10
    y = [0] * 10
    for j in range(10):
        if distribution_accu[i][j] != 0:
            y[j] = distribution_accu[i][j]
            y1[j] = math.log10(distribution_accu[i][j])+.2
    plt.plot (x,y1,markes[i],label= inputfiles[i][-6:-4]+' bits',color=colors[i]) # extract bitwidth from file name  #options:  y or y1 (log)
    for a,b,c in zip (x,y1,y):  #options:  y or y1 (log)
        plt.text(a,b, "%d"% c,ha='center', va= 'bottom',fontsize=8)

plt.xlabel("Data Range")
plt.ylabel("Collision Times (scaled in log10)")
#plt.xlim(20000, 213000, 20000)
plt.ylim(0, 7, 1)
plt.title(u"Accumulatd Collision Distribution by Bitwidth (Dataset Size: 1M)")
#plt.legend(loc="upper right", bbox_to_anchor=(0, 0))
#plt.legend(loc='EastOutside')
plt.xticks(["100000","200000","300000","400000","500000","600000","700000","800000","900000","1000000"],
          ['$100K$', '$200K$', '$300K$', '$400K$','$500K$','$600K$','$700K$','$800K$','$900K$','$1M$'])
plt.yticks([0, 1, 2, 3, 4,5,6],
          [r'$0$', r'$10$', r'$100$', r'$1K$', r'$10K$',r'$100K$',r'$1000K$'])
plt.legend(loc='upper center', bbox_to_anchor=(0.5,1),ncol=3,fancybox=True)
plt.show()

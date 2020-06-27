#**********************************************************************
#                                                                     *
#               University Of North Carolina Charlotte                *
#                                                                     *
#Program: collision analysis                                          *
#Description: This program is to analyze the collision distribution   *
#                                                                     *
#                                                                     *
#File Name: collisionDistribution.py                                  *
#File Version: 4.0                                                    *
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
    path="dataV4/"
    #inputfiles = ["shake_200K_16.dat"]
    inputfiles = ["shake_200K_16.dat","shake_200K_20.dat","shake_200K_24.dat","shake_200K_28.dat","shake_200K_32.dat","shake_200K_36.dat"]
    outputfile="collisionDistribution_200K.txt"

    k=0
    filename=[]
    firstCollisionData=[]
    secondCollisionData=[]
    collisionList = {}
    collisions = []
    collidedDataNum = []
    p1=[] # first collision head
    p11=[] # first collision tail
    p12=[] # fist collission tail on send time
    p2=[] # second collision head
    p21=[] # second cillision tail
    meantimeFirst2Collision =[]
    timeFisrtCollisionRepeat =[]
    #distribution = [[0]*10]* len(inputfiles)
    distribution = [[0]*10 for _ in range(len(inputfiles))] # initialization distribution array

    for file in (inputfiles):
        filename.append(file)
        f = open(path+file, mode='r')
        content = f.readlines()
        f.close()

        # find the collision data
        dataWidthCount= dict(zip(*np.unique(content, return_counts=True))) # count each recoard's duplicate #
        # print(dataWithCount)
        # print("Collision list:", collisionList)
        collidedDataNum.append(0)
        collisions.append(0)  #amount of collision
        for key,value in dataWidthCount.items():
           if value >=2:
                collisionList.update({key:value-1})  #add collision data key=data, valune-1 = collision times
                collisions[k]= collisions[k] + value - 1   #total collision in this file
                collidedDataNum[k] +=1   # number of collision data in this file

        dataWidthCount.clear()
        #print("%s:  "  % (inputfiles[k-1]),end="")
        #print(collisionList) # for debugging

        allCollisionPosition=[]
        allCollisionPosition.append(0)

        # record all collision positions
        p = 0
        collisionPositionList = []
        collisionPositionList.clear()
        #initialize the disctionary for flaging collision
        a=collisionList.keys()
        b=[0]*len(collisionList)
        collisionListStatus = dict(zip(a,b))
        for data in content:
            for collision in collisionListStatus.keys():
                if data == collision:
                    if collisionListStatus[collision] == 1: # the original collide item will not be counted
                        collisionPositionList.append(p)
                    else:
                        collisionListStatus[collision] = 1
            p+=1

        # print(collisionPositionList)
        for n in range(1,11):
            for record in collisionPositionList:
                if record < n*20000 and record >= (n-1)*20000: # for 200k data set
                    distribution[k][n-1]+=1
        k += 1
f = open(outputfile, 'w')
print ("Collision Distribution:")
f.write("Collision Distribution:\n\n")
f.write("Range of Items:    ")
for j in range(10):
    r=20000*(j+1) #for 200k data set
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
'''

# plot
x=[20000,40000,60000,80000,100000,120000,140000,160000,180000,200000]
markes = ['-o', '-s', '-^', '-p', '-^', '-v', '-p', '-d', '-h', '-2', '-8', '-6']

for i in range (len(inputfiles)):
    #y = distribution[i]
    y1 = [0] * 10
    y = [0] * 10
    for j in range(10):
        if distribution[i][j] != 0:
            y[j] = distribution[i][j]
            y1[j] = math.log10(distribution[i][j])+.2
    plt.plot (x,y1,markes[i],label= inputfiles[i][-6:-4]+' bits') # extract bitwidth from file name  #options:  y or y1 (log)
    for a,b,c in zip (x,y1,y):  #options:  y or y1 (log)
        plt.text(a,b, "%d"% c,ha='left', va= 'bottom',fontsize=8)

plt.xlabel("Data Range")
plt.ylabel("Collision Times (scaled in log10)")
plt.xlim(20000, 213000, 20000)
plt.ylim(0, 6, 2)
plt.title(u"Collision Distribution by Bitwidth (Dataset Size: 200K)")
#plt.legend(loc="upper right", bbox_to_anchor=(0, 0))
#plt.legend(loc='EastOutside')
plt.xticks([20000,40000,60000,80000,100000,120000,140000,160000,180000,200000],
          ['$20K$', '$40K$', '$60K$', '$80K$','$100K$','$120K$','$140K$','$160K$','$180K$','$200K$'])
plt.yticks([0, 1, 2, 3, 4,5,6],
          [r'$0$', r'$10$', r'$100$', r'$1K$', r'$10K$',r'$100K$'])
plt.legend(loc='upper center', bbox_to_anchor=(0.5,1),ncol=3,fancybox=True)
plt.show()


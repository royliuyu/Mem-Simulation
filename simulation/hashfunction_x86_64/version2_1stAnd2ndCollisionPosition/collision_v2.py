#**********************************************************************
#                                                                     *
#               University Of North Carolina Charlotte                *
#                                                                     *
#Program: collision analysis                                          *
#Description: This program is to analyze the collision situation with *
#             various bit width sha codes                             *
#			                                                          *
#File Name: collision.py                                              *
#File Version: 2.0                                                    *
#                                                                     *
#Programmed by: Yu Liu                                                *
#                                                                     *
#Input file: input.h										          *
#Output file:collision_shake.txt"                                     *
#**********************************************************************
import numpy as np
import matplotlib as plt
import matplotlib.pyplot as plt
import re


if __name__ == '__main__':
    path="data/75000/"
    #inputfiles=["output_shake_40.dat"]
    # If select to run below file together,it will take around than 2-3 hours
    inputfiles=["shake_75000_16.dat","shake_75000_24.dat","shake_75000_32.dat","shake_75000_40.dat","shake_75000_48.dat","shake_75000_56.dat","shake_75000_64.dat"]
    #inputfiles=["shake_10000_16.dat","shake_10000_24.dat"]
    #inputfiles = ["shake_10000_16.dat"]

    #inputfiles=["output_shake_32.dat"]
    outputfile="collision_75K.txt"

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

    for file in (inputfiles):
        filename.append(file)
        f = open(path+file, mode='r')
        content = f.readlines()
        f.close()

        # find the first 2 lollisions
        j=0
        firstCollisionData.append('-')
        secondCollisionData.append('-')
        p1.append(0)
        p11.append(0)
        p12.append(0)
        p2.append(0)
        p21.append(0)
        meantimeFirst2Collision.append(0)
        timeFisrtCollisionRepeat.append(0)

        findFirstComplete=0
        findSecondComplete =0
        for data in content:
            for pt in range(j+1,len(content)):
                if content[pt]==content[j]:
                    #print("j-%d: %s VS pt-%d: %s "%(j,content[j],pt,content[pt])) # for debugging
                    if findFirstComplete == 0:
                        if p11[k] == 0: # first collision
                            firstCollisionData[k] = content[pt].strip('\n')  # record the the data of first collision
                            p1[k] = j
                            p11[k]= pt
                        else: # first collision on second time
                            p12[k] = pt
                            findFirstComplete = 1
                        break
                    if findSecondComplete == 0 and findFirstComplete == 1:  # second collision
                        secondCollisionData[k]= content[pt].strip('\n')
                        p2[k] = j
                        p21[k] = pt
                        findSecondComplete =1
                        break
            if findSecondComplete == 1 and findSecondComplete == 1: #if find 2 collisions then quit
                break
            else:
                j+=1

        if p12[k] != 0:
            timeFisrtCollisionRepeat[k] = p12[k]-p11[k]
        if p21[k] != 0:
            meantimeFirst2Collision[k] = p21[k]-p11[k]

        # count the collision amount
        dataWithCount= dict(zip(*np.unique(content, return_counts=True))) # count each recoard's duplicate #
        # print(dataWithCount)
        # print("Collision list:", collisionList)
        collidedDataNum.append(0)
        collisions.append(0)  #amount of collision
        for key,value in dataWithCount.items():
           if value >=2:
                collisionList.update({key:value-1})  #collision data
                collisions[k]= collisions[k] + value - 1   #total collision in this file
                collidedDataNum[k] +=1   # number of collision data in this file
        k+=1
        dataWithCount.clear()
        #print("%s:  "  % (inputfiles[k-1]),end="")
        print(collisionList) # for debugging
        collisionList.clear()

    print("\n")
    #print(count) # for debugging

    # output the result
    f = open(outputfile, 'w')
    print("Data source              Number of collided data          Total collissions        First colission position         Second collssion position         Time between first repeating collision     Mean-time of first two collisions     First collided data                 Second collided data")
    f.write("Data source              Number of collided data          Total collissions        First colission position         Second collssion position         Time between first repeating collision     Mean-time of first two collisions     First collided data                 Second collided data\n")
    for i in range(len(inputfiles)):
        print("%-20s     %-6d                           %-6d                  %6d -> %-6d                 %6d -> %-6d                   %-6d                                     %-6d                                %-32s    %-32s" %(inputfiles[i],collidedDataNum[i],collisions[i], p1[i],p11[i],p2[i],p21[i],timeFisrtCollisionRepeat[i],meantimeFirst2Collision[i],firstCollisionData[i],secondCollisionData[i]))

        f.write("%-20s     %-6d                           %-6d                  %6d -> %-6d                 %6d -> %-6d                   %-6d                                     %-6d                                %-32s    %-32s\n" %(inputfiles[i],collidedDataNum[i],collisions[i], p1[i],p11[i],p2[i],p21[i],timeFisrtCollisionRepeat[i],meantimeFirst2Collision[i],firstCollisionData[i],secondCollisionData[i]))

    f.close()
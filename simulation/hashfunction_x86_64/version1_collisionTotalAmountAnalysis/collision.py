#**********************************************************************
#                                                                     *
#               University Of North Carolina Charlotte                *
#                                                                     *
#Program: collision analysis                                          *
#Description: This program is to analyze the collision situation with *
#             various bit width sha codes                             *
#			                                                          *
#File Name: collision.py                                              *
#File Version: 1.0                                                    *
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
    path="new_data/"
    #inputfiles=["output_shake_40.dat"]
    # If select to run below file together,it will take around than 2-3 hours
    inputfiles=["output_shake_12.dat","output_shake_16.dat","output_shake_20.dat","output_shake_24.dat","output_shake_28.dat","output_shake_32.dat","output_shake_36.dat","output_shake_40.dat","output_shake_48.dat","output_shake_56.dat","output_shake_64.dat"]
    #inputfiles=["output_shake_32.dat"]


    outputfile="collision_shake.txt"

    k=0
    filename=[]
    findCollision=[]
    firstCollisionPosition=[]
    firstCollisionData=[]
    collisionList = {}
    collisions = []
    collidedDataNum = []
    temp = []

    for file in (inputfiles):
        filename.append(file)
        f = open(path+file, mode='r')
        content = f.readlines()
        f.close()

        # find the first lollision
        j=0
        temp.append(0)
        firstCollisionPosition.append(0)
        firstCollisionData.append('')
        findCollision.append(0)   # a flag of collision
        for data in content:
            for pt in range(j+1,len(content)):
                if content[pt]==content[j]:
                    #print("j-%d: %s VS pt-%d: %s "%(j,content[j],pt,content[pt])) # for debugging
                    firstCollisionPosition[k]=pt # record the position of first collision
                    temp[k] = j
                    firstCollisionData[k]=content[pt].strip('\n') # record the the data of first collision without '\n'
                    findCollision[k]=1
                    break
            if findCollision[k] == 1: # if find a collision
                break
            else:
                j+=1

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
        print("%s:  "  % (inputfiles[k-1]),end="")
        print(collisionList) # for debugging
        collisionList.clear()
    print("\n")
    #print(count) # for debugging

    # output the result
    f = open(outputfile, 'w')
    print("Data source                   First colission position             Number of collided data          Total collissions               First collided data")
    f.write("Data source                   First colission position             Number of collided data          Total collissions               First collided data\n")
    for i in range(len(inputfiles)):
        print("%-20s          %-4d -> %-5d                        %-6d                           %-6d                          %-64s" %(inputfiles[i], temp[i],firstCollisionPosition[i],collidedDataNum[i],collisions[i], firstCollisionData[i]))
        f.write("%-20s          %-4d -> %-5d                        %-6d                           %-6d                          %-64s\n" %(inputfiles[i], temp[i],firstCollisionPosition[i],collidedDataNum[i],collisions[i], firstCollisionData[i]))
    f.close()

    # plot the result
    plt.rcParams['font.sans-serif']=['Comic Sans MS']

    a=collisions
    b=firstCollisionPosition
    lx=[]
    l=[i for i in range(len(inputfiles))]
    for string in inputfiles:
        num=number = re.sub("\D","",string)
        lx.append(num)

    #print(firstCollisionPosition)
    #print(collisions)

    fmt='%d%%'
    fig = plt.figure()
    plt.title('COLLISION (with original data)') # warning
    plt.xlabel(u"SHA3 bits", fontproperties='Comic Sans MS') # warning

    ax1 = fig.add_subplot(111)
    ax1.plot(l, b,'or-',label=u'First collision position')
    for i,(_x,_y) in enumerate(zip(l,b)):
        plt.text(_x,_y,b[i],color='black',fontsize=10,)
    ax1.legend(loc=1)
    ax1.set_ylim([0, 100000])
    ax1.set_ylabel('First collision position')

    #fisrt collision position
    ax2 = ax1.twinx() # second axel
    plt.bar(l,a,alpha=0.3,color='blue',label=u'Total collisions')
    ax2.legend(loc=2)
    ax2.set_ylim([0, 100000])  #y axel range
    ax2.set_ylabel('Total collisions')
    plt.legend(prop={'family':'Comic Sans MS','size':8},loc="upper left")
    #ax.set_xlabel('First collision position');
    plt.xticks(l,lx)
    plt.show()